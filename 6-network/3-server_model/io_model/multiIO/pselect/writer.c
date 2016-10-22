#include "head.h"

int main()
{
	int fifd;
	char buff[BUFF_SIZE];
	
	if (-1 == mkfifo(FIFO_NAME, 0666) && errno != EEXIST)
		error_exit("mkfifo");

	if (-1 == (fifd = open(FIFO_NAME, O_WRONLY)))
		error_exit("open");


	while (1) {
		fgets(buff, BUFF_SIZE, stdin);
		if (-1 == write(fifd, buff, strlen(buff)+1))
			error_exit("write");
	}

	return 0;
}
