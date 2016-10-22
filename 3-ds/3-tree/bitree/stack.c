#include "stack.h"

linkstack_t *stack_init(int len)
{
	linkstack_t *stack = NULL;

	stack = malloc(sizeof(*stack));
	stack->top = create_stknode(0);
	stack->clen = 0;
	stack->max = len;
	
	return stack;
}

int stack_destroy(linkstack_t *stack)
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

stknode_t *create_stknode(stkdata_t value)
{
	stknode_t *node = NULL;
	
	node = malloc(sizeof(*node));
	node->data = value;
	node->next = NULL;

	return node;
}

int stack_push(linkstack_t *stack, stkdata_t value)
{
	stknode_t *new = NULL;

	if (stack->clen >= stack->max)
		return -1;

	new = create_stknode(value);
	new->next = stack->top->next;
	stack->top->next = new;

	stack->clen++;

	return 0;
}

int stack_pop(linkstack_t *stack, stkdata_t *value)
{
	stknode_t *p = stack->top->next;
	
	if (stack->clen <= 0)
		return -1;

	*value = p->data;
	stack->top->next = p->next;
	free(p);

	stack->clen--;

	return 0;
}

int stack_isfull(linkstack_t *stack)
{
	return stack->clen >= stack->max;
}

int stack_isempty(linkstack_t *stack)
{
	return stack->clen <= 0;
}
