#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int num;
	struct node *next;
} Node, *NodePtr;

int main()
{
	void printList(NodePtr);
	NodePtr makeNode(int);
	NodePtr addInPlace(NodePtr, int);
	int n;
	NodePtr top, np, last;

	top = NULL;

	printf("Enter integers, follwed by return.\n");
	printf("Terminate input with 0.\n");

	if(scanf("%d", &n)!= 1) n = 0;
	while(n!= 0)
	{
		top = addInPlace(top, n);
		if(scanf("%d", &n)!=1)n = 0;

		/*
		np = makeNode(n);
		if(top == NULL) top = np;
		else last -> next = np;
		last = np;
		if(scanf("%d", &n)!=1)n=0;
		*/
	}
	printList(top);
	printf("Length of list: %d\n", length(top));
}

NodePtr addInPlace(NodePtr top, int n)
{
	NodePtr np, curr, prev, makeNode(int);
	np = makeNode(n);
	prev = NULL;
	curr = top;
	while(curr != NULL && n > curr->num)
	{
		prev = curr;
		curr = curr->next;
	}
	if(prev == NULL)
	{
		np->next = top;
		return np;
	}
	np->next = curr;
	prev->next = np;
	return top;
}

NodePtr makeNode(int n)
{
	NodePtr np = (NodePtr)malloc(sizeof(Node));
	np -> num = n;
	np -> next = NULL;
	return np;
}

int length(NodePtr top)
{
	int n = 0;
	NodePtr curr = top;
	while(curr != NULL)
	{
		n++;
		curr = curr->next;
	}
	return n;
}

NodePtr search(NodePtr top, int key)
{
	while(top != NULL && key != top->num)
		top = top->next;
	return top;	
}

NodePtr getLast(NodePtr top)
{
	if(top == NULL) return NULL;
	while(top->next != NULL)
		top = top->next;
	return top;
}

void printList(NodePtr np)
{
	printf("Printing Linked List:\n");
	while(np != NULL)
	{
		printf("%d\n", np->num);
		np = np->next;
	}
}
