#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#define BUFF_SIZE	1024
#define FIFO_NAME	"fifo"	
#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
