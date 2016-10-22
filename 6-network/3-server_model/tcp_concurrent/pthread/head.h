#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define error_exit(_errmsg_) \
	error(EXIT_FAILURE, errno, _errmsg_)

#define BUFF_SIZE	1024

#define SER_PORT	50000
#define SER_ADDR	"192.168.1.44"

#endif /* __HEAD_H__ */
