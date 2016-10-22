#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _linknode_ {
	int data;
	struct _linknode_ *next;
}lnode_t;

typedef struct _linklist_ {
	lnode_t *head;
	int clen;
	int mlen;
}list_t;

extern lnode_t *create_linknode(int value);
extern list_t *list_init(int len);
extern int list_insert(list_t *list, int value);
extern int list_show(list_t *list);
extern int list_destroy(list_t *list);
extern lnode_t *list_search(list_t *list, int target);
extern int list_modify(list_t *list, int old, int new);
extern int list_delete(list_t *list, int target);
extern int list_reverse(list_t *list);
extern int list_sort(list_t *list);

#endif /* __LIST_H__ */
