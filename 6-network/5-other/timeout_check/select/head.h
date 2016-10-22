#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <sys/select.h>

#define SER_ADDR	"192.168.10.10"
#define SER_PORT	10001

#define BUFF_SIZE	(65535 - 20 - 8)
#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#endif /* __HEAD_H__ */
