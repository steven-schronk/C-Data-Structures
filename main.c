#include <stdio.h>
#include "linked_list.h"

int main()
{
	Head *list = list_new();
	printf("Pointer To List: %p\n", list);
	list_push(list);
	list_push(list);
	list_push(list);
	list_push(list);
	list_push(list);
	list_remove(list, 3);
	list_clear(list);
	printf("List Tail: %p\n", list_tail(list));
	return 0;
}
