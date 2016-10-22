#include "head.h"

/* when you try to press CTL+C, remove the socket path before */
void signal_handler(int signo)
{
	remove(SOCK_PATH_SER);
	exit(0);
}

int main()
{
	int sockfd;
	struct sockaddr_un seraddr;
	struct sockaddr_un cltaddr;
	socklen_t addrlen = sizeof(cltaddr);
	char buff[BUFF_SIZE];
	int ret;

	/* capture the CTL+C signal */
	signal(SIGINT, signal_handler);
	
	if (-1 == (sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)))
		error_exit("socket");

	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path, SOCK_PATH_SER);
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");

	while (1) {
		if(-1 == (ret = recvfrom(sockfd, buff, BUFF_SIZE, 0, (struct sockaddr *)&cltaddr, &addrlen)))
			error_exit("recvfrom");

		printf("%s --> %s\n", cltaddr.sun_path, buff);
		
		if (-1 == sendto(sockfd, buff, ret, 0, (struct sockaddr *)&cltaddr, sizeof(cltaddr)))
			error_exit("sendto");
	}

	close(sockfd);
	remove(SOCK_PATH_SER);

	return 0;
}
