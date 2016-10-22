/*���ܣ� ����UDPʵ����һ���򵥵Ķ��˶Ի����
 *���ߣ� james
 *���ڣ� 2014.9.4
 *�汾�� v1.0
 *˵����������������ն˽�������������ʵ�־��������죬�漰֪ʶ���У� C���ԡ�
 *		�� �̡����磨UDP����
 */

/* ����ͨ�ź�����Ҫ��ͷ�ļ� */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ��׼����������ַ������������������Ҫ��ͷ�ļ� */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define SER_PORT	50000			/* �������Ҫ�󶨵Ķ˿ں� */

#define MESG_NAME_LEN	64		/* ͨ��Э�����û�������󳤶� */
#define MESG_TEXT_LEN	512		/* ͨ��Э�������ݵ���󳤶� */
/* ������Ҫ��ͨ��Э�� */
typedef struct mesg {
	char name[MESG_NAME_LEN];		/* ���� */
	char text[MESG_TEXT_LEN];		/* ���� */
}mesg_t;



/* ��ȡ����ʱ�䲢����һ������õ��ַ��������硰2014-9-4 10:20:40�� */
char *chat_get_time(void);

/* ����ָ������ɫ��ӡ�������ݵı��⣬���硰james@2014-9-4 10:20:40[192.168.1.1]�� */
int chat_print_tittle(const char *usr, const char *date, const char *ip);

/* ����ָ����ɫ��ӡ�������� */
int chat_print_text(const char *text);

/* ������� */
int main(int argc, const char *argv[])
{
	/* ���庯����Ҫ�ľֲ����� */
	int sockfd;
	struct sockaddr_in localaddr;
	struct sockaddr_in peeraddr;
	socklen_t addrlen = sizeof(peeraddr);
	mesg_t msgbuf;
	char name[MESG_NAME_LEN];
	pid_t pid;
	
	/* ����ն˴��Σ��������������ƥ���򱨴��˳� */
	if (argc != 2) {
		fprintf(stderr, "invalid arguments !\n");
		fprintf(stderr, "USAGE:\n\t./chat IP\n");
		exit(EXIT_FAILURE);
	}
	
	/* ��⴫�ݵ�IP��ַ�Ƿ���ȷ */
	if (-1 == inet_addr(argv[1])) {
		fprintf(stderr, "invalid ipaddress !");
		exit(EXIT_FAILURE);
	}
	
	/* �ر�CTL-C ���ܣ���ֹ�û��Ƿ��ر���� */
	signal(SIGINT, SIG_IGN);

	/* ���׽��� */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket");
		return -1;
	}

	/* �󶨱���IP�Ͷ˿ں� */
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(SER_PORT);
	localaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr(SER_ADDR);
	if (-1 == bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr))) {
		perror("bind");
		return -1;
	}

	/* ���뱾�������������ͨ��Э��� */
	puts("enter your name:");
	fgets(name, MESG_NAME_LEN, stdin);
	name[strlen(name)-1] = '\0';	/*ȥ��ĩβ�Ļ��з�*/
	puts("Welcome To Chatroom !\n'#' For Quit.");

	/* �����ӽ��� */
	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}

	/* �ӽ��̸��������Ϣ����ӡ���ն� */
	if (pid == 0) {
		while (-1 != recvfrom(sockfd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&peeraddr, &addrlen)) {
			chat_print_tittle(msgbuf.name, chat_get_time(), inet_ntoa(peeraddr.sin_addr));
			chat_print_text(msgbuf.text);
		}
		/* �������ʧ�ܣ���ɱ�������̲��˳� */
		kill(getppid(), SIGKILL);
		exit(0);

	/* �����̸����ȡ�û����벢���� */
	} else {
		/* ���Է��ĵ�ַ��Ϣ */
		peeraddr.sin_family = AF_INET;
		peeraddr.sin_port = htons(SER_PORT);
		peeraddr.sin_addr.s_addr = inet_addr(argv[1]);
		strcpy(msgbuf.name, name);
		while (1) {
			fgets(msgbuf.text, MESG_TEXT_LEN, stdin);
			msgbuf.text[strlen(msgbuf.text)-1] = '\0';

			/* ����û�������ǡ�#������ɱ���ӽ��̲��˳� */
			if (!strcmp(msgbuf.text, "#")) {
				kill(pid, SIGKILL);
				exit(0);
			}

			/* ���û�����⣬���������� */
			if (-1 == sendto(sockfd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&peeraddr, addrlen)) {
				perror("recvfrom");
				return -1;
			}
		}

	}

	close(sockfd);

	return 0;
}

/* ��ñ��ص�ǰʱ�䣬������һ�����չ̶���ʽ��װ�õ�ʱ���ַ�����
 * ���ڸ��ַ����ھ�̬������ռ䣬��˵���������Ҫ�����ڴ�й©���⣬
 *	��Ҫ�ͷŸÿռ䡣
 */
char *chat_get_time(void)
{
	time_t tm_sec;
	struct tm *tm_buff;
	static char tm_str[128];

	time(&tm_sec);
	tm_buff = localtime(&tm_sec);
	
	sprintf(tm_str, "%d/%d/%d %d:%d:%d", 
			tm_buff->tm_year+1900, tm_buff->tm_mon+1, tm_buff->tm_mday,
			tm_buff->tm_hour, tm_buff->tm_min, tm_buff->tm_sec);

	return tm_str;
}

/* ���û�ָ�����ַ����ֱ��Բ�ͬ����ɫ��װ��ʾ����ӡ���⣩�� */
int chat_print_tittle(const char *usr, const char *date, const char *ip)
{
	printf("\e[1;31m%s\e[0m@\e[1;32m%s\e[34m[%s]\e[0m\n", usr, date, ip);

	return 0;
}

/* ���û�ָ�����ַ�����ĳ����ɫ��ʾ����ӡ���ݣ� */
int chat_print_text(const char *text)
{
	printf("\t\e[1;33m%s\e[0m\n", text);

	return 0;
}
