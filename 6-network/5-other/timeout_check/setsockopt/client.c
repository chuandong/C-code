#include "head.h"

int main()
{
	int sockfd;
	char buff[BUFF_SIZE];
	struct sockaddr_in seraddr;
	struct timeval timout;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		perror("socket");
		return -1;
	}

	timout.tv_sec = 3;
	timout.tv_usec = 0;
	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timout, sizeof(timout)))
		error_exit("setsockopt");

	strcpy(buff, "helloworld");
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	
	while (1) {
		if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0, 
					(struct sockaddr *)&seraddr, sizeof(seraddr))) {
			perror("sendto");
		}
		printf("SEND: %s\n", buff);

		if (-1 == recvfrom(sockfd, buff, BUFF_SIZE, 0, NULL, NULL))
			error_exit("recvfrom");

		printf("RECV: %s\n", buff);
	}

	close(sockfd);

	return 0;
}
