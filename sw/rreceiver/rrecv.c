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
    int err = 0, rc, i, j;
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

    const uint8_t buf[16] = {};


    for (i = 0; i < 10; i++) {
	    rc = recv(netsock, (void *)buf, 16, 0);
	    printf("%d bytes received \n", rc);
	    for (j = 0; j < 16; j++) {
	    	printf("0x%x ", buf[j]);
	    }

	    printf("\n");

    }

op_err:
    close(netsock);

    return err;
}
