#include "list.h"

list_t *list_init(int len)
{
	list_t *list = NULL;

	list = malloc(sizeof(list_t));
	list->data = malloc(sizeof(int) * len);
	list->clen = 0;
	list->tlen = len;

	return list;
}

int list_destroy(list_t *list)
{
	free(list->data);
	free(list);

	return 0;
}

int list_insert(list_t *list, int value)
{
	if (list->clen >= list->tlen)
		return -1;

	list->data[list->clen++] = value;

	return 0;
}

int list_show(list_t *list)
{
	int i = 0;

	printf("Clen: %d\tTlen: %d\n", list->clen, list->tlen);
	for (i = 0; i < list->clen; i++)
		printf("%5d", list->data[i]);
	putchar('\n');

	return 0;
}

int list_delete(list_t *list, int target)
{
	int i;

	for (i = 0; i < list->clen; i++) {
		if (list->data[i] == target)
			break;
	}
	if (i >= list->clen)
		return -1;

	while (i+1 < list->clen) {
		list->data[i] = list->data[i+1];
		i++;
	}
	list->clen--;

	return 0;
}

int list_modify(list_t *list, int old, int new)
{
	int i;

	for (i = 0; i < list->clen; i++) {
		if (list->data[i] == old)
			break;
	}
	if (i >= list->clen)
		return -1;

	list->data[i] = new;

	return 0;
}

int *list_search(list_t *list, int target)
{
	int i;

	for (i = 0; i < list->clen; i++) {
		if (list->data[i] == target)
			return list->data + i;
	}

	return NULL;
}

int list_sort(list_t *list)
{
	int i;
	int j;
	int tmp;
	int *p = list->data;
	int n = list->clen - 1;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i; j++) {
			if (p[j] > p[j+1]) {
				tmp = p[j];
				p[j] = p[j+1];
				p[j+1] = tmp;
			}
		}
	}

	return 0;
}

int list_reverse(list_t *list)
{
	int *h = list->data;
	int *t = list->data + list->clen - 1;
	int tmp;
	
	while (h < t) {
		tmp = *h;
		*h = *t;
		*t = tmp;
		h++;
		t--;
	}

	return 0;
}
