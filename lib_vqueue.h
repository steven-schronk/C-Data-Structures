#ifndef LIB_VQUEUE_H_
#define LIB_VQUEUE_H_

#define Queue_Head List_Head
#define Queue_Node List_Node

/* create a new queue */
#define vq_new() list_new()

/* add node to queue */
#define vq_enq(pHead) list_ins_head(pHead)

/* push node onto stack - with data */
#define vq_enq_data(pHead, pData) list_ins_head_data(pHead, pData)

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

/* make a deep copy of queue */
#define vq_copy(pDest, pSrc) list_copy(pDest, pSrc)

/* print out contents of queue to stdout */
#define vq_print(pHead) list_print(pHead)

/* reverse contents of list */
#define vq_reverse(pHead) list_reverse(pHead)

/* get address of node at num - first node is 1 */
#define vq_get_num(pHead, count) list_get_num(pHead, count)

/* append high list to last node of low list - does not modify pHi list */
#define vq_append(pLo, pHi) list_append(pLo, pHi)

/* reverse current nodes - modify pointer to next in each */
#define vq_node_swap(pPrev, pCurr) list_node_swap(pPrev, pCurr)

/* return an array of pointers to data payload in list - does not modify list */
#define vq_data_array(pHead, pArr, len) list_data_array(pHead, pArr, len)

/* return an array of pointers to nodes in list - does not modify list */
#define vq_node_array(pHead, pArr, len) list_node_array(pHead, pArr, len)

#endif /* LIB_VQUEUE_H_ */
