#include "head.h"
#include <sys/time.h>

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

	fd_set rdfds;
	fd_set tmpfds;
	struct timeval tmval;
	int ret;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		perror("socket");
		return -1;
	}

	strcpy(buff, "helloworld");
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	
	FD_ZERO(&rdfds);
	FD_SET(sockfd, &rdfds);
	tmpfds = rdfds;
		

	while (1) {
		if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0, 
					(struct sockaddr *)&seraddr, sizeof(seraddr))) {
			perror("sendto");
		}
		printf("SEND: %s\n", buff);

		tmval.tv_sec = 3;
		tmval.tv_usec = 0;
		rdfds = tmpfds;
		ret = select(sockfd+1, &rdfds, NULL, NULL, &tmval);
		if (ret == -1)
			error_exit("select");
		else if (ret == 0) {
			fprintf(stderr, "time out !!\n");
//			exit(0);
		}

		if (FD_ISSET(sockfd, &rdfds)) {
			if (-1 == recvfrom(sockfd, buff, BUFF_SIZE, 0, NULL, NULL))
				error_exit("recvfrom");
			printf("RECV: %s\n", buff);
		}

	}

	close(sockfd);

	return 0;
}
