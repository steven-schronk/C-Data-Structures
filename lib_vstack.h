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

#endif /* LIB_VSTACK_H_ */
