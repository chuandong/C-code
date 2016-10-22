#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	char buff[BUFF_SIZE];
	int i;

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == connect(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr))) {
		perror("connect");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (1) {
		sprintf(buff, "helloworld%3d", i++);
		send(sockfd, buff, strlen(buff)+1, 0);
		recv(sockfd, buff, BUFF_SIZE, 0);
		printf("\e[1;3%dm%s\e[0m\n", i % 8, buff);
		sleep(1);
	}

	close(sockfd);

	return 0;
}
