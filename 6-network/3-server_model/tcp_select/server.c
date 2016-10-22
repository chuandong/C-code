#include "head.h"
#include <sys/select.h>

void do_service(int sockfd, fd_set *fds);

int main()
{
	int sockfd;
	int connfd;
	struct sockaddr_in seraddr;
	struct sockaddr_in cltaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	
	fd_set rdfds;
	fd_set tmpfds;
	int maxfd;
	int ifd;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_exit("socket");

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == bind(sockfd, (sa_t *)&seraddr, sizeof(sa_t)))
		error_exit("bind");

	if (-1 == listen(sockfd, 128))
		error_exit("listen");

	FD_ZERO(&rdfds);
	FD_SET(sockfd, &rdfds);
	maxfd = sockfd;
	tmpfds = rdfds;
	
	while (1) {
		rdfds = tmpfds;
		if (-1 == select(maxfd + 1, &rdfds, NULL, NULL, NULL))
			error_exit("select");
		
		if (FD_ISSET(sockfd, &rdfds)) {
			if (-1 == (connfd = accept(sockfd, (sa_t *)&cltaddr, &addrlen)))
				perror("accept");
			printf("\e[1;32mACCEPT  --> %s:%d\e[0m\n", inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));
			FD_SET(connfd, &tmpfds);
			maxfd = connfd > maxfd ? connfd : maxfd;
		}

		for (ifd = sockfd+1; ifd <= maxfd; ifd++) {
			if (FD_ISSET(ifd, &rdfds))
				do_service(ifd, &tmpfds);
		}
	}
}

void do_service(int fd, fd_set *pfds)
{
	int ret;
	char buff[BUFF_SIZE];
	struct sockaddr_in cltaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	if (0 >= (ret = recv(fd, buff, BUFF_SIZE, 0))) {
		getpeername(fd, (sa_t *)&cltaddr, &addrlen);
		printf("\e[1;31mCLOSE  --> %s:%d\e[0m\n", inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));

		FD_CLR(fd, pfds);
		close(fd);
	}
	if (-1 == send(fd, buff, ret, 0)) {
		FD_CLR(fd, pfds);
		close(fd);	
	}

}
