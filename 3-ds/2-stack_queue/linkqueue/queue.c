#include "queue.h"

qnode_t *create_qnode(int value)
{
	qnode_t *node;

	node = malloc(sizeof(*node));
	node->data = value;
	node->next = NULL;

	return node;
}

queue_t *queue_init(int len)
{
	queue_t *queue;

	queue = malloc(sizeof(*queue));
	queue->head = create_qnode(0);
	queue->tail = queue->head;
	queue->tlen = len;
	queue->clen = 0;
	
	return queue;
}

int queue_destroy(queue_t *queue)
{
	qnode_t *p = queue->head;
	qnode_t *tmp;

	while (NULL != p) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(queue);

	return 0;
}

int queue_enqueue(queue_t *queue, int value)
{
	qnode_t *new;
	
	if (queue_isfull(queue))
		return -1;

	new = create_qnode(value);
	queue->tail->next = new;
	queue->tail = new;
	queue->clen++;

	return 0;
}

int queue_dequeue(queue_t *queue, int *value)
{
	qnode_t *p = queue->head;
	
	if (queue_isempty(queue))
		return -1;
	
	queue->head = p->next;
	free(p);

	*value = queue->head->data;
	queue->clen--;

	return 0;
}

int queue_isfull(queue_t *queue)
{
	return queue->clen >= queue->tlen;
}

int queue_isempty(queue_t *queue)
{
	return queue->clen <= 0;
}

int queue_getlen(queue_t *queue)
{
	return queue->clen;
}

#if QUEUE_DEBUG
void _queue_debug_(queue_t *queue)
{
	qnode_t *p = queue->head->next;

	printf("Head: %p\tTail: %p\tTlen: %d\tClen: %d\n", 
			queue->head, queue->tail, queue->tlen, queue->clen);

	while (NULL != p) {
		printf("%3d", p->data);
		p = p->next;
	}
	putchar('\n');
}
#endif

