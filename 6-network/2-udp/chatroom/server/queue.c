#include "queue.h"

qnode_t *create_qnode(qdata_t *value)
{
	qnode_t *node;

	node = malloc(sizeof(*node));
	if (value != NULL)
		node->data = *value;
	node->next = NULL;

	return node;
}

queue_t *queue_init(int len)
{
	queue_t *queue;

	if (NULL == (queue = malloc(sizeof(*queue))))
		return NULL;
	queue->head = create_qnode(0);
	queue->tail = queue->head;
	queue->tlen = len;
	queue->clen = 0;

	queue->sem = malloc(sizeof(sem_t));
	if (-1 == sem_init(queue->sem, 0, 0)) {
		free(queue->head);
		free(queue);
		return NULL;
	}
	
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
	sem_destroy(queue->sem);
	free(queue->sem);
	free(queue);

	return 0;
}

int queue_enqueue(queue_t *queue, qdata_t *value)
{
	qnode_t *new;
	
	if (queue_isfull(queue))
		return -1;

	new = create_qnode(value);
	queue->tail->next = new;
	queue->tail = new;
	queue->clen++;
	sem_post(queue->sem);

	return 0;
}

int queue_dequeue(queue_t *queue, qdata_t *value)
{
	qnode_t *p = queue->head;
	
//	if (queue_isempty(queue))
//		return -1;
	
	sem_wait(queue->sem);

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

	printf("Head: %p\tTail: %p\tTlen: %d\tClen: %d\n", 
			queue->head, queue->tail, queue->tlen, queue->clen);

}
#endif

