#ifndef _HEAD_H_
#define _HEAD_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE	1024

#define SER_ADDR	"192.168.10.10"
#define SER_PORT	50001

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

typedef struct sockaddr sa_t;

#endif
