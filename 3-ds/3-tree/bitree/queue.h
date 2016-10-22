#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include "bitnode.h"

typedef  bitnode_t* qdata_t;

typedef struct _qnode_ {
	qdata_t data;
	struct _qnode_ *next;
}qnode_t;

typedef struct _linkqueue_ {
	qnode_t *head;
	qnode_t *tail;
	int clen;
	int max;
}linkqueue_t;

extern qnode_t *create_qnode(qdata_t value);
extern linkqueue_t *queue_init(int len);
extern int queue_destroy(linkqueue_t *queue);
extern int queue_enqueue(linkqueue_t *queue, qdata_t value);
extern int queue_dequeue(linkqueue_t *queue, qdata_t *value);

#endif	/* __QUEUE_H__ */
