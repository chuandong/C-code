#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BUFF_SIZE	1024
#define PORT	10001

int sockfd;
void *thread_sender(void *arg);
void *thread_receiver(void *arg);

int main(int argc, const char **argv)
{
	pthread_t tid_snd;
	pthread_t tid_rcv;
	struct sockaddr_in myaddr;

	if (argc != 2) {
		fprintf(stderr, "invalid arguments !\n");
		fprintf(stderr, "USAGE:\n\t./chat IP\n");
		exit(EXIT_FAILURE);
	}

	if (-1 == inet_addr(argv[1])) {
		fprintf(stderr, "invalid ipaddress !");
		exit(EXIT_FAILURE);
	}

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	if (-1 == bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr))) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (0 != pthread_create(&tid_snd, NULL, thread_sender, (void *)argv[1]))
		exit(EXIT_FAILURE);

	if (0 != pthread_create(&tid_rcv, NULL, thread_receiver, NULL))
		exit(EXIT_FAILURE);

	pthread_join(tid_snd, NULL);
	pthread_join(tid_rcv, NULL);

	return 0;
}

void *thread_sender(void *arg)
{
	struct sockaddr_in peraddr;
	const char *ipaddr = arg;
	char buff[BUFF_SIZE];
	
	peraddr.sin_family = AF_INET;
	peraddr.sin_port = htons(PORT);
	peraddr.sin_addr.s_addr = inet_addr(ipaddr);

	while (1) {
		fgets(buff, BUFF_SIZE, stdin);
		if (-1 == sendto(sockfd, buff, strlen(buff) + 1, 0, 
					(struct sockaddr *)&peraddr, sizeof(peraddr))) {
			perror("sendto");
			exit(EXIT_FAILURE);
		}
	}

	return NULL;

}
void *thread_receiver(void *arg)
{
	struct sockaddr_in peraddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buff[BUFF_SIZE];

	while (1) {
		if (-1 == recvfrom(sockfd, buff, BUFF_SIZE, 0, 
					(struct sockaddr *)&peraddr, &addrlen)) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		printf("\e[1;31m%s:%d\e[0m --> \e[1;32m%s\e[0m\n", inet_ntoa(peraddr.sin_addr),
				ntohs(peraddr.sin_port), buff);
	}
}
