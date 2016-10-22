#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr,
					   cltaddr;

	int i;

	for (i = 0; i < 1000; i++) {
		if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
			error_exit("socket");

		seraddr.sin_family = AF_INET;
		seraddr.sin_port = htons(SER_PORT);
		seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
		if (-1 == connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
			error_exit("connect");

		close(sockfd);
	}

	return 0;
}
