#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_SIZE  2048

int main(int argc, char *arhv[])
{
	int fd_r, fd_w;  
	int i;
	int iRet=0;
	char buff[MAX_SIZE];
	
	struct	stat	statbuf;
	
	stat("/home/dong/code/cfile/aa.txt", &statbuf);
	fd_r = open("/home/dong/code/cfile/aa.txt", O_RDONLY );
	fd_w = open("/home/dong/code/cfile/bb.txt", O_WRONLY );
	
	for (i = 0; i < statbuf.st_size; i++)
	{
		read(fd_r, buff, 1);
		write(fd_w, buff,1);
	}
	return 0;
}
