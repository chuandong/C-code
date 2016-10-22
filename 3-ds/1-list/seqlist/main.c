#include "list.h"	/* the operation of list */
#include <stdio.h>	/* puts */

int main()
{
	list_t *list;
	int value = 10;
	int *p = NULL;
	
	list = list_init(10);
	
	puts("Insert:");
	while (0 == list_insert(list, value))
		value--;
	list_show(list);	

	puts("Delete:");
	list_delete(list, 5);
	list_show(list);

	puts("Modify:");
	list_modify(list, 2, 20);
	list_show(list);

	puts("Search:");
	p = list_search(list, 6);
	if (p == NULL)
		puts("NO");
	else
		printf("%d\n", *p);

	puts("Sort:");
	list_sort(list);
	list_show(list);	

	puts("Reverse:");
	list_reverse(list);
	list_show(list);	

	puts("Destroy:");
	list_destroy(list);

	return 0;
}
