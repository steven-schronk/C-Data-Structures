#ifndef LIB_LL_H_
#define LIB_LL_H_

/* return address of next node in list */
#define list_next(element) ((element)->pNext)

/* return address of data in this node */
#define list_data(element) ((element)->pData)

#define list_is_head(list, element) ((element) == (list)->pNext ? 1 : 0)

#define list_is_tail(element) ((element)->pNext == NULL ? 1 : 0)

#define list_head(list) ((list)->pNext)

#define list_size(list) ((list)->count)

typedef struct list_node {
	void *pData;
	struct list_node *pNext;
} List_Node;

typedef struct {
	struct list_node *pNext;
	int count;
} List_Head;

/* create new empty list */
List_Head *list_new(void);

/* completely delete list and return all memory to heap */
void list_delete(List_Head *);

/* Returns length of list
	Returns integer count of number of nodes in list.
	If pointer passed to function is null, returns -1 value.
*/
int list_len(List_Head *);

/* search through list */
List_Node *list_search(List_Head *);

/* return address of end of list */
List_Node *list_tail(List_Head *);

/*print list contents and details */
void list_print(List_Head *);

/* push new node on head of list */
List_Node *list_ins_head(List_Head *);

/* push new node on tail of list */
List_Node *list_ins_tail(List_Head *);

/* insert node before this node in list */
List_Node *list_ins_before(List_Head *, List_Node *);

/* insert node after this node in list */
List_Node *list_ins_after(List_Head *, List_Node *);

/* node remove (by address) */
int list_rm_node(List_Head *pHead, List_Node *);

/* remove next node in list */
int list_rm_next(List_Head *pHead, List_Node *);

int list_rm_before(List_Head *pHead, List_Node *);

/* remove all nodes in list and free memory for each node */
void list_clear(List_Head *);

#endif /* LIB_LL_H_ */
