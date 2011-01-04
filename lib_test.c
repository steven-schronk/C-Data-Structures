#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_test.h"
#include "lib_ll.h"
#include "lib_vqueue.h"
#include "lib_vstack.h"

#define PASSED 0
#define FAILED 1

void exit_error(const char *err_msg)
{
	fprintf(stderr, "ERROR: %s\n", err_msg);
	exit(EXIT_FAILURE);
}

void test_msg_start(char *msg)
{
	int msg_length = strlen(msg);
	printf("%s", msg);

	/* 74 is 80 - length of "PASSED" */
	while(msg_length < 74)
	{
		putchar('.');
		msg_length++;
	}
}

void test_msg_end(int pass)
{
	if(pass == PASSED)
	{
		printf("PASSED\n");
	} else {
		printf("FAILED\n\n");
		exit_error("UNIT TESTING FAILED.\n\n");
	}
}

/* unit tests begin here */

int test_linked_list()
{
	int result = 0;
	List_Node *test_node1 = NULL;
	List_Node *test_node2 = NULL;
	List_Head *test_list = list_new();

	test_msg_start("Test Linked List Creation");
	if(test_list == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List Empty Length - Using Variable");
	if(test_list->count != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List Empty Length - Using Length Function");
	if(list_len(test_list) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Adding Node To Empty List");
	if(list_ins_tail(test_list) == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Adding Node To Non-Empty List");
	if(list_ins_tail(test_list) == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Clearing List With More Than One Node");
	list_clear(test_list);
	if(test_list->count != 0) result++;
	if(list_len(test_list) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Clearing List With No Nodes");
	list_clear(test_list);
	if(test_list->count != 0) result++;
	if(list_len(test_list) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List End - No Nodes");
	list_clear(test_list);
	if(list_tail(test_list) != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List End - One Node Only");
	list_clear(test_list);
	test_node1 = list_ins_tail(test_list);
	if(test_node1 == NULL) result++;
	if(list_tail(test_list) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List End - More Than One Node");
	list_clear(test_list);
	list_ins_tail(test_list);
	test_node1 = list_ins_tail(test_list);
	if(test_node1 == NULL) result++;
	if(list_tail(test_list) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Node From List With More Than One Node");
	list_clear(test_list);
	test_node1 = list_ins_tail(test_list);
	test_node2 = list_ins_head(test_list);
	list_rm_node(test_list, test_node1);
	if(test_list->pNext != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Node From Empty List");
	list_clear(test_list);
	test_node1 = (List_Node*)&test_list; /* pointer points to known bad location */
	/* should not crash but return gracefully */
	if(list_rm_node(test_list, test_node1) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Inserting Node After");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	test_node1 = list_ins_tail(test_list);
	test_node2 = list_ins_after(test_list, test_node1);

	 /* test beginning */
	if(test_list->pNext != test_node1) result++;
	 /*...and end nodes. */
	if(list_tail(test_list) != test_node2) result++;
	/* end node next should be null */
	if(list_tail(test_list)->pNext != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Inserting Node Before");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	test_node1 = list_ins_head(test_list);
	test_node2 = list_ins_before(test_list, test_node1);

	/* test beginning */
	if(test_list->pNext != test_node2) result++;
	/*...and end nodes. */
	if(list_tail(test_list) != test_node1) result++;
	/* end node next should be null */
	if(list_tail(test_list)->pNext != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Test Lengths");
	list_clear(test_list);
	if(list_len(test_list) != 0) result++;

	/* adding nodes using each function */
	list_ins_head(test_list);
	if(list_len(test_list) != 1) result++;

	list_ins_tail(test_list);
	if(list_len(test_list) != 2) result++;

	list_ins_before(test_list, list_tail(test_list));
	if(list_len(test_list) != 3) result++;

	list_ins_after(test_list, list_tail(test_list));
	if(list_len(test_list) != 4) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Previous Node Check");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	if(list_prev_node(test_list, NULL) != NULL) result++;
	if(list_prev_node(NULL, test_list->pNext) != NULL) result++;
	if(list_prev_node(NULL, test_node1 + 1000) != NULL) result++;
	test_node1 = list_ins_head(test_list);
	if(list_prev_node(test_list, test_list->pNext) != NULL) result++;
	test_node2 = list_ins_head(test_list);
	if(list_prev_node(test_list, test_node1) != test_node2) result++;
	if(list_prev_node(test_list, test_node2) != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Nodes By Address");
	/* removing nodes from various places */
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;

	if(list_rm_node(NULL, test_list->pNext)!= -1) result++;
	if(list_rm_node(test_list, NULL) != -1) result++;
	test_node1 = list_ins_head(test_list);
	test_node2 = list_ins_head(test_list);
	list_rm_node(test_list, test_list->pNext);
	if(list_len(test_list) != 1) result++;
	test_node1 = list_tail(test_list);
	list_rm_node(test_list, test_node1);
	if(list_len(test_list) != 0) result++;
	if(list_rm_node(test_list, list_tail(test_list)) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Nodes After Address");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	test_node1 = list_ins_tail(test_list);
	test_node2 = list_ins_tail(test_list);
	if(list_rm_next(test_list, test_node1) != 1) result++;

	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Nodes Before Address");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	if(list_rm_before(test_list, NULL) != -1) result++;
	if(list_rm_before(NULL, NULL) != -1) result++;
	if(list_rm_before(test_list + 1000, NULL) != -1) result++;
	test_node1 = list_ins_tail(test_list);
	test_node2 = list_ins_tail(test_list);
	if(list_rm_before(test_list, test_node2 + 1000) != -1) result++;
	if(list_rm_before(test_list, test_node2) != 1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Next Preprocessor");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	test_node1 = list_ins_tail(test_list);
	test_node2 = list_ins_tail(test_list);
	if(list_next(test_node1) == test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Default Payload");
	list_clear(test_list);
	test_node1 = NULL;
	test_node2 = NULL;
	test_node1 = list_ins_tail(test_list);
	test_node2 = list_ins_tail(test_list);
	if(test_node1->pData != NULL) result++;

	/* make data point to something and test again... */
	test_node1->pData = test_node1;
	if(list_data(test_node1) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Is Head Preprocessor");
	if(list_is_head(test_list, test_node2) != 0) result++;
	if(list_is_head(test_list, test_node1) != 1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Is Tail Preprocessor");
	if(list_is_tail(test_node2) != 1) result++;
	if(list_is_tail(test_node1) != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Head Preprocessor");
	if(list_head(test_list) != test_node1) result++;
	test_msg_end(result);

	return result;
}

int test_vstack()
{
	int result = 0;
	int i = 0;
	char data[] = "This is some test data\n";
	char *pCh;
	Stack_Head *test_stack = vstack_new();
	Stack_Node *temp_node1 = NULL, *temp_node2 = NULL;

	test_msg_start("Test Variable Stack - Creating New Stack");
	if(!test_stack) result++;
	test_msg_end(result);

	test_msg_start("Test Variable Stack - Pushing Data Into Stack");
	while(data[i] != '\0')
	{
		temp_node1 = vstack_push(test_stack);
		/* reserve memory for node payload - pointer to memory in pData */
		pCh = malloc(sizeof(char));
		*pCh = data[i];
		temp_node1->pData = pCh;
		i++;
	}
	test_msg_end(result);

	test_msg_start("Test Variable Stack - Popping Data Off Of Stack");
	while(i > 0)
	{
		i--;
		temp_node1 = vstack_peek(test_stack);
		/* verify data of this node */
		pCh = temp_node1->pData;
		if(*pCh != data[i]) result++;
		vstack_pop(test_stack);
	}
	test_msg_end(result);

	test_msg_start("Test Variable Stack - Popping Data Off Empty Stack");
	vstack_clear(test_stack);
	if(vstack_pop(test_stack) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Variable Stack - Tracking Stack Size");
	vstack_clear(test_stack);
	if(vstack_size(test_stack) != 0) result++;
	vstack_push(test_stack);
	if(vstack_size(test_stack) != 1) result++;
	temp_node1 = vstack_peek(test_stack);
	if(vstack_size(test_stack) != 1) result++;
	vstack_pop(test_stack);
	if(vstack_size(test_stack) != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Variable Stack - Tracking Node Address With Peek and Push");
	vstack_clear(test_stack);
	temp_node1 = NULL;
	temp_node1 = vstack_push(test_stack);
	temp_node2 = vstack_push(test_stack);
	if(vstack_peek(test_stack) != temp_node2) result++;
	vstack_pop(test_stack);
	if(vstack_peek(test_stack) != temp_node1) result++;
	test_msg_end(result);

	return result;
}

int test_vqueue()
{
	int result = 0;
	int i = 0;
	char data[] = "T\n";
	char *pCh;
	Queue_Head *test_q = vq_new();
	Queue_Node *temp_node1 = NULL, *temp_node2 = NULL;

	test_msg_start("Test Queue - Creating New Queue");
	if(!test_q) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Pushing Data Into Queue");
	while(data[i] != '\0')
	{
		temp_node1 = vq_enq(test_q);
		/* reserve memory for node payload - pointer to memory in pData */
		pCh = malloc(sizeof(char));
		*pCh = data[i];
		temp_node1->pData = pCh;
		i++;
	}
	test_msg_end(result);

	test_msg_start("Test Queue - Popping Data Off Of Queue");
	i = 0;
	while(data[i] != '\n')
	{
		temp_node1 = vq_peek(test_q);
		/* verify data of this node */
		pCh = temp_node1->pData;
		if(*pCh != data[i]) result++;
		vq_deq(test_q);
		i++;
	}
	test_msg_end(result);

	test_msg_start("Test Queue - Popping Data Off Empty Queue");
	vq_clear(test_q);
	if(vq_deq(test_q) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Tracking Queue Size");
	vq_clear(test_q);
	if(vq_size(test_q) != 0) result++;
	vq_enq(test_q);
	if(vq_size(test_q) != 1) result++;
	temp_node1 = vq_peek(test_q);
	if(vq_size(test_q) != 1) result++;
	vq_deq(test_q);
	if(vq_size(test_q) != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Tracking Node Address With Enqueue and Dequeue");
	vq_clear(test_q); temp_node1 = NULL; temp_node2 = NULL;
	temp_node1 = vq_enq(test_q);
	temp_node2 = vq_enq(test_q);
	if(vq_peek(test_q) != temp_node1) result++;
	vq_deq(test_q);
	if(vq_peek(test_q) != temp_node2) result++;
	test_msg_end(result);

	return result;
}

int test_stack_array()
{
	int result = 0;

	return result;
}

int test_all()
{
	int result = 0;
	result += test_linked_list();
	result += test_stack_array();
	result += test_vstack();
	result += test_vqueue();
	return result;
}

int main()
{
	printf("\nRUNNING ALL UNIT TESTS ON DATA STRUCTURES.\n\n");
	if(test_all() == 0)
	{
		printf("\nUNIT TEST COMPLETE - ALL TESTS RETURNED PASSED.\n\n");
	} else {
		exit_error("UNIT TEST FAILED.\n\n");
	}
	exit(EXIT_SUCCESS);
}
