#include <stdio.h>
#include <stdlib.h>

#define ROGUE_VALUE -9999

typedef struct node {
	int num;
	struct node *next;
} Node, *NodePtr;

typedef struct stackType {
	NodePtr top;
} StackType, *Stack;

Stack initStack();
int empty(Stack);
void push(Stack, int);
int pop(Stack);

int main()
{
	int n;
	Stack s = initStack();
	scanf("%d", &n);
	while(n != 0)
	{
		push(s, n);
		scanf("%d", &n);
	}
	while(!empty(s))
		printf("%d ", pop(s));
	printf("\n");
}

Stack initStack()
{
	Stack sp = (Stack)malloc(sizeof(StackType));
	sp->top = NULL;
	return sp;
}

int empty(Stack s)
{
	return (s->top == NULL);
}

void push(Stack s, int n)
{
	NodePtr np = (NodePtr)malloc(sizeof(Node));
	np->num = n;
	np->next = s->top;
	s->top = np;
}

int pop(Stack s)
{
	if(empty(s)) return ROGUE_VALUE;
	int hold = s->top->num;
	NodePtr temp = s->top;
	s->top = s->top->next;
	free(temp);
	return hold;
}
