#include "network.h"

Network_t *network_init(void)
{
	int sockfd;
	int is_bacst = 1;
	unsigned int bcastip;
	struct sockaddr_in bcastaddr;
	Network_t *net;

	net = malloc(sizeof(*net));

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		return NULL;

	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &is_bacst, sizeof(is_bacst)))
		return NULL;
	
	net_getbcastaddr(NET_DEV_NAME, &bcastip);
	
	bcastaddr.sin_family = AF_INET;
	bcastaddr.sin_port = htons(NET_PORT);
	bcastaddr.sin_addr.s_addr = bcastip;
//	printf("%s\n", inet_ntoa(bcastaddr.sin_addr));
	if (-1 == bind(sockfd, (struct sockaddr *)&bcastaddr, sizeof(bcastaddr)))
		return NULL;

	net->net_fd = sockfd;
	net->net_bcast = bcastip;

	return net;
}

int network_destroy(Network_t *net)
{
	close(net->net_fd);
	free(net);

	return 0;
}

int network_broadcast(Network_t *net, const void *buff, size_t size)
{
	int sockfd = net->net_fd;
	struct sockaddr_in addr;
	int ret;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(NET_PORT);
	addr.sin_addr.s_addr = net->net_bcast;

	ret = sendto(sockfd, buff, size, 0,
			(struct sockaddr *)&addr, sizeof(addr));

	return ret;
}

int network_send(Network_t *net, const void *buff, size_t size)
{
	int sockfd = net->net_fd;
	struct sockaddr_in addr;
	int ret;

	addr.sin_family = AF_INET;
	addr.sin_port = NET_PORT;
	addr.sin_addr.s_addr = net->net_peer;

	ret = sendto(sockfd, buff, size, 0,
			(struct sockaddr *)&addr, sizeof(addr));

	return ret;
}

int network_recv(Network_t *net, void *buff, size_t size)
{
	int sockfd = net->net_fd;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int ret;

	ret = recvfrom(sockfd, buff, size, 0, 
			(struct sockaddr *)&addr, &addrlen);
	net->net_peer = addr.sin_addr.s_addr;

	return ret;
}

int network_recv_timeout(Network_t *net, void *buff, size_t size, struct timeval *tm)
{
	int sockfd = net->net_fd;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int ret;
	struct timeval no_tmo = {0,0};
	
	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, tm, sizeof(*tm)))
		return -1;

	ret = recvfrom(sockfd, buff, size, 0, 
			(struct sockaddr *)&addr, &addrlen);
	net->net_peer = addr.sin_addr.s_addr;
	
	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &no_tmo, sizeof(*tm)))
		return -1;

	return ret;
}

unsigned int network_get_peer(Network_t *net)
{
	return net->net_peer;
}

unsigned int network_get_bcast(Network_t *net)
{
	return net->net_bcast;
}
