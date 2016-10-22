#ifndef __USERLIST_H__
#define __USERLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userinfo.h"

typedef UserInfo_t LnkData_t;

typedef struct _linknode_ {
	LnkData_t data;
	struct _linknode_ *next;
}UsrNode_t;

typedef struct _linklist_ {
	UsrNode_t *head;
	int clen;
	int tlen;
}UserList_t;

extern UsrNode_t *create_linknode(LnkData_t *value);
extern UserList_t *user_list_init(int len);
extern int user_list_destroy(UserList_t *list);
extern int user_list_insert(UserList_t *list, LnkData_t *value);
extern int user_list_delete(UserList_t *list, LnkData_t *value);
extern UsrNode_t *user_list_search(UserList_t *list, LnkData_t *value);
extern int user_list_getlen(UserList_t *list);
extern int user_list_getall(UserList_t *list, UserInfo_t *user[]);
extern int user_list_getmyinfo(UserList_t *list, UserInfo_t *info);
extern int user_list_setmyinfo(UserList_t *list, UserInfo_t *info);

#endif /* __LINKLIST_H__ */
