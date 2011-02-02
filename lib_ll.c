#include <assert.h>
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
	List_Node *pTemp;
	assert(pHead != NULL);
	if(pHead->count == 0) { return; }
	pTemp = pHead->pNext;
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
	assert(pHead != NULL);
	if (pHead == NULL) return -1;
	return pHead->count;
}

int list_search(List_Head *pHead, List_Node *pNode)
{
	List_Node *pTemp = NULL;
	assert(pHead != NULL);
	if(pHead->count == 0) return 0;
	pTemp = pHead->pNext;
	while(pTemp != NULL) {
		if(pTemp == pNode) return 1;
		pTemp = pTemp->pNext;
	}
	return 0;
}

List_Node *list_tail(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;

	if(pHead->pNext == NULL) return NULL;
	while(pTemp->pNext != NULL)
		pTemp = pTemp->pNext;
	return pTemp;
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

List_Node *list_ins_head_data(List_Head *pHead, void *Data)
{
	List_Node *temp = list_ins_head(pHead);
	temp->pData = Data;
	return temp;
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

List_Node *list_ins_tail_data(List_Head *pHead, void *Data)
{
	List_Node *temp = list_ins_tail(pHead);
	temp->pData = Data;
	return temp;
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

int list_copy(List_Head *pDest, List_Head *pSrc)
{
	int i = 1; /* start with head node */
	List_Node *pTemp = NULL;
	assert(pDest != NULL && pSrc != NULL);
	if(pSrc->count == 0) { return 0; } /* nothing to copy */
	list_clear(pDest);
	while (i <= pSrc->count) {
		pTemp = list_get_num(pSrc, i);
		list_ins_tail_data(pDest, pTemp->pData);
		i++;
	}
	return 0;
}

void list_print(List_Head *pHead)
{
	int i = 0;
	List_Node *temp = NULL;
	assert(pHead != NULL);
	printf("\n");
	if(pHead->count == 0)
		printf("Empty List\n");
	else {
		temp = pHead->pNext;
		do {
			printf("List Item: %d -> Data: %p\n", i, (void *)temp);
			temp = temp->pNext;
			i++;
		} while (temp != NULL);
	}
}

List_Node *list_get_num(List_Head *pHead, int count)
{
	int i = 1;
	List_Node *pNode;
	assert(count > 0);
	assert(pHead != NULL);
	if(pHead->count == 0) { return NULL; } /* list is empty */
	if(count > pHead->count) { return NULL; } /* node does not exist */
	pNode = pHead->pNext;
	while(i < count) {
		pNode = pNode->pNext;
		i++;
	}
	return pNode;
}

int list_node_swap(List_Node *pPrev, List_Node *pCurr)
{
	List_Node* pTemp = NULL;
	assert(pCurr != NULL && pPrev != NULL);
	pTemp = pCurr->pNext;
	pCurr->pNext = pPrev->pNext;
	pPrev->pNext = pTemp;
	return 0;
}

List_Head *list_reverse(List_Head *pHead)
{
	List_Head *newList = list_new();
	assert(pHead != NULL);
	while(pHead->count > 0)
	{
		list_ins_head_data(newList, pHead->pNext->pData);
		list_rm_node(pHead, pHead->pNext);
	}
	list_delete(pHead);
	return newList;
}

void list_append(List_Head *pLo, List_Head *pHi)
{
	List_Node *pTemp = NULL;
	assert(pLo != NULL && pHi != NULL);
	pTemp = list_tail(pLo);
	pTemp->pNext = pHi->pNext;
	pLo->count = pLo->count + pHi->count;
}

int list_data_array(List_Head *pHead, void *pArr[], int len)
{
	int i = 0;
	List_Node *pTemp = NULL;
	assert(pHead != NULL);
	assert(pArr != NULL);
	assert(len > 0);
	for(i = 0; i < len; i++) /* reset array */
		pArr[i] = NULL;
	if(pHead->count == 0) return 1;
	pTemp = pHead->pNext;
	i = 0;
	while(pTemp != NULL) {
		pArr[i++] = pTemp->pData;
		pTemp = pTemp->pNext;
	}
	return 0;
}

int list_node_array(List_Head *pHead, void *pArr[], int len)
{
	int i = 0;
	List_Node *pTemp = NULL;
	assert(pHead != NULL);
	assert(pArr != NULL);
	assert(len > 0);
	for(i = 0; i < len; i++) /* reset array */
		pArr[i] = NULL;
	if(pHead->count == 0) return 1;
	pTemp = pHead->pNext;
	i = 0;
	while(pTemp != NULL){
		pArr[i++] = pTemp;
		pTemp = pTemp->pNext;
	}
	return 0;
}

void list_clear(List_Head *pHead)
{
	List_Node *pTemp = pHead->pNext;
	assert(pHead != NULL);
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
