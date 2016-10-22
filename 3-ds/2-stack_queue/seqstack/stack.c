#include "stack.h"

stack_t *stack_init(int len)
{
	stack_t *stack;

	stack = malloc(sizeof(*stack));
	stack->data = malloc(sizeof(int) * len);
	stack->top = 0;
	stack->tlen = len;

	return stack;
}

int stack_destroy(stack_t *stack)
{
	free(stack->data);
	free(stack);

	return 0;
}

int stack_push(stack_t *stack, int value)
{
	if (stack_isfull(stack))
		return -1;

	stack->data[stack->top++] = value;
	
	return 0;
}

int stack_isfull(stack_t *stack)
{
	return stack->top >= stack->tlen;
}

#if STACK_DEBUG
void _stack_debug_(stack_t *stack)
{
	int i;
	int *p = stack->data;

	puts("----------------- DEBUG ---------------------");
	printf("Top: %d\tTlen: %d\n", stack->top, stack->tlen);
	for (i = 0; i < stack->top; i++)
		printf("%3d", p[i]);
	putchar('\n');
}
#endif

int stack_pop(stack_t *stack, int *value)
{
	if (stack_isempty(stack))
		return -1;

	*value = stack->data[--stack->top];

	return 0;
}

int stack_isempty(stack_t *stack)
{
	return stack->top <= 0;
}

int stack_getlen(stack_t *stack)
{
	return stack->top;
}

int stack_gettop(stack_t *stack, int *value)
{
	if (stack_isempty(stack))
		return -1;

	*value = stack->data[stack->top-1];

	return 0;
}
