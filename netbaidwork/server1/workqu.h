#ifndef __WORKQUE_H__
#define __WORKQUE_H__
#include"func.h"
typedef struct tag_node{
	int nd_sockfd;
	struct tag_node *nd_next;
}node_t,*pnode_t;
typedef struct {
	pnode_t que_head,que_tail;
	int que_capcacity;
	int que_size;
	pthread_mutex_t que_mutex;
}que_t,*pque_t;
#endif
