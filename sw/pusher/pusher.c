#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MTU_MAX 1500

int tun_alloc(char *dev, int flags) 
{

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
	if((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
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


int init_sender(const char *ifname, int *netsock)
{
	int err = 0, rc, i;
	struct ifreq ifr;

	printf("interface-name: %s\n", ifname);

   
	*netsock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	memset(&ifr, 0, sizeof(ifr));

	strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

	// get the index number of the interface
	err = ioctl(*netsock, SIOCGIFINDEX, &ifr);
	if (err < 0) {
		printf("ioctl SIOCGIFINDEX failed for %s\n", ifname);
		goto op_err;
	}

	printf("init: IFRIDX ifr_ifindex=%d\n",ifr.ifr_ifindex);
	int ifidx = ifr.ifr_ifindex;

	struct sockaddr_ll addr;
	addr.sll_family = AF_PACKET;
	addr.sll_protocol = htons(ETH_P_ALL);
	addr.sll_ifindex = ifidx;

	err = bind(*netsock, (struct sockaddr *) &addr,
			sizeof(struct sockaddr_ll));

	if (err < 0) {
		printf("bind failed with error: %d\n", err);
	}
op_err:
	

	return err;
}


int recv_send_packets(int tun_fd, int netsock)
{
	int nread;
	
	/* Need to get the mtu size of the tun interface*/
	uint8_t *buffer = (uint8_t *)malloc(MTU_MAX);
	if (!buffer) {
		printf("malloc failed\n");
		
		return -1;
	}
	
	/* Now read data coming from the kernel */
	while(1) {
		/* Note that "buffer" should be at least the MTU size of the interface, eg 1500 bytes */
		nread = read(tun_fd, buffer, MTU_MAX);
		if(nread < 0) {
			perror("Reading from interface");
			close(tun_fd);
			return -1;
		}

		/* Do whatever with the data */
		printf("Read %d bytes \n", nread);
		for (int i = 0; i < nread; i++) {
			printf("0x%02x ", buffer[i]);
		}
		printf("\n");
		
		nread = send(netsock, (void *)buffer, nread, 0);
	}

	return 0;
}


int main(int arc, char **argv)
{
    	int tunfd, rc, netsock;
	char tun_name[IFNAMSIZ];
	char dest_netdev[IFNAMSIZ];
	
	strcpy(tun_name, argv[1]);
	strcpy(dest_netdev, argv[2]);
	
	tunfd = tun_alloc(tun_name, IFF_TAP);  /* tun interface */
	
	printf("tun_name: %s\n", tun_name);
	printf("Destination netdevice: %s\n", dest_netdev);
	
	rc = init_sender(dest_netdev, &netsock);
	
	if (rc) {
		close(tunfd);
		printf("init_sender failed ...\n");
		return rc;
	}

	printf("before recv_send_packets\n");
	rc = recv_send_packets(tunfd, netsock);
	
	if (rc) {
		printf("recv_send_packets failed\n");
	}
	
	close(tunfd);
	close(netsock);
    
	return rc;
}
