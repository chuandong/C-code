#include "head.h"

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in seraddr;
	
	const char *fname = argv[1];
	int fd;
	finfo_t infbuf;
	struct stat statbuf;
	char buff[FILE_BUFF_SIZE];
	int ret;

	if (argc != 2) {
		fprintf(stderr, "invalid arguemt !\n");
		fprintf(stderr, "USAGE:\n\t./client srcfile");
		return -1;
	}

	/* network init */
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))) 
		error_exit("socket");

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == connect(sockfd, (sa_t*)&seraddr, sizeof(sa_t)))
		error_exit("connect");

	/* open source file */
	if (-1 == (fd = open(fname, O_RDONLY)))
		error_exit("open");

	if (-1 == stat(fname, &statbuf))
		error_exit("stat");
	strncpy(infbuf.name, fname, FILE_NAME_MAXLEN);
	infbuf.size = statbuf.st_size;
	infbuf.mode = statbuf.st_mode;
	md5_file(fname, infbuf.md5);
	
#if DEBUG
	char __tmp[17];
	md5_num2str(infbuf.md5, __tmp);
	printf("name: %s\n", infbuf.name);
	printf("size: %d\n", infbuf.size);
	printf("md5:  %s\n", __tmp);
#endif

	/* send file info to server */
	if (-1 == send(sockfd, &infbuf, sizeof(infbuf), 0))
		error_exit("sendto");

	while (1) {
		if (-1 == (ret = read(fd, buff, FILE_BUFF_SIZE)))
			error_exit("read");
		if (ret == 0)
			break;
		
		if (-1 == send(sockfd, buff, ret, 0))
			error_exit("send");
	}

	close(sockfd);
	close(fd);

	return 0;
}
