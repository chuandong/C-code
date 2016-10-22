#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "network.h"
#include "userlist.h"
#include "chatproto.h"
#include "window.h"

#define CHAT_MAX_USER	200
	
Network_t *net;
UserList_t *user;
Window_t *win;

void *chat_pthread_snd(void *arg);
void *chat_pthread_rcv(void *arg);

void chat_system_quit(void);
int chat_system_login(void);

char *chat_get_timestr(void);
int chat_get_myinfo(UserInfo_t *info);

int chat_user_show_online(void);
int chat_user_login(ChatProto_t *msgbuf);
int chat_user_chat(ChatProto_t *msgbuf);
int chat_user_logout(ChatProto_t *msgbuf);
int chat_user_ack(ChatProto_t *msgbuf);

int main()
{
	pthread_t tid_rcv;
	pthread_t tid_snd;

	net = network_init();
	user = user_list_init(CHAT_MAX_USER);
	
	if (-1 == chat_system_login()) {
		window_error();
		exit(0);
	}
	
	win = window_init();
//	chat_user_search();


	pthread_create(&tid_rcv, NULL, chat_pthread_rcv, NULL);
	pthread_create(&tid_snd, NULL, chat_pthread_snd, NULL);

	pthread_join(tid_rcv, NULL);
	pthread_join(tid_snd, NULL);

	chat_system_quit();

	return 0;
}

void chat_system_quit(void)
{
	network_destroy(net);
	user_list_destroy(user);	
	window_destroy(win);
	exit(0);
}

int chat_get_myinfo(UserInfo_t *info)
{
	user_list_getmyinfo(user, info);

	return 0;
}

char *chat_get_timestr(void)
{
	time_t tm_sec;
	struct tm *tm_buf;
	static char tm_str[128];

	time(&tm_sec);
	tm_buf = localtime(&tm_sec);

	sprintf(tm_str, "%d/%d/%d %d:%d:%d", 
			tm_buf->tm_year+1900, tm_buf->tm_mon+1, tm_buf->tm_mday,
			tm_buf->tm_hour, tm_buf->tm_min, tm_buf->tm_sec);

	return tm_str;
}

char *chat_get_addr(void)
{
	struct sockaddr_in addr;
	unsigned int ipv4;

	net_getipaddr(NET_DEV_NAME, &ipv4);
	addr.sin_addr.s_addr = ipv4;
	return inet_ntoa(addr.sin_addr);
}

void *chat_pthread_snd(void *arg)
{
	ChatProto_t msgbuf;
	
	msgbuf.chat_type = CHAT_TYPE_CHAT;
	chat_get_myinfo(&msgbuf.chat_user);
	
	while (1) {
		window_gets(win, msgbuf.chat_text, CHAT_TEXT_LEN);
		if (0 == strcmp(msgbuf.chat_text, "#")) {
			msgbuf.chat_type = CHAT_TYPE_LOGOUT;
			network_broadcast(net, &msgbuf, sizeof(msgbuf));
			chat_system_quit();
		}
			
		network_broadcast(net, &msgbuf, sizeof(msgbuf));
	}
	return NULL;
}

void *chat_pthread_rcv(void *arg)
{
	ChatProto_t msgbuf;
	
	while (1) {
		network_recv(net, &msgbuf, sizeof(msgbuf));

		switch (msgbuf.chat_type) {
		case CHAT_TYPE_CHAT:
			chat_user_chat(&msgbuf);
			break;
		case CHAT_TYPE_LOGIN:
			chat_user_login(&msgbuf);
			break;
		case CHAT_TYPE_LOGOUT:
			chat_user_logout(&msgbuf);
			break;
		case CHAT_TYPE_ACK:
			chat_user_ack(&msgbuf);
			break;
		default:
			break;
		}
	}

	return NULL;
}

int chat_system_login(void)
{
	WindowPasswd_t pwd;
	ChatProto_t chatbuf;
	UserInfo_t info;

	window_login(&pwd);
	if (0 != strcmp(pwd.pwd_passwd, "1"))
		return -1;
	
	strcpy(info.user_name, pwd.pwd_name);
	net_getipaddr(NET_DEV_NAME, &info.user_addr);
	user_list_setmyinfo(user, &info);

	memset(&chatbuf, 0, sizeof(chatbuf));
	chatbuf.chat_type = CHAT_TYPE_LOGIN;
	chat_get_myinfo(&chatbuf.chat_user);
	network_broadcast(net, &chatbuf, sizeof(chatbuf));
	
	return 0;
}

int chat_user_show_online(void)
{
	UserInfo_t *infos[CHAT_MAX_USER];
	const char *list[CHAT_MAX_USER];
	int n;
	int i;
	
	user_list_getall(user, infos);
	n = user_list_getlen(user);

	for (i = 0; i < n; i++)
		list[i] = infos[i]->user_name;
	
	window_show_list(win, list, n);

	return 0;
}


int chat_user_chat(ChatProto_t *buf)
{
	ChatProto_t msgbuf = *buf;

	window_show_title(win, msgbuf.chat_user.user_name,
			chat_get_timestr(), inet_ntoa(*(struct in_addr *)&msgbuf.chat_user.user_addr));
	window_show_text(win, msgbuf.chat_text);

	return 0;
}

int chat_user_login(ChatProto_t *buf)
{
	ChatProto_t msgbuf = *buf;

	window_show_title(win, "system", chat_get_timestr(), 
			chat_get_addr());
	sprintf(msgbuf.chat_text, "%s Login !", msgbuf.chat_user.user_name);
	window_show_text(win, msgbuf.chat_text);
	user_list_insert(user, &msgbuf.chat_user);
	chat_user_show_online();

	memset(&msgbuf, 0, sizeof(msgbuf));
	msgbuf.chat_type = CHAT_TYPE_ACK;
	chat_get_myinfo(&msgbuf.chat_user);
	network_broadcast(net, &msgbuf, sizeof(msgbuf));

	return 0;
}

int chat_user_logout(ChatProto_t *buf)
{
	ChatProto_t msgbuf = *buf;

	window_show_title(win, "system", chat_get_timestr(), 
			chat_get_addr());
	sprintf(msgbuf.chat_text, "%s Logout !", msgbuf.chat_user.user_name);
	window_show_text(win, msgbuf.chat_text);
	user_list_delete(user, &msgbuf.chat_user);
	chat_user_show_online();

	return 0;
}

int chat_user_ack(ChatProto_t *buf)
{
	ChatProto_t msgbuf = *buf;

	user_list_insert(user, &msgbuf.chat_user);
	chat_user_show_online();

	return 0;
}
