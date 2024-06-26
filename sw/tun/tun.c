#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <string.h>

int tun_alloc(char *dev, int flags) {

  struct ifreq ifr;
  int fd, err;
  char *clonedev = "/dev/net/tun";

  /* Arguments taken by the function:
   *
   * char *dev: the name of an interface (or '\0'). MUST have enough
   *   space to hold the interface name if '\0' is passed
   * int flags: interface flags (eg, IFF_TUN etc.)
   */

   /* open the clone device */
   if( (fd = open(clonedev, O_RDWR)) < 0 ) {
     return fd;
   }

   /* preparation of the struct ifr, of type "struct ifreq" */
   memset(&ifr, 0, sizeof(ifr));

   ifr.ifr_flags = flags;   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */

   if (*dev) {
     /* if a device name was specified, put it in the structure; otherwise,
      * the kernel will try to allocate the "next" device of the
      * specified type */
     strncpy(ifr.ifr_name, dev, IFNAMSIZ);
   }

   /* try to create the device */
   if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
     close(fd);
     return err;
   }

  /* if the operation was successful, write back the name of the
   * interface to the variable "dev", so the caller can know
   * it. Note that the caller MUST reserve space in *dev (see calling
   * code below) */
  strcpy(dev, ifr.ifr_name);

  /* this is the special file descriptor that the caller will use to talk
   * with the virtual interface */
  return fd;
}

int recv_tun_packets(int tun_fd, char *tun_name, uint8_t *buffer)
{
	int nread;
	/* Now read data coming from the kernel */
	while(1) {
		/* Note that "buffer" should be at least the MTU size of the interface, eg 1500 bytes */
		nread = read(tun_fd, buffer, 1500);
		if(nread < 0) {
			perror("Reading from interface");
			close(tun_fd);
			return -1;
		}

		/* Do whatever with the data */
		printf("Read %d bytes from device %s\n", nread, tun_name);
		for (int i = 0; i < nread; i++) {
			printf("0x%02x ", buffer[i]);
		}
	}

	return 0;
}


int main(int argc, char **argv)
{
	int tunfd, rc;
	char tun_name[IFNAMSIZ];

	strcpy(tun_name, argv[1]);
	tunfd = tun_alloc(tun_name, IFF_TAP);  /* tun interface */
	
	printf("tun_name: %s\n", tun_name);

	/* Need to get the mtu size of the tun interface*/
	uint8_t *buffer = (uint8_t *)malloc(1500);
	if (!buffer) {
		printf("malloc failed\n");
		close(tunfd);
		return -1;
	}
	
	printf("before recv_tun_packets\n");
	rc = recv_tun_packets(tunfd, tun_name, buffer);

	return rc;
}
