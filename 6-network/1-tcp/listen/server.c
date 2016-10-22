#include "head.h"

int main()
{
	int sockfd,
		connfd;
	struct sockaddr_in seraddr,
					   peraddr;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_exit("socket");
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");

	if (-1 == listen(sockfd, 128))
		error_exit("listen");


	int i = 0;
	while (1) {
		if (-1 == (connfd = accept(sockfd, NULL, NULL)))
			error_exit("accept");
		printf("%d\n", i++);
		close(connfd);
	}
	close(sockfd);

	return 0;
}
