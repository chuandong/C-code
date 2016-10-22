#include "list.h"

list_t *list_init(int len)
{
	list_t *list;

	list = malloc(sizeof(list_t));
	list->head = create_linknode(0);
	list->clen = 0;
	list->mlen = len;

	return list;
}

int list_insert(list_t *list, int value)
{
	lnode_t *new;

	if (list->clen >= list->mlen)
		return -1;

	new = create_linknode(value);
	new->next = list->head->next;
	list->head->next = new;

	list->clen++;

	return 0;
}

lnode_t *create_linknode(int value)
{
	lnode_t *node;

	node = malloc(sizeof(lnode_t));
	node->data = value;
	node->next = NULL;

	return node;
}

int list_show(list_t *list)
{
	lnode_t *p = list->head->next;

	printf("Clen: %d\tMlen: %d\n", list->clen, list->mlen);
	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	putchar('\n');

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

lnode_t *list_search(list_t *list, int target)
{
	lnode_t *p = list->head->next;

	while (NULL != p) {
		if (p->data == target)
			break;
		p = p->next;
	}

	return p;
}

int list_modify(list_t *list, int old, int new)
{
	lnode_t *p = list->head->next;

	while (NULL != p) {
		if (p->data == old)
			break;
		p = p->next;
	}
	if (NULL == p)
		return -1;

	p->data = new;
	return 0;
}

int list_delete(list_t *list, int target)
{
	lnode_t *p = list->head;
	lnode_t *tmp;

	while (NULL != p->next) {
		if (p->next->data == target)
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

int list_reverse(list_t *list)
{
	lnode_t *p = list->head->next;
	lnode_t *tmp;

	list->head->next = NULL;

	while (NULL != p) {
		tmp = p;
		p = p->next;
		tmp->next = list->head->next;
		list->head->next = tmp;
	}

	return 0;
}

int list_sort(list_t *list)
{
	lnode_t *p = list->head->next;
	lnode_t *tmp;
	lnode_t *locat;

	list->head->next = NULL;

	while (NULL != p) {
		tmp = p;
		p = p->next;

		locat = list->head;
		while (NULL != locat->next && locat->next->data < tmp->data)
			locat = locat->next;
		tmp->next = locat->next;
		locat->next = tmp;
	}

	return 0;
}
