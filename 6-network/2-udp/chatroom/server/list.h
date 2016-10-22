#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

typedef struct sockaddr_in ldata_t;

typedef struct _linknode_ {
	ldata_t data;
	struct _linknode_ *next;
}lnode_t;

typedef struct _linklist_ {
	lnode_t *head;
	int clen;
	int mlen;
}list_t;

extern lnode_t *create_linknode(ldata_t *value);
extern list_t *list_init(int len);
extern int list_insert(list_t *list, ldata_t *value);
extern int list_visit(list_t *list, int (*callback)(void *, ldata_t *), void *arg);
extern int list_destroy(list_t *list);
extern lnode_t *list_search(list_t *list, ldata_t *target);
extern int list_delete(list_t *list, ldata_t *target);
extern int list_getlen(list_t *list);

/* callback for list_visit
 *	int callback(void *arg, ldata_t *addr);
 *	arg: it`s just a copy from the 3th argument of list_visit.
 *	data: the each ipaddr of list.
 */

#endif /* __LIST_H__ */
