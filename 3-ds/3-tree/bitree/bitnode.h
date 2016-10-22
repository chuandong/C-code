#ifndef __BITNODE_H__
#define __BITNODE_H__

typedef struct _bitnode_ {
	int data;
	struct _bitnode_ *lchild;
	struct _bitnode_ *rchild;
}bitnode_t;

#endif	/* __BITNODE_H__ */

