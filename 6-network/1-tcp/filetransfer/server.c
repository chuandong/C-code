#include "head.h"

int check_file(finfo_t *info);

int main()
{
	int sockfd;
	int connfd;
	struct sockaddr_in seraddr;
	struct sockaddr_in cltaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	int fd;
	finfo_t infbuf; 
	char buff[FILE_BUFF_SIZE];
	int ret;

	/* network init */
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_exit("socket");

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == bind(sockfd, (sa_t *)&seraddr, sizeof(sa_t)))
		error_exit("bind");

	if (-1 == listen(sockfd, 128))
		error_exit("listen");

	while (1) {
		if (-1 == (connfd = accept(sockfd, (sa_t *)&cltaddr, &addrlen)))
			error_exit("accept");

		/* receive file info */
		if (-1 == recv(connfd, &infbuf, sizeof(infbuf), 0))
			error_exit("recv");
		
		printf("%s:%d --> %s[%d]\n", inet_ntoa(cltaddr.sin_addr), 
				ntohs(cltaddr.sin_port), infbuf.name, infbuf.size);

#if DEBUG
	char __buff[17];
	md5_num2str(infbuf.md5, __buff);
	printf("name: %s\n", infbuf.name);
	printf("size: %d\n", infbuf.size);
	printf("md5:  %s\n", __buff);
#endif

		/* create file  */
		if (-1 == (fd = open(infbuf.name, O_WRONLY | O_CREAT | O_TRUNC,
						infbuf.mode & 0777)))
			error_exit("open");

		while (1) {
			if (-1 == (ret = recv(connfd, buff, FILE_BUFF_SIZE, 0)))
				error_exit("recv");
			if (ret == 0)
				break;

			if (-1 == write(fd, buff, ret))
				error_exit("write");
		}
		if (0 != check_file(&infbuf))
			fprintf(stderr, "%s: ERROR!\n", infbuf.name);

		close(fd);
		close(connfd);
	}
	close(sockfd);

	return 0;
}

int check_file(finfo_t *info)
{
	unsigned char md5num[FILE_MD5_MAXLEN];
	
	if (-1 == md5_file(info->name, md5num))
		return -1;

	if (0 != memcmp(info->md5, md5num, FILE_MD5_MAXLEN))
		return -1;

	return 0;
}
