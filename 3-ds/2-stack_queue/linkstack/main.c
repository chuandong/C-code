#include "stack.h"
#include <stdio.h>

int main()
{
	stack_t *stack;
	int value;
	
	stack = stack_init(10);
	
	puts("Push:");
	value = 1;
	while (0 == stack_push(stack, value)) {
		printf("%3d", value);
		value++;
	}
	putchar('\n');

#if STACK_DEBUG
	_stack_debug_(stack);
#endif

	puts("Pop:");
	while (0 == stack_pop(stack, &value))
		printf("%3d", value);
	putchar('\n');

#if STACK_DEBUG
	_stack_debug_(stack);
#endif
	stack_destroy(stack);

	return 0;
}
