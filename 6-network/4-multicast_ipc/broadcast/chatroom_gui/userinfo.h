#ifndef __USER_INFO_H__
#define __USER_INFO_H__

#define USER_NAME_LEN	64

typedef struct _user_info {
	char user_name[USER_NAME_LEN];
	unsigned int user_addr;
}UserInfo_t;

#endif
