#ifndef __NETDEVICE_H__
#define __NETDEVICE_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>

extern int net_getbcastaddr(const char *devname, unsigned int *ipv4);
extern int net_getipaddr(const char * devname, unsigned int *ipv4);
extern int net_gethwaddr(const char * devname, unsigned char *mac);
extern int net_getifindex(const char *devname);

#endif /* __NETDEVICE_H__ */
