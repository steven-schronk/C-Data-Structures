#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "lib_ll.h"

List_Head *list_new(void)
{
	List_Head *pHead = malloc(sizeof(List_Head));
	if (pHead == NULL) return NULL;
	pHead->count = 0;
	pHead->pNext = NULL;
	return pHead;
}

void list_delete(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;
	while(pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		free(pTemp);
	}
	pHead->count = 0;
	pHead->pNext = NULL;
	free(pHead);
}

int list_len(List_Head *pHead)
{
	if (pHead == NULL) return -1;
	return pHead->count;
}

List_Node *list_search(List_Head *pHead)
{
	pHead++; /* junk code */
	return NULL;
}

List_Node *list_tail(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;

	if(pHead->pNext == NULL) return NULL;
	while(pTemp->pNext != NULL)
		pTemp = pTemp->pNext;
	return pTemp;
}

void list_print(List_Head *pHead)
{
	printf("Count: %d\n", pHead->count);
}

List_Node *list_ins_head(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;

	List_Node *pNode = malloc(sizeof(List_Node));
	if (pNode == NULL) return NULL;
	pNode->pData = NULL;
	pNode->pNext = NULL;
	if(pHead->pNext == NULL) /* adding to empty list */
	{
		pHead->pNext = pNode;
	} else {
		pNode->pNext = pTemp;
		pHead->pNext = pNode;
	}
	pHead->count++;
	return pNode;
}

List_Node *list_ins_tail(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;
	List_Node *pNode = malloc(sizeof(List_Node));
	if (pNode == NULL) return NULL;
	pNode->pData = NULL;
	if(pHead->pNext == NULL) /* empty list */
	{
		pHead->pNext = pNode;
	} else {
		pTemp = list_tail(pHead);
		pTemp->pNext = pNode;
		pNode->pNext = NULL;
	}
	pHead->count++;
	return pNode;
}

List_Node *list_ins_before(List_Head *pHead, List_Node *pNode)
{
	List_Node *pTemp = pHead->pNext;
	List_Node *pPrev = NULL;
	List_Node *pNew = malloc(sizeof(List_Node));
	if (pNew == NULL) return NULL;
	pNew->pData = NULL;
	if(pTemp == NULL) /* empty list */
	{
		pHead->pNext = pNode;
	} else {
		while(pTemp != pNode && pTemp != NULL)
		{
			pPrev = pTemp;
			pTemp = pTemp->pNext;
		}
		if(pTemp == NULL) /* did not find matching node */
		{
			free(pNew);
			return NULL;
		}
		if(pPrev == NULL) pHead->pNext = pNew;
		else pPrev->pNext = pNew; /* put new node at end of previous */
		pNew->pNext = pTemp; /* push current node down */
	}
	pHead->count++;
	return pNew;
}

List_Node *list_ins_after(List_Head *pHead, List_Node *pNode)
{
	List_Node *pTemp = pHead->pNext;
	List_Node *pNew = malloc(sizeof(List_Node));
	if (pNew == NULL) return NULL;
	pNew->pData = NULL;
	if(pTemp == NULL) /* empty list */
	{
		pHead->pNext = pNode;
	} else {
		while(pTemp != pNode && pTemp != NULL)
		{
			pTemp = pTemp->pNext;
		}
		if(pTemp == NULL) /* did not find matching node */
		{
			free(pNew);
			return NULL;
		}
		pTemp->pNext = pNew;
		pNew->pNext = NULL;
	}
	pHead->count++;
	return pNew;
}

int list_rm_node(List_Head *pHead, List_Node *pNode)
{
	List_Node *pPrev = NULL;

	if(pHead == NULL || pNode == NULL)
		return -1; /* Not valid data */

	if(list_size(pHead) == 0)
		return -1; /* list was empty */

	pPrev = list_prev_node(pHead, pNode);
	if(pNode->pNext == NULL) /* removing from end of list */
	{
		if(pPrev == NULL) /* no node before this one */
		{
			pHead->pNext = NULL;
		} else { /* previous node exists */
			/*pHead->pNext = pHead->pNext->pNext;*/
			pPrev->pNext = NULL;
		}
	} else { /* removing from middle */
		if(pPrev == NULL)
		{
			pHead->pNext = pNode->pNext;
		} else {
			pPrev->pNext = pNode->pNext;
		}
	}
	free(pNode);
	pHead->count--;
	return 1;
}

int list_rm_before(List_Head *pHead, List_Node *pNode)
{
	List_Node *pPrev = list_prev_node(pHead, pNode);
	if(pPrev == NULL)
		return -1;
	return list_rm_node(pHead, pPrev);
}

void list_clear(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;
	if(pTemp != NULL)
	{
		while(pTemp->pNext != NULL)
		{
			pTemp = pTemp->pNext;
			free(pTemp);
		}
	}
	pHead->count = 0;
	pHead->pNext = NULL;
}

List_Node *list_prev_node(List_Head *pHead, List_Node *pNode)
{
	List_Node *pPrev = NULL, *pTemp;

	if(pHead == NULL || pNode == NULL)
		return NULL;
	pTemp = pHead->pNext;
	do {
		pPrev = pTemp;
		pTemp = pTemp->pNext;
		if(pTemp == NULL) return NULL; /* reached end of list */
	} while(pTemp != pNode);
	return pPrev;
}
