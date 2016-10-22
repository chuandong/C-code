#include <stdio.h>
#include <stdlib.h>

typedef struct _seqlist_ {
	int *data;
	int mlen;
	int clen;
}list_t;

list_t *list_init(int len);
int list_insert(list_t *list, int value);
int list_show(list_t *list);
int list_destroy(list_t *list);
int list_modify(list_t *list, int old, int new);
int *list_search(list_t *list, int target);
int list_delete(list_t *list, int target);
int list_reverse(list_t *list);
int list_sort(list_t *list);

int main()
{
	list_t *list;
	int value = 110;
	int *ret;

	list = list_init(10);
	
	while (0 == list_insert(list, value))
		value--;
	list_show(list);

#if 0
	list_modify(list, 200, 50);
	list_show(list);

	ret = list_search(list, 110);
	if (ret == NULL)
		puts("no");
	else
		printf("find: %d\n", *ret);

	list_delete(list, 110);
	list_show(list);

	list_reverse(list);
	list_show(list);
#endif

	list_sort(list);
	list_show(list);

	list_destroy(list);

	return 0;
}

list_t *list_init(int len)
{
	list_t *list;

	list = malloc(sizeof(list_t));
	list->data = malloc(len * sizeof(int));
	list->mlen = len;
	list->clen = 0;

	return list;
}

int list_insert(list_t *list, int value)
{
	if (list->clen >= list->mlen)
		return -1;

	list->data[list->clen] = value;
	list->clen++;

	return 0;
}

int list_show(list_t *list)
{
	int i;

	printf("Clen: %d\tMlen: %d\n", list->clen, list->mlen);
	for (i = 0; i < list->clen; i++)
		printf("%5d", list->data[i]);
	putchar('\n');

	return 0;
}

int list_destroy(list_t *list)
{
	free(list->data);
	free(list);

	return 0;
}

int list_modify(list_t *list, int old, int new)
{
	int i;

	for (i = 0; i < list->clen; i++) {
		if (old == list->data[i])
			break;
	}
	if (i >=list->clen)
		return -1;

	list->data[i] = new;
	return 0;
}

int *list_search(list_t *list, int target)
{
	int i;

	for (i = 0; i < list->clen; i++) {
		if (target == list->data[i])
			return list->data + i;
	}

	return NULL;
}

int list_delete(list_t *list, int target)
{
	int i;

	for (i = 0; i < list->clen; i++) {
		if (target == list->data[i])
			break;
	}
	if (i >= list->clen)
		return -1;

	while (i + 1 < list->clen) {
		list->data[i] = list->data[i + 1];
		i++;
	}
	list->clen--;

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

int list_sort(list_t *list)
{
	int i,j;
	int tmp;
	int n = list->clen - 1;
	int *data = list->data;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i; j++) {
			if (data[j] > data[j + 1]) {
				tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}

	return 0;
}

