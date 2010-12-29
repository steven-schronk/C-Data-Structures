#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int num;
	struct node *next;
} Node, *NodePtr;

int main()
{
	void printList(NodePtr);
	NodePtr makeList(void);
	NodePtr merge(NodePtr, NodePtr);
	NodePtr A, B;

	printf("Enter numbers for the first list (0 to end)\n");
	A = makeList();
	printf("Enter numbers for the second list (0 to end)\n");
	B = makeList();
	printf("\nThe merged list is\n");
	printList(merge(A,B));
}

NodePtr makeList()
{
	NodePtr makeNode(int), np, top, last;
	int n;
	top = NULL;
	if(scanf("%d", &n)!= 1)n = 0;
	while(n != 0)
	{
		np = makeNode(n);
		if(top == NULL) top = np;
		else last->next = np;
		last = np;
		if(scanf("%d", &n) != 1) n = 0;
	}
	return top;
}

NodePtr makeNode(int n)
{
	NodePtr np = (NodePtr)malloc(sizeof(Node));
	np->num = n;
	np->next = NULL;
	return np;
}

void printList(NodePtr np)
{
	while(np != NULL)
	{
		printf("%d ", np->num);
		np = np->next;
	}
	printf("\n\n");
}

NodePtr merge(NodePtr A, NodePtr B)
{
	NodePtr C = NULL, last;
	while(A != NULL && B != NULL)
	{
		if(A->num < B->num)
		{
			if(C==NULL)C = A; else last->next = A;
			last = A;
			A = A->next;
		} else {
			if(C == NULL)C = B; else last->next = A;
			last = A;
			A = A->next;
		}
		if(A == NULL)last->next = B;
		else last->next = A;
	}
	return C;
}



