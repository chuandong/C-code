#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define STACK_DEBUG	0

typedef struct _seqstack_ {
	int *data;
	int top;
	int tlen;
}stack_t;

extern stack_t *stack_init(int len);
extern int stack_destroy(stack_t *stack);
extern int stack_push(stack_t *stack, int value);
extern int stack_pop(stack_t *stack, int *value);
extern int stack_isfull(stack_t *stack);
extern int stack_isempty(stack_t *stack);
extern int stack_getlen(stack_t *stack);
extern int stack_gettop(stack_t *stack, int *value);

#if STACK_DEBUG
extern void _stack_debug_(stack_t *stack);
#endif

#endif /* __STACK_H__ */
