#include "list.h"

#define N	10

int main()
{
	int data[N] = {1,5,8,3,6,19, 37, 100, 45, 2};
	list_t *list;
	int i;
	
	list = list_init(N);

	for (i = 0; i < N; i++)
		list_insert(list, data[i]);
	list_show(list);

	list_reverse(list);
	list_show(list);
	
	list_sort(list);
	list_show(list);

	list_destroy(list);

	return 0;
}
