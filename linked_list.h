#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct node Node;

struct node
{
	void *pData;
	Node *pNext;
};

typedef struct head Head;

struct head
{
	int count;
	Node *pNode;
};

/* create a new empty list */
Head *list_new();

/* delete list and free memory */
int list_delete(Head *pHead);

/* test list to determine if empty */
int list_empty(Head *pHead);

/* add node to beginning of list */
Node *list_push(Head *pHead);

/* add node to tail of list */
Node *list_push_tail(Head *pHead);

/* remove specified node from list - counts from one*/
int list_remove(Head *pHead, int count);

/* return pointer to last node in list */
Node *list_tail(Head *pHead);

/* remove all nodes from list and free memory from them */
int list_clear(Head *pHead);

#endif /* LINKED_LIST_H_ */
