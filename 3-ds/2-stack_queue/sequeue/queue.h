#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_DEBUG	1

typedef struct _sequeue_ {
	int *data;
	int head;
	int tail;
	int tlen;
}queue_t;

extern queue_t *queue_init(int len);
extern int queue_destroy(queue_t *queue);
extern int queue_enqueue(queue_t *queue, int value);
extern int queue_dequeue(queue_t *queue, int *value);
extern int queue_isfull(queue_t *queue);
extern int queue_isempty(queue_t *queue);
extern int queue_getlen(queue_t *queue);
#if QUEUE_DEBUG
extern void _queue_debug_(queue_t *queue);
#endif

#endif	/* __QUEUE_H__ */
