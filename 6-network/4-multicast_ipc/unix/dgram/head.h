
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
#define SOCK_PATH_SER	"./sock_server"
#define SOCK_PATH_CLT	"./sock_client"
#define BUFF_SIZE	1024
