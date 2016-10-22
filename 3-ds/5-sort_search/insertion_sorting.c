#include <stdio.h>
#include <stdlib.h>

typedef struct _linknode_ {
	int data;
	struct _linknode_ *next;
}lnode_t;

lnode_t *create_linknode(int value);
lnode_t *list_init(int len);
int list_show(lnode_t *list);
int list_sort(lnode_t *list);

int main()
{
	lnode_t *head;
	
	head = list_init(10);
	list_show(head);

	list_sort(head);
	list_show(head);

}

lnode_t *list_init(int len)
{
	lnode_t *head;
	int i;
	lnode_t *new;

	head = create_linknode(0);

	for (i = 0; i < len; i++) {
		new = create_linknode(rand() % 100);
		new->next = head->next;
		head->next = new;
	}

	return head;
}

lnode_t *create_linknode(int value)
{
	lnode_t *node;

	node = malloc(sizeof(lnode_t));
	node->data = value;
	node->next = NULL;

	return node;
}

int list_show(lnode_t *head)
{
	lnode_t *p = head->next;

	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	putchar('\n');

	return 0;
}

int list_sort(lnode_t *head)
{
	lnode_t *p = head->next;
	lnode_t *tmp;
	lnode_t *locat;

	head->next = NULL;

	while (NULL != p) {
		tmp = p;
		p = p->next;

		locat = head;
		while (NULL != locat->next && locat->next->data < tmp->data)
			locat = locat->next;
		tmp->next = locat->next;
		locat->next = tmp;
	}

	return 0;
}
