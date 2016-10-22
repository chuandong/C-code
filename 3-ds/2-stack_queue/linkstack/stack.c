#include "stack.h"

stknode_t *create_stknode(int value)
{
	stknode_t *node = NULL;

	node = malloc(sizeof(*node));
	node->data = value;
	node->next = NULL;

	return node;
}

stack_t *stack_init(int len)
{
	stack_t *stack;

	stack = malloc(sizeof(*stack));
	stack->top = create_stknode(0);
	stack->clen = 0;
	stack->tlen = len;

	return stack;
}

int stack_destroy(stack_t *stack)
{
	stknode_t *p = stack->top;
	stknode_t *tmp;

	while (NULL != p) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(stack);

	return 0;
}

int stack_push(stack_t *stack, int value)
{
	stknode_t *node;

	if (stack_isfull(stack))
		return -1;
	
	node = create_stknode(value);
	node->next = stack->top->next;
	stack->top->next = node;
	stack->clen++;

	return 0;
}

int stack_pop(stack_t *stack, int *value)
{
	stknode_t *p = stack->top->next;

	if (stack_isempty(stack))
		return -1;

	*value = p->data;
	stack->top->next = p->next;
	free(p);
	stack->clen--;

	return 0;
}

int stack_isfull(stack_t *stack)
{
	return stack->clen >= stack->tlen;
}

int stack_isempty(stack_t *stack)
{
	return stack->clen <= 0;
}

int stack_getlen(stack_t *stack)
{
	return stack->clen;
}

int stack_gettop(stack_t *stack, int *value)
{
	if (stack_isempty(stack))
		return -1;
	
	*value = stack->top->next->data;

	return 0;
}

#if STACK_DEBUG
void _stack_debug_(stack_t *stack)
{
	stknode_t *p = stack->top->next;

	printf("Tlen: %d\tClen: %d\n", stack->tlen, stack->clen);
	while (NULL != p) {
		printf("%3d", p->data);
		p = p->next;
	}
	putchar('\n');
}
#endif
