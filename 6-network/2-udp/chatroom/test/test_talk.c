#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "protocol.h"

/* public resource */
int sockfd;
char myname[PROTO_NAME_LEN];
struct sockaddr_in seraddr;

void *thread_sender(void *arg);
void *thread_receiver(void *arg);

void user_login();
void user_logout();

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

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	user_login();

	signal(SIGINT, SIG_IGN);

	if (0 != pthread_create(&tid_snd, NULL, thread_sender, NULL))
		exit(EXIT_FAILURE);

	if (0 != pthread_create(&tid_rcv, NULL, thread_receiver, NULL))
		exit(EXIT_FAILURE);

	pthread_join(tid_snd, NULL);
	pthread_join(tid_rcv, NULL);

	return 0;
}

void *thread_sender(void *arg)
{
	proto_t msgbuf;
	int i = 0;
	
	while (1) {
		msgbuf.prot_flag = PROTO_FLAG_TALK; 
		strcpy(msgbuf.prot_name, myname);

		snprintf(msgbuf.prot_text, PROTO_TEXT_LEN, "helloworld ---- %d", i++);

		if (0 == strcmp(msgbuf.prot_text, "#q"))
			user_logout();

		if (-1 == sendto(sockfd, &msgbuf, sizeof(msgbuf), 0, 
					(struct sockaddr *)&seraddr, sizeof(seraddr))) {
			perror("sendto");
			exit(EXIT_FAILURE);
		}
		usleep(10000);
	}

	return NULL;

}
void *thread_receiver(void *arg)
{
	proto_t msgbuf;
	int i = 0;

	while (1) {
		if (-1 == recvfrom(sockfd, &msgbuf, sizeof(msgbuf), 0, NULL, NULL)) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		printf("%d\r", i++);

	}
}

void user_login()
{
	static int i = 0;
	proto_t msgbuf;
	
	sprintf(msgbuf.prot_name, "james%d", i++);

	msgbuf.prot_flag = PROTO_FLAG_LOGIN; 
	strcpy(msgbuf.prot_name, myname);

	if (-1 == sendto(sockfd, &msgbuf, sizeof(msgbuf), 0, 
				(struct sockaddr *)&seraddr, sizeof(seraddr))) {
		perror("sendto");
		exit(EXIT_FAILURE);
	}
	
}

void user_logout()
{
	proto_t msgbuf;

	msgbuf.prot_flag = PROTO_FLAG_LOGOUT; 
	strcpy(msgbuf.prot_name, myname);

	if (-1 == sendto(sockfd, &msgbuf, sizeof(msgbuf), 0, 
				(struct sockaddr *)&seraddr, sizeof(seraddr))) {
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
