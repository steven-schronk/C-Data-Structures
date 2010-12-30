#include <stdio.h>
#include <stdlib.h>

#define ROGUE_VALUE -9999
#define MAX_STACK 10

typedef struct {
	int top;
	int st[MAX_STACK];
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
	sp->top = -1;
	return sp;
}

int empty(Stack s)
{
	return (s->top == -1);
}

void push(Stack s, int n)
{
	if(s->top == MAX_STACK - 1)
	{
		printf("\nStack Overflow\n");
		exit(1);
	}
	++(s->top);
	s->st[s->top] = n;
}

int pop(Stack s)
{
	if(empty(s)) return ROGUE_VALUE;
	int hold = s->st[s->top];
	--(s->top);
	return hold;
}
