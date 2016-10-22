#include "head.h"
#include <sys/time.h>

int main()
{
	int fifd;
	char buff[BUFF_SIZE];
	fd_set rdfds,
		   tmpfds;
	int maxfd;
	struct timeval timout;
	int ret;
	
	if (-1 == mkfifo(FIFO_NAME, 0666) && errno != EEXIST)
		error_exit("mkfifo");

	if (-1 == (fifd = open(FIFO_NAME, O_RDONLY)))
		error_exit("open");

	FD_ZERO(&rdfds);
	FD_SET(0, &rdfds);
	FD_SET(fifd, &rdfds);
	tmpfds = rdfds;
	maxfd = fifd;

	while (1) {
		rdfds = tmpfds;
		timout.tv_sec = 3;
		timout.tv_usec = 0;
		if (-1 == (ret = select(maxfd + 1, &rdfds, NULL, NULL, &timout)))
			error_exit("select");
		if (ret == 0)
			fprintf(stderr, "time out !\n");

		if (FD_ISSET(0, &rdfds)) {
			fgets(buff, BUFF_SIZE, stdin);
			printf("STDIN: %s", buff);
		}

		if (FD_ISSET(fifd, &rdfds)) {
			memset(buff, 0, BUFF_SIZE);
			if (-1 == read(fifd, buff, BUFF_SIZE))
				error_exit("read");
			printf("FIFO: %s\n", buff);
		}
	}

	return 0;
}
