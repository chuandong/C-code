#include "head.h"

#define SOCK_PATH_CLT_PREFIX	"sock_"

char sock_path[108];

/* when you try to press CTL+C, remove the socket path before */
void signal_handler(int signo)
{
	remove(sock_path);
	exit(0);
}

int main(int argc, const char *argv[])
{
	int sockfd;
	char buff[BUFF_SIZE];
	struct sockaddr_un cltaddr;
	struct sockaddr_un seraddr;
	int i = 0;

	if (argc != 2) {
		fprintf(stderr, "invalid argument");
		return -1;
	}
	
	strcpy(sock_path, SOCK_PATH_CLT_PREFIX);
	strcat(sock_path, argv[1]);
	
	signal(SIGINT, signal_handler);
	
	if (-1 == (sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)))
		error_exit("socket");

	cltaddr.sun_family = AF_UNIX;
	strcpy(cltaddr.sun_path, sock_path);

	/* if you are not binding, you will not be able to receive messages */
	if (-1 == bind(sockfd, (struct sockaddr *)&cltaddr, sizeof(cltaddr)))
		error_exit("bind");

	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path, SOCK_PATH_SER);
	
	while (1) {
		sprintf(buff, "hello unix --- %d", i++);
		if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0, (struct sockaddr *)&seraddr, sizeof(cltaddr)))
			error_exit("sendto");

		if (-1 == recvfrom(sockfd, buff, BUFF_SIZE, 0, NULL, NULL))
			error_exit("error_exit");
		puts(buff);
		sleep(1);
	}
	close(sockfd);
	remove(SOCK_PATH_CLT);

	return 0;
}
