#ifndef __CHAT_PROTOCOL_H__
#define __CHAT_PROTOCOL_H__

#include "userinfo.h"

#define CHAT_TEXT_LEN	512
#define CHAT_TYPE_LOGIN		'I'
#define CHAT_TYPE_LOGOUT	'O'
#define CHAT_TYPE_CHAT		'C'
#define CHAT_TYPE_ACK		'A'

typedef struct _chat_protocol_ {
	int chat_type;
	UserInfo_t chat_user;
	char chat_text[CHAT_TEXT_LEN];
}ChatProto_t;

#endif	/* __CHAT_PROTOCOL_H__ */

