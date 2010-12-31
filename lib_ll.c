#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

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

	if(pHead->pNext == NULL)
	{
		return NULL;
	}
	while(pTemp->pNext != NULL){
		pTemp = pTemp->pNext;
	}
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
		while (pTemp->pNext != NULL)/* move to end of list */
			pTemp = pNode->pNext;
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
	List_Node *pTemp;

	if (list_size(pHead) == 0)
		return -1; /* list was empty */

	if (pNode == NULL) { /* removal from head */
	   pTemp = pHead->pNext;
	   pHead->pNext = pHead->pNext->pNext;

 	  /*if (list_size(pHead) == 1)
	      pHead->tail = NULL;  */

	} else { /* removal away from head */

	   	if (pNode->pNext == NULL)
      			return -1;

   		pTemp = pNode->pNext;
   		pNode->pNext = pNode->pNext->pNext;
   		/*
   		if (pNode->next == NULL)
      			pHead->tail = pNode;*/
	}
	free(pTemp);
	pHead->count--;
	return 1;
}

int list_rm_next(List_Head *pHead, List_Node *pNode)
{
	List_Node *pTemp;

	if (list_size(pHead) == 0)
		return -1; /* list was empty */

	if (pNode == NULL) { /* removal from head */
	   pTemp = pHead->pNext;
	   pHead->pNext = pHead->pNext->pNext;

 	  /*if (list_size(pHead) == 1)
	      pHead->tail = NULL;  */

	} else { /* removal away from head */

	   	if (pNode->pNext == NULL)
      			return -1;

   		pTemp = pNode->pNext;
   		pNode->pNext = pNode->pNext->pNext;
   		/*
   		if (pNode->next == NULL)
      			pHead->tail = pNode;*/
	}
	free(pTemp);
	pHead->count--;
	return 1;
}

int list_rm_before(List_Head *pHead, List_Node *pNode)
{
	pNode=NULL;
	pHead=NULL;
	/* IMPLEMENT THIS */
	return 0;
}

int list_rm_node2(List_Head *pHead, List_Node *pNode)
{
	List_Node *pTemp = pHead->pNext;
	List_Node *pPrev = NULL;
	if(pHead->count == 0) return -1;

	/* find node in list */
	while(pTemp != pNode)
	{
		pPrev = pTemp;
		pTemp = pTemp->pNext;
	}
	if(pTemp == NULL) return -1; /* could not find this node at all */

	/* found node at end of list */
	if(pTemp->pNext == NULL)
	{
		pPrev->pNext = NULL; /* move end of list up one */
	} else { /* found node between two other nodes */
		pPrev->pNext = pTemp->pNext;
	}
	free(pNode);
	pHead->count--;
	return 1;
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
