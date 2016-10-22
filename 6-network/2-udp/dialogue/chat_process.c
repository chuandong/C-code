/*功能： 基于UDP实现了一个简单的二人对话软件
 *作者： james
 *日期： 2014.9.4
 *版本： v1.0
 *说明：该软件可以在终端界面下允许俩人实现局域网聊天，涉及知识点有： C语言、
 *		进 程、网络（UDP）。
 */

/* 网络通信函数需要的头文件 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* 标准输入输出、字符串处理等其他函数需要的头文件 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define SER_PORT	50000			/* 该软件需要绑定的端口号 */

#define MESG_NAME_LEN	64		/* 通信协议中用户名的最大长度 */
#define MESG_TEXT_LEN	512		/* 通信协议中内容的最大长度 */
/* 聊天需要的通信协议 */
typedef struct mesg {
	char name[MESG_NAME_LEN];		/* 姓名 */
	char text[MESG_TEXT_LEN];		/* 内容 */
}mesg_t;



/* 获取本地时间并返回一个打包好的字符串，例如“2014-9-4 10:20:40” */
char *chat_get_time(void);

/* 按照指定的颜色打印聊天内容的标题，例如“james@2014-9-4 10:20:40[192.168.1.1]” */
int chat_print_tittle(const char *usr, const char *date, const char *ip);

/* 按照指定颜色打印聊天内容 */
int chat_print_text(const char *text);

/* 程序入口 */
int main(int argc, const char *argv[])
{
	/* 定义函数需要的局部变量 */
	int sockfd;
	struct sockaddr_in localaddr;
	struct sockaddr_in peeraddr;
	socklen_t addrlen = sizeof(peeraddr);
	mesg_t msgbuf;
	char name[MESG_NAME_LEN];
	pid_t pid;
	
	/* 检测终端传参，如果参数个数不匹配则报错退出 */
	if (argc != 2) {
		fprintf(stderr, "invalid arguments !\n");
		fprintf(stderr, "USAGE:\n\t./chat IP\n");
		exit(EXIT_FAILURE);
	}
	
	/* 检测传递的IP地址是否正确 */
	if (-1 == inet_addr(argv[1])) {
		fprintf(stderr, "invalid ipaddress !");
		exit(EXIT_FAILURE);
	}
	
	/* 关闭CTL-C 功能，防止用户非法关闭软件 */
	signal(SIGINT, SIG_IGN);

	/* 打开套接字 */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket");
		return -1;
	}

	/* 绑定本地IP和端口号 */
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(SER_PORT);
	localaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr(SER_ADDR);
	if (-1 == bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr))) {
		perror("bind");
		return -1;
	}

	/* 输入本人姓名，并填充通信协议包 */
	puts("enter your name:");
	fgets(name, MESG_NAME_LEN, stdin);
	name[strlen(name)-1] = '\0';	/*去除末尾的换行符*/
	puts("Welcome To Chatroom !\n'#' For Quit.");

	/* 分裂子进程 */
	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}

	/* 子进程负责接收消息并打印到终端 */
	if (pid == 0) {
		while (-1 != recvfrom(sockfd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&peeraddr, &addrlen)) {
			chat_print_tittle(msgbuf.name, chat_get_time(), inet_ntoa(peeraddr.sin_addr));
			chat_print_text(msgbuf.text);
		}
		/* 如果接收失败，则杀死父进程并退出 */
		kill(getppid(), SIGKILL);
		exit(0);

	/* 父进程负责读取用户输入并发送 */
	} else {
		/* 填充对方的地址信息 */
		peeraddr.sin_family = AF_INET;
		peeraddr.sin_port = htons(SER_PORT);
		peeraddr.sin_addr.s_addr = inet_addr(argv[1]);
		strcpy(msgbuf.name, name);
		while (1) {
			fgets(msgbuf.text, MESG_TEXT_LEN, stdin);
			msgbuf.text[strlen(msgbuf.text)-1] = '\0';

			/* 如果用户输入的是‘#’，则杀死子进程并退出 */
			if (!strcmp(msgbuf.text, "#")) {
				kill(pid, SIGKILL);
				exit(0);
			}

			/* 如果没有问题，则正常发送 */
			if (-1 == sendto(sockfd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&peeraddr, addrlen)) {
				perror("recvfrom");
				return -1;
			}
		}

	}

	close(sockfd);

	return 0;
}

/* 获得本地当前时间，并返回一个按照固定格式组装好的时间字符串，
 * 由于该字符串在静态区申请空间，因此调用者无需要考虑内存泄漏问题，
 *	不要释放该空间。
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

/* 将用户指定的字符串分别以不同的颜色封装显示（打印标题）。 */
int chat_print_tittle(const char *usr, const char *date, const char *ip)
{
	printf("\e[1;31m%s\e[0m@\e[1;32m%s\e[34m[%s]\e[0m\n", usr, date, ip);

	return 0;
}

/* 将用户指定的字符串以某种颜色显示（打印内容） */
int chat_print_text(const char *text)
{
	printf("\t\e[1;33m%s\e[0m\n", text);

	return 0;
}
