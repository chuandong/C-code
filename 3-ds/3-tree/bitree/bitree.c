#include <stdio.h>
#include <stdlib.h>
#include "bitnode.h"
#include "queue.h"
#include "stack.h"

bitnode_t *create_bitnode(int value);
bitnode_t *bitree_init(int start, int end);
int bitree_destroy(bitnode_t *root);
int bitree_preorder(bitnode_t *root);
int bitree_inorder(bitnode_t *root);
int bitree_postorder(bitnode_t *root);
int bitree_getheight(bitnode_t *root);
int bitree_nuorder(bitnode_t *root);

int main()
{
	bitnode_t *root = NULL;
	int ret;
	
	root = bitree_init(1, 10);

	puts("PreOrder:");
	bitree_preorder(root);
	putchar(10);

	puts("InOrder:");
	bitree_inorder(root);
	putchar(10);

	puts("PostOrder:");
	bitree_postorder(root);
	putchar(10);

	puts("NuOrder:");
	bitree_nuorder(root);
	putchar(10);

	ret = bitree_getheight(root);
	printf("%d\n", ret);
	
	bitree_destroy(root);

	return 0;
}

bitnode_t *create_bitnode(int value)
{
	bitnode_t *node = NULL;

	node = malloc(sizeof(*node));
	node->data = value;
	node->lchild = NULL;
	node->rchild = NULL;

	return node;
}

bitnode_t *bitree_init(int start, int end)
{
	bitnode_t *root = NULL;

	if (start > end)
		return NULL;

	root = create_bitnode(start);
	root->lchild = bitree_init(start * 2, end);
	root->rchild = bitree_init(start * 2 + 1, end);

	return root;
}

#if 0
int bitree_preorder(bitnode_t *root)
{
	if (root == NULL)
		return -1;

	printf("%5d", root->data);
	bitree_preorder(root->lchild);
	bitree_preorder(root->rchild);

	return 0;
}
//#else

int bitree_preorder(bitnode_t *root)
{
	linkstack_t *stack = NULL;

	stack = stack_init(10);
	stack_push(stack, root);

	while (!stack_isempty(stack)) {
		if (root != NULL) {
			printf("%5d", root->data);
			stack_push(stack, root);
			root = root->lchild;
		} else {
			stack_pop(stack, &root);
			root = root->rchild;
		}
	}

	stack_destroy(stack);

	return 0;
}

#endif

/* from kangpan@farsight 2014.9.25 */
int bitree_preorder(bitnode_t *root)
{
	linkstack_t *stack = NULL;

	stack = stack_init(10);
	stack_push(stack, root);

	while (!stack_isempty(stack)) {
		stack_pop(stack, &root);
		printf("%5d", root->data);
		if (root->rchild != NULL)
			stack_push(stack, root->rchild);
		if (root->lchild != NULL)
			stack_push(stack, root->lchild);
	}

	stack_destroy(stack);

	return 0;
}

int bitree_inorder(bitnode_t *root)
{
	if (NULL == root)
		return -1;

	bitree_inorder(root->lchild);
	printf("%5d", root->data);
	bitree_inorder(root->rchild);

	return 0;
}

int bitree_postorder(bitnode_t *root)
{
	if (NULL == root)
		return -1;

	bitree_postorder(root->lchild);
	bitree_postorder(root->rchild);
	printf("%5d", root->data);

	return 0;
}

int bitree_destroy(bitnode_t *root)
{
	if (NULL == root)
		return -1;
	
	bitree_destroy(root->lchild);
	bitree_destroy(root->rchild);
	free(root);

	return 0;
}

int bitree_getheight(bitnode_t *root)
{
	static int n = 0;
	static int max = 0;

	if (NULL == root)
		return max;
	
	n++;
	max = max > n ? max : n;
	bitree_getheight(root->lchild);
	bitree_getheight(root->rchild);
	n--;

	return max;
}

int bitree_nuorder(bitnode_t *root)
{	
	linkqueue_t *queue = NULL;

	queue = queue_init(10);
	queue_enqueue(queue, root);

	while (0 == queue_dequeue(queue, &root)) {
		printf("%5d", root->data);
		if (NULL != root->lchild)
			queue_enqueue(queue, root->lchild);
		if (NULL != root->rchild)
			queue_enqueue(queue, root->rchild);
	}

	queue_destroy(queue);

	return 0;
}
