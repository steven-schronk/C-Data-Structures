#ifndef LIB_VQUEUE_H_
#define LIB_VQUEUE_H_

#define Queue_Head List_Head
#define Queue_Node List_Node

/* create a new queue */
#define vq_new() list_new()

/* add node to queue */
#define vq_enq(pHead) list_ins_head(pHead)

/* remove node from queue */
#define vq_deq(pHead) list_rm_node(pHead, list_tail(pHead))

/* view next node in line */
#define vq_peek(pHead) list_tail(pHead)

/* number of elements in queue */
#define vq_size(pHead) pHead->count

/* empty contents of queue */
#define vq_clear(pHead) list_clear(pHead)

/* delete and free contents of this queue */
#define vq_delete(pHead) list_delete(pHead)

#endif /* LIB_VQUEUE_H_ */
