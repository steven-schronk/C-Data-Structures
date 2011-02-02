#ifndef LIB_LL_H_
#define LIB_LL_H_

typedef struct list_node {
	void *pData;
	struct list_node *pNext;
} List_Node;

typedef struct {
	struct list_node *pNext;
	int count;
} List_Head;

/* return address of next node in list */
#define list_next(element) ((element)->pNext)

/* return address of data in this node */
#define list_data(element) ((element)->pData)

/* test node to determine if it is the head of list */
#define list_is_head(list, element) ((element) == (list)->pNext ? 1 : 0)

/* test node to determine if it is the tail of list */
#define list_is_tail(element) ((element)->pNext == NULL ? 1 : 0)

/* remove next node in list */
#define list_rm_next(list, element) list_rm_node(list, (element)->pNext)

/* return pointer to the head node in the list */
#define list_head(list) ((list)->pNext)

/* return integer value of the size of the list */
#define list_size(list) ((list)->count)

/* create new empty list */
List_Head *list_new(void);

/* completely delete list and return all memory to heap */
void list_delete(List_Head *);

/* returns length of list.
	returns integer count of number of nodes in list.
	if pointer passed to function is null, returns -1 value.
*/
int list_len(List_Head *);

/* search through list for pointer to node*/
int list_search(List_Head *pHead, List_Node *pNode);

/* return address of end of list */
List_Node *list_tail(List_Head *);

/* push new node on head of list */
List_Node *list_ins_head(List_Head *);

/* push new node on head of list - with data */
List_Node *list_ins_head_data(List_Head *pHead, void *Data);

/* push new node on tail of list */
List_Node *list_ins_tail(List_Head *);

/* push new node on tail of list - with data */
List_Node *list_ins_tail_data(List_Head *pHead, void *Data);

/* insert node before this node in list */
List_Node *list_ins_before(List_Head *, List_Node *);

/* insert node after this node in list */
List_Node *list_ins_after(List_Head *, List_Node *);

/* node remove (by address) */
int list_rm_node(List_Head *pHead, List_Node *);

/* remove node before this address if it exists
	returns 1 if ok, -1 list empty or did not contain specified node
*/
int list_rm_before(List_Head *pHead, List_Node *);

/* make a deep copy of list */
int list_copy(List_Head *pDest, List_Head *pSrc);

/* print out contents of list to stdout */
void list_print(List_Head *pHead);

/* get address of node at num - first node is 1 */
List_Node *list_get_num(List_Head *pHead, int count);

/* reverse current nodes - modify pointer to next in each */
int list_node_swap(List_Node *pPrev, List_Node *pCurr);

/* reverse contents of list */
List_Head *list_reverse(List_Head *pHead);

/* append high list to last node of low list - does not modify pHi list */
void list_append(List_Head *pLo, List_Head *pHi);

/* return an array of pointers to data payload in list - does not modify list */
int list_data_array(List_Head *pHead, void *pArr[], int len);

/* return an array of pointers to nodes in list - does not modify list */
int list_node_array(List_Head *pHead, void *pArr[], int len);

/* remove all nodes in list and free memory for each node */
void list_clear(List_Head *);

/* return address of previous node in list
	returns NULL if no node found -- address of node otherwise
*/
List_Node *list_prev_node(List_Head *pHead, List_Node *pNode);

#endif /* LIB_LL_H_ */
