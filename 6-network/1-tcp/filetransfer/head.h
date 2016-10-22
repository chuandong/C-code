#ifndef _HEAD_H_
#define _HEAD_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "md5.h"

#define DEBUG	1

#define SER_ADDR	"192.168.10.10"
#define SER_PORT	50001

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

typedef struct sockaddr sa_t;


#define FILE_BUFF_SIZE	4096
#define FILE_NAME_MAXLEN	256
#define FILE_MD5_MAXLEN		16
struct file_info {
	char name[FILE_NAME_MAXLEN];
	mode_t mode;
	int size;
	unsigned char md5[FILE_MD5_MAXLEN];
};
typedef struct file_info finfo_t;

#endif
