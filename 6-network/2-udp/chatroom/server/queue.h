#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "protocol.h"

#define QUEUE_DEBUG	0

typedef proto_t qdata_t;

typedef struct _qnode_ {
	qdata_t data;
	struct _qnode_ *next;
}qnode_t;

typedef struct _linkqueue_ {
	sem_t *sem;
	qnode_t *head;
	qnode_t *tail;
	int clen;
	int tlen;
}queue_t;

extern qnode_t *create_qnode(qdata_t *value);
extern queue_t *queue_init(int len);
extern int queue_destroy(queue_t *queue);
extern int queue_enqueue(queue_t *queue, qdata_t *value);
extern int queue_dequeue(queue_t *queue, qdata_t *value);
extern int queue_isfull(queue_t *queue);
extern int queue_isempty(queue_t *queue);
extern int queue_getlen(queue_t *queue);
#if QUEUE_DEBUG
extern void _queue_debug_(queue_t *queue);
#endif

#endif	/* __QUEUE_H__ */