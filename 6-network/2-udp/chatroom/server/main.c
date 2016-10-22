#include "protocol.h"
#include "queue.h"
#include "list.h"

#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_DEBUG 0

/* limit */
#define MSGQUE_LEN_MAX	(1 << 20)
#define ADDRLIST_LEN_MAX	(1 << 20)

/* public resource */
queue_t *msgque;
list_t *addrlist;
int sockfd;

/* daemon */
void become_daemon(void);

/* thread handler */
void *thread_sender(void *arg);
void *thread_receiver(void *arg);

/* the callback for list_visit */
int callback(void *arg, ldata_t *addr);

int main()
{
	pthread_t tid_snd;
	pthread_t tid_rcv;
	struct sockaddr_in localaddr;

#if ! SERVER_DEBUG
	become_daemon();
#endif
	
	/* network_init */
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(SER_PORT);
	localaddr.sin_addr.s_addr = INADDR_ANY;
	if (-1 == bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr))) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	addrlist = list_init(ADDRLIST_LEN_MAX);
	msgque = queue_init(MSGQUE_LEN_MAX);


	if (0 != pthread_create(&tid_snd, NULL, thread_sender, NULL))
		exit(EXIT_FAILURE);
	if (0 != pthread_create(&tid_rcv, NULL, thread_receiver, NULL))
		exit(EXIT_FAILURE);

#if SERVER_DEBUG
	while (1) {
		char cmd[16];
		fgets(cmd, 16, stdin);
		if (0 == strcmp(cmd, "#quit\n"))
			goto System_Quit;
	}

System_Quit:
	pthread_cancel(tid_snd);
	pthread_cancel(tid_rcv);
#endif

	pthread_join(tid_snd, NULL);
	pthread_join(tid_rcv, NULL);
	
	queue_destroy(msgque);
	list_destroy(addrlist);
	close(sockfd);

	return 0;
}

void *thread_receiver(void *arg)
{
	proto_t probuf;
	struct sockaddr_in cltaddr;
	socklen_t addrlen = sizeof(cltaddr);
	
	while (1) {
		if (-1 == recvfrom(sockfd, &probuf, sizeof(proto_t), 0,
				(struct sockaddr *)&cltaddr, &addrlen)) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		switch (probuf.prot_flag) {
		case PROTO_FLAG_TALK:
			queue_enqueue(msgque, &probuf);
#if SERVER_DEBUG && QUEUE_DEBUG
			_queue_debug_(msgque);
#endif
			break;
		case PROTO_FLAG_LOGIN:
			list_insert(addrlist, &cltaddr);
#if SERVER_DEBUG
			printf("[%d]%s LogIn !\n", list_getlen(addrlist), probuf.prot_name);
#endif
			sprintf(probuf.prot_text, "%s LogIn !", probuf.prot_name);
			strcpy(probuf.prot_name, "#System");
			queue_enqueue(msgque, &probuf);
			break;
		case PROTO_FLAG_LOGOUT:
			list_delete(addrlist, &cltaddr);
#if SERVER_DEBUG
			printf("[%d]%s LogOut !\n", list_getlen(addrlist), probuf.prot_name);
#endif
			
			sprintf(probuf.prot_text, "%s LogOut !", probuf.prot_name);
			strcpy(probuf.prot_name, "#System");
			queue_enqueue(msgque, &probuf);
			break;
		}
	}
}

void *thread_sender(void *arg)
{
	proto_t msgbuf;
	
	while (1) {
		queue_dequeue(msgque, &msgbuf);
		list_visit(addrlist, callback, &msgbuf);
	}

	return 0;
}

int callback(void *arg, ldata_t *addr)
{
	proto_t *msgbuf = arg;

	if (-1 == sendto(sockfd, msgbuf, sizeof(proto_t), 0, 
				(struct sockaddr *)addr, sizeof(ldata_t)))
		return -1;
	return 0;
}

void become_daemon(void)
{
	pid_t pid;
	int maxfileno;
	int fd;

	if (-1 == (pid = fork())) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid > 0) 
		exit(EXIT_SUCCESS);

	if (-1 == setsid()) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	chdir("/");
	umask(0);

	maxfileno = getdtablesize();
	for (fd = 0; fd < maxfileno; fd ++)
		close(fd);
	
	return ;
}
