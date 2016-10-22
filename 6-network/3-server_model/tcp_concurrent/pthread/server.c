#include "head.h"
#include <signal.h>
#include <pthread.h>

int network_init(void);
void *pthread_service(void *arg);

int main()
{
	int sockfd;
	int connfd;
	pthread_t tid;
	pthread_attr_t attr;
	
	sockfd = network_init();
	
	if (0 != (errno = pthread_attr_init(&attr)))
		error_exit("pthread_attr_init");
	if (0 != (errno = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)))
		error_exit("pthread_attr_setdetachstate");
	
	while (1) {
		connfd = accept(sockfd, NULL, NULL);
		pthread_create(&tid, &attr, pthread_service, (void*)connfd);
	}

	return 0;
}

int network_init(void)
{
	int sockfd;
	struct sockaddr_in seraddr;
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = INADDR_ANY;
	if (-1 == bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr))) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	if (-1 == listen(sockfd, 128)) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

void *pthread_service(void *arg)
{
	int connfd = (int)arg;
	char buff[BUFF_SIZE];
	struct sockaddr_in peeraddr;
	socklen_t addrlen = sizeof(peeraddr);

	while (0 < recv(connfd, buff, BUFF_SIZE, 0)) {
		getpeername(connfd, (struct sockaddr*)&peeraddr, &addrlen);
		printf("\e[1;31m%s\e[0m:\e[1;32m%d\e[0m --> \e[1;33m%s\e[0m\n",
				inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port), buff);

		strcat(buff, " --- echo");
		send(connfd, buff, strlen(buff)+1, 0);
	}
	close(connfd);

	pthread_exit(NULL);
	return NULL;
}
