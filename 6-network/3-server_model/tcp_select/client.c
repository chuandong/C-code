#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	char buff[BUFF_SIZE];
	int i = 0;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))) 
		error_exit("socket");

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == connect(sockfd, (sa_t*)&seraddr, sizeof(sa_t)))
		error_exit("connect");

	while (1) {
		sprintf(buff, "hellloworld -- %d", i++);
		if (-1 == send(sockfd, buff, strlen(buff)+1, 0))
			error_exit("send");

		memset(buff, 0, BUFF_SIZE);
		if (-1 == recv(sockfd, buff, BUFF_SIZE, 0))
			error_exit("recv");
		printf("RECV: %s\n", buff);

		usleep(1000000);
	}

	close(sockfd);

	return 0;
}
