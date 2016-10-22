#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	struct sockaddr_in cltaddr;
	socklen_t addrlen = sizeof(cltaddr);
	char buff[BUFF_SIZE];
	int ret;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		perror("socket");
		return -1;
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr))) {
		perror("bind");
		return -1;
	}

	while (1) {
		if (-1 == (ret = recvfrom(sockfd, buff, BUFF_SIZE, 0, 
					(struct sockaddr *)&cltaddr, &addrlen))) {
			perror("recvfrom");
			return -1;
		}
		printf("%s:%d -> ", inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));
		printf("%s\n", buff);

		getchar();

		if (-1 == sendto(sockfd, buff, ret, 0, (struct sockaddr *)&cltaddr, sizeof(cltaddr)))
			error_exit("sendto");
	}

	close(sockfd);

	return 0;
}
