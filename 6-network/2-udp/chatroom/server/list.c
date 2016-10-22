#include "list.h"

list_t *list_init(int len)
{
	list_t *list;

	list = malloc(sizeof(list_t));
	list->head = create_linknode(NULL);
	list->clen = 0;
	list->mlen = len;

	return list;
}

int list_insert(list_t *list, ldata_t *value)
{
	lnode_t *new;

	if (list->clen >= list->mlen)
		return -1;

	if (NULL != list_search(list, value))
		return 0;

	new = create_linknode(value);
	new->next = list->head->next;
	list->head->next = new;

	list->clen++;

	return 0;
}

lnode_t *create_linknode(ldata_t *value)
{
	lnode_t *node;

	node = malloc(sizeof(lnode_t));
	if (value != NULL)
		node->data = *value;
	node->next = NULL;

	return node;
}

int list_visit(list_t *list, int (*callback)(void *, ldata_t *), void *arg)
{
	lnode_t *p = list->head->next;

	while (NULL != p) {
		if (0 != callback(arg, &p->data))
			return -1;
		p = p->next;
	}

	return 0;
}

int list_destroy(list_t *list)
{
	lnode_t *p = list->head;
	lnode_t *tmp;

	while (NULL != p) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(list);

	return 0;
}

lnode_t *list_search(list_t *list, ldata_t *target)
{
	lnode_t *p = list->head->next;

	while (NULL != p) {
		if (0 == memcmp(&p->data, target, 8))
			break;
		p = p->next;
	}

	return p;
}

int list_delete(list_t *list, ldata_t *target)
{
	lnode_t *p = list->head;
	lnode_t *tmp;

	while (NULL != p->next) {
		if (0 == memcmp(&p->next->data, target, 8))
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

int list_getlen(list_t *list)
{
	return list->clen;
}
