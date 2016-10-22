#include "head.h"

void timeout_handler(int signo)
{
	fprintf(stderr, "time out !!\n");
	exit(0);
}

int main()
{
	int sockfd;
	char buff[BUFF_SIZE];
	struct sockaddr_in seraddr;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		perror("socket");
		return -1;
	}

	strcpy(buff, "helloworld");
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	
	signal(SIGALRM, timeout_handler);

	while (1) {
		if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0, 
					(struct sockaddr *)&seraddr, sizeof(seraddr))) {
			perror("sendto");
		}
		alarm(3);
		printf("SEND: %s\n", buff);

		if (-1 == recvfrom(sockfd, buff, BUFF_SIZE, 0, NULL, NULL))
			error_exit("recvfrom");
		alarm(0);

		printf("RECV: %s\n", buff);
	}

	close(sockfd);

	return 0;
}
