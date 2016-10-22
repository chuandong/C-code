#include "userlist.h"

UserList_t *user_list_init(int len)
{
	UserList_t *list = NULL;
	UserInfo_t info;

	list = malloc(sizeof(UserList_t));
	list->head = create_linknode(&info);
	list->clen = 0;
	list->tlen = len;

	return list;
}

int user_list_insert(UserList_t *list, LnkData_t *value)
{
	UsrNode_t *new = NULL;
	UsrNode_t *p = list->head;

	if (list->clen >= list->tlen)
		return -1;

	if (NULL != user_list_search(list, value))
		return 0;

	new = create_linknode(value);
	new->next = p->next;
	p->next = new;

	list->clen++;

	return 0;
}

UsrNode_t *create_linknode(LnkData_t *value)
{
	UsrNode_t *node = NULL;

	node = malloc(sizeof(UsrNode_t));
	memcpy(&node->data, value, sizeof(*value));
	node->next = NULL;

	return node;
}

int user_list_destroy(UserList_t *list)
{
	UsrNode_t *p = list->head;
	UsrNode_t *tmp = NULL;

	while (NULL != p) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(list);

	return 0;
}

int user_list_delete(UserList_t *list, LnkData_t *obj)
{
	UsrNode_t *p = list->head;
	UsrNode_t *tmp = NULL;

	while (NULL != p->next) {
//		if (0 == memcmp(&p->next->data, obj, sizeof(*obj)))
		if (p->data.user_addr == obj->user_addr)
			break;
		p = p->next;
	}
	if (NULL == p->next)
		return -1;

	tmp = p->next;
	p->next = tmp->next;
	free(tmp);

	list->clen--;

	return 0;
}

UsrNode_t *user_list_search(UserList_t *list, LnkData_t *obj)
{
	UsrNode_t *p = list->head->next;

	while (NULL != p) {
//		if (0 == memcmp(&p->data, obj, sizeof(*obj)))
		if (p->data.user_addr == obj->user_addr)
			break;
		p = p->next;
	}

	return p;
}

int user_list_getall(UserList_t *list, UserInfo_t *user[])
{
	UsrNode_t *p = list->head->next;
	int i = 0;

	while (NULL != p) {
		user[i++] = &p->data;
		p = p->next;
	}

	return i;
}

int user_list_getlen(UserList_t *list)
{
	return list->clen;
}

int user_list_setmyinfo(UserList_t *list, UserInfo_t *info)
{
	list->head->data = *info;

	return 0;
}

int user_list_getmyinfo(UserList_t *list, UserInfo_t *info)
{
	*info = list->head->data;

	return 0;
}

