#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int arc, char **argv)
{
    int err = 0, rc, i;
    struct ifreq ifr;

    printf("argv[0]: %s, argv[1]: %s \n", argv[0], argv[1]);

   
    int netsock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    memset(&ifr, 0, sizeof(ifr));

    strncpy(ifr.ifr_name, argv[1], sizeof(ifr.ifr_name));

    // get the index number of the interface
    err = ioctl(netsock, SIOCGIFINDEX, &ifr);
    if (err < 0) {
        printf("ioctl SIOCGIFINDEX failed for %s\n", argv[1]);
	goto op_err;
    }

    printf("init: IFRIDX ifr_ifindex=%d\n",ifr.ifr_ifindex);
    int ifidx = ifr.ifr_ifindex;

    struct sockaddr_ll addr;
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_ALL);
    addr.sll_ifindex = ifidx;

    err = bind(netsock, (struct sockaddr *) &addr,
        sizeof(struct sockaddr_ll));

    if (err < 0) {
        printf("bind failed with error: %d\n", err);
    }

    const uint8_t buf[16] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x12};

    for (i = 0; i < 10; i++) {
	    rc = send(netsock, (void *)buf, 16, 0);
	    printf("%d bytes sent \n", rc);

    }

op_err:
    close(netsock);

    return err;
}
