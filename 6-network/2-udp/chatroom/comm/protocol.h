#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define PROTO_NAME_LEN	32
#define PROTO_TEXT_LEN	512
#define PROTO_FLAG_LOGIN	'I'
#define PROTO_FLAG_LOGOUT	'O'
#define PROTO_FLAG_TALK	'T'

struct chatroom_protocol {
	int prot_flag;
	char prot_name[PROTO_NAME_LEN];
	char prot_text[PROTO_TEXT_LEN];
};
typedef struct chatroom_protocol proto_t;

#define SER_PORT	50001

#endif
