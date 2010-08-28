#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "linked_list.h"

Head *list_new()
{
	Head *pHead = malloc(sizeof(Head));
	if (pHead == NULL)
		return NULL;
	pHead->count = 0;
	return pHead;
}

int list_delete(Head *pHead)
{
	return 0;
}

/* find current length of list */
int list_length(Head *pHead)
{
	return pHead->count;
}

int list_empty(Head *pHead)
{
	if(pHead->count == 0)
		return true;
	return false;
}

Node *list_next(Head *pHead)
{
	if(pHead->pNode == NULL)
		return false;
	return pHead->pNode;
}

Node *list_push(Head *pHead)
{
	if (pHead == NULL)
		return NULL;

	Node *node = malloc(sizeof(Node));
	if (node == NULL)
		return NULL;
	if(pHead->count > 0)
	{
		node->pNext = pHead->pNode;
	}
	pHead->pNode = node;
	pHead->count++;
	return node;
}

int list_remove(Head *pHead, int count)
{
	Node *pLastNode = pHead->pNode;
	Node *pNextNode = pLastNode;
	if(pHead == NULL || count > pHead->count)
		return -1;

	while(count > 1)
	{
		pLastNode = pNextNode;
		pNextNode = pLastNode->pNext;
		count--;
	}

	pLastNode->pNext = pNextNode->pNext;
	free(pNextNode);
	pHead->count--;
	return 0;
}

Node *list_tail(Head *pHead)
{
	Node *pNode = pHead->pNode;
	if(pHead == NULL)
		return NULL;

	while(pNode->pNext != NULL)
	{
		pNode = pNode->pNext;
	}
	return pNode;
}

int list_clear(Head *pHead)
{
	if(pHead == NULL || pHead->count <= 0)
		return -1;

	Node *pLastNode = pHead->pNode; /* get first node address */
	Node *pNextNode = pLastNode;
	while(pLastNode->pNext != NULL) /* move until no more nodes exist */
	{
		pLastNode = pNextNode;
		pNextNode = pLastNode->pNext;
		free(pLastNode);
	}
	pHead->pNode = NULL;
	pHead->count = 0;
	return 0;
}
