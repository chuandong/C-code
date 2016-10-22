#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include "bitnode.h"

typedef bitnode_t* stkdata_t;

typedef struct _stknode_ {
	stkdata_t data;
	struct _stknode_ *next;
}stknode_t;

typedef struct _linkstack_ {
	stknode_t *top;
	int clen;
	int max;
}linkstack_t;

extern stknode_t *create_stknode(stkdata_t value);
extern linkstack_t *stack_init(int len);
extern int stack_destroy(linkstack_t *stack);
extern int stack_push(linkstack_t *stack, stkdata_t value);
extern int stack_pop(linkstack_t *stack, stkdata_t *value);
extern int stack_isempty(linkstack_t *stack);
extern int stack_isfull(linkstack_t *stack);

#endif	/* __STACK_H__ */
