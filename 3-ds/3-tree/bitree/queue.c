#include "queue.h"

linkqueue_t *queue_init(int len)
{
	linkqueue_t *queue = NULL;

	queue = malloc(sizeof(*queue));
	queue->head = create_qnode(0);
	queue->tail = queue->head;
	queue->clen = 0;
	queue->max = len;
	
	return queue;
}

int queue_destroy(linkqueue_t *queue)
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

qnode_t *create_qnode(qdata_t value)
{
	qnode_t *node = NULL;

	node = malloc(sizeof(*node));
	node->data = value;
	node->next = NULL;

	return node;
}

int queue_enqueue(linkqueue_t *queue, qdata_t value)
{
	qnode_t *new = NULL;

	if (queue->clen >= queue->max)
		return -1;

	new = create_qnode(value);
	queue->tail->next = new;
	queue->tail = new;

	queue->clen++;

	return 0;
}

int queue_dequeue(linkqueue_t *queue, qdata_t *value)
{
	qnode_t *p = queue->head;

	if (queue->clen <= 0)
		return -1;

	queue->head = p->next;
	free(p);

	*value = queue->head->data;
	queue->clen--;

	return 0;
}
