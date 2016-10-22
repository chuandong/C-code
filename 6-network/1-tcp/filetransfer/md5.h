#ifndef __MD5_H__
#define __MD5_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include "md5core.h"

#define BUFF_SIZE	4096
#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

void md5_num2str(const unsigned char *md5num, char *md5str);

extern int md5_file(const char *fname, unsigned char *md5num);
extern int md5_str(const char *str, unsigned char *md5num);

#endif	/* __MD5_H__ */
