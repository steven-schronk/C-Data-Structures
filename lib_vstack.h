#ifndef LIB_VSTACK_H_
#define LIB_VSTACK_H_

#define Stack_Head List_Head
#define Stack_Node List_Node

/* create a new stack */
#define vstack_new() list_new()

/* push node onto stack */
#define vstack_push(pHead) list_ins_head(pHead)

/* push node onto stack - with data */
#define vstack_push_data(pHead, pData) list_ins_head_data(pHead, pData)

/* remove node from stack */
#define vstack_pop(pHead) list_rm_node(pHead, pHead->pNext)

/* view next node in stack */
#define vstack_peek(pHead) pHead->pNext

/* number of elements in stack */
#define vstack_size(pHead) pHead->count

/* empty contents of stack */
#define vstack_clear(pHead) list_clear(pHead)

/* delete and free contents of this queue */
#define vstack_delete(pHead) list_delete(pHead)

/* make a deep copy of list */
#define vstack_copy(pHead) list_copy(pDest, pSrc)

/* print out contents of list to stdout */
#define vstack_print(pHead) list_print(pHead)

/* reverse contents of list */
#define vstack_reverse(pHead) list_reverse(pHead)

/* append high list to last node of low list - does not modify pHi list */
#define vstack_append(pLo, pHi) list_append(pLo, pHi)

/* return an array of pointers to data payload in list - does not modify list */
#define vstack_data_array(pHead, pArr, len) list_data_array(pHead, pArr, len)

/* return an array of pointers to nodes in list - does not modify list */
#define vstack_node_array(pHead, pArr, len) list_node_array(pHead, pArr, len)

#endif /* LIB_VSTACK_H_ */
