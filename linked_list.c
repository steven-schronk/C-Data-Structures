#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "linked_list.h"

Head *list_new()
{
	Head *head = malloc(sizeof(Head));
	if (head == NULL)
		return NULL;
	head->count = 0;
	return head;
}

int list_delete(Head *list)
{
	return 0;
}

/* find current length of list */
int list_length(Head *list)
{
	return list->count;
}

int list_empty(Head *list)
{
	if(list->count == 0)
		return true;
	return false;
}

Node *list_next(Head *list)
{
	if(list->pNode == NULL)
		return false;
	return list->pNode;
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

int list_remove(Head *list, int count)
{
	Node *pLastNode = list->pNode;
	Node *pNextNode = pLastNode;
	if(list == NULL || count > list->count)
		return -1;

	while(count > 1)
	{
		pLastNode = pNextNode;
		pNextNode = pLastNode->pNext;
		count--;
	}

	pLastNode->pNext = pNextNode->pNext;
	free(pNextNode);
	list->count--;
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
