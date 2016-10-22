#include "netdevice.h"

int net_getbcastaddr(const char *devname, unsigned int *addr)
{
	unsigned int ipv4;
	
	net_getipaddr(devname, &ipv4);
	*addr = ipv4 | 0xff000000;

	return 0;
}

int net_getipaddr(const char *devname, unsigned int *ipv4)
{
	struct ifreq ifreq_buf[4];
	struct ifconf ifconf_buf;
	struct sockaddr_in *ipbuf;
	int sockfd;
	int index;
	int max;
	int retval;

	ifconf_buf.ifc_len = sizeof(ifreq_buf);
	ifconf_buf.ifc_req = ifreq_buf;

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		retval = -1; goto goto_return;
	}

	if (-1 == ioctl(sockfd, SIOCGIFCONF, &ifconf_buf)) {
		retval = -1; goto goto_return;
	}
			
	max = ifconf_buf.ifc_len / sizeof(*ifreq_buf);

	for (index = 0; index < max; index ++) {
		if (0 == strcmp(devname, ifreq_buf[index].ifr_name)) {
			ipbuf = (struct sockaddr_in *)&ifreq_buf[index].ifr_addr;
			*ipv4 = ipbuf->sin_addr.s_addr;
			retval = index;
			goto goto_return;
		}
	}
	retval = -1;

goto_return:
	close(sockfd);
	return retval;
}

int net_gethwaddr(const char *devname, unsigned char *mac)
{
	struct ifreq ifreq_buf[4];
	struct ifconf ifconf_buf;
	int sockfd;
	int index;
	int max;
	int retval;

	ifconf_buf.ifc_len = sizeof(ifreq_buf);
	ifconf_buf.ifc_req = ifreq_buf;

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		retval = -1; goto goto_return;
	}

	if (-1 == ioctl(sockfd, SIOCGIFCONF, &ifconf_buf)) {
		retval = -1; goto goto_return;
	}
			
	max = ifconf_buf.ifc_len / sizeof(*ifreq_buf);

	for (index = 0; index < max; index ++) {
		if (0 != strcmp(devname, ifreq_buf[index].ifr_name))
			continue;

		if (-1 == ioctl(sockfd, SIOCGIFHWADDR, &ifreq_buf[index])) {
			retval = 1; goto goto_return;
		}
		memcpy(mac, (char *)&ifreq_buf[index].ifr_hwaddr+2, 6);
		retval = index;
		goto goto_return;
	}
	retval = -1;

goto_return:
	close(sockfd);
	return retval;
}

int net_getifindex(const char *devname)
{
	struct ifreq ifreq_buf;
	int sockfd;
	int retval;

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		retval = -1; goto goto_return;
	}

	strcpy(ifreq_buf.ifr_name, devname);
	if (-1 == ioctl(sockfd, SIOCGIFINDEX, &ifreq_buf)) {
		retval = -1; goto goto_return;
	}
			
	retval = ifreq_buf.ifr_ifindex;
goto_return:
	close(sockfd);
	return retval;
}
