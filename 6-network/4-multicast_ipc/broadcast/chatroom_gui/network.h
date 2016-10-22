#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "netdevice.h"

#define NET_DEV_NAME "eth0"
#define NET_PORT 50000

typedef struct _network_ {
	int net_fd;
	unsigned int net_bcast;
	unsigned int net_peer;
}Network_t;
extern Network_t *network_init(void);
extern int network_destroy(Network_t *net);
extern int network_send(Network_t *net, const void *buff, size_t size);
extern int network_recv(Network_t *net, void *buff, size_t size);
extern int network_recv_timeout(Network_t *net, void *buff, size_t size, struct timeval *tm);
extern int network_broadcast(Network_t *net, const void *buff, size_t size);
extern unsigned int network_get_peer(Network_t *net);
extern unsigned int network_get_bcast(Network_t *net);

#endif /* __NETWORK_H__ */
