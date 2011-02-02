#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib_test.h"
#include "lib_hash.h"
#include "lib_ll.h"
#include "lib_random.h"
#include "lib_sort.h"
#include "lib_vbtree.h"
#include "lib_vqueue.h"
#include "lib_vstack.h"

#define PASSED 0
#define FAILED 1

#define SORT_TESTS 1000

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

int test_random()
{
	int i, j, result = 0;
	test_msg_start("Test Random Number Generator - Integers 0 to 100");
		random_seed();
		j = 0;
		while(j < 100000) {
			i = random_int(0,100);
			if(i < 0 || i > 100) result++;
			j++;
		}
	test_msg_end(result);

	return result;
}

int test_linked_list()
{
	int i,j, result = 0;
	List_Node *test_node1 = NULL;
	List_Node *test_node2 = NULL;
	List_Node *test_node3 = NULL;
	List_Node *pTrack[5];
	void* pArr[6];

	List_Head *test_list1 = list_new();
	List_Head *test_list2 = list_new();

	test_msg_start("Test Linked List Creation");
		if(test_list1 == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List Empty Length - Using Variable");
		if(test_list1->count != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List Empty Length - Using Length Function");
		if(list_len(test_list1) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Adding Node To Empty List");
		if(list_ins_tail(test_list1) == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Adding Node To Non-Empty List");
		if(list_ins_tail(test_list1) == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Clearing List With More Than One Node");
		list_clear(test_list1);
		if(test_list1->count != 0) result++;
		if(list_len(test_list1) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Clearing List With No Nodes");
		list_clear(test_list1);
		if(test_list1->count != 0) result++;
		if(list_len(test_list1) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List End - No Nodes");
		list_clear(test_list1);
		if(list_tail(test_list1) != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List End - One Node Only");
		list_clear(test_list1);
		test_node1 = list_ins_tail(test_list1);
		if(test_node1 == NULL) result++;
		if(list_tail(test_list1) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List End - More Than One Node");
		list_clear(test_list1);
		list_ins_tail(test_list1);
		test_node1 = list_ins_tail(test_list1);
		if(test_node1 == NULL) result++;
		if(list_tail(test_list1) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Node From List With More Than One Node");
		list_clear(test_list1);
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_head(test_list1);
		list_rm_node(test_list1, test_node1);
		if(test_list1->pNext != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Node From Empty List");
		list_clear(test_list1);
		test_node1 = (List_Node*)&test_list1; /* pointer points to known bad location */
		/* should not crash but return gracefully */
		if(list_rm_node(test_list1, test_node1) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Inserting Node After");
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_after(test_list1, test_node1);

		/* test beginning */
		if(test_list1->pNext != test_node1) result++;
		/*...and end nodes. */
		if(list_tail(test_list1) != test_node2) result++;
		/* end node next should be null */
		if(list_tail(test_list1)->pNext != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Inserting Node Before");
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;
		test_node1 = list_ins_head(test_list1);
		test_node2 = list_ins_before(test_list1, test_node1);

		/* test beginning */
		if(test_list1->pNext != test_node2) result++;
		/*...and end nodes. */
		if(list_tail(test_list1) != test_node1) result++;
		/* end node next should be null */
		if(list_tail(test_list1)->pNext != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Test Lengths");
		list_clear(test_list1);
		if(list_len(test_list1) != 0) result++;

		/* adding nodes using each function */
		list_ins_head(test_list1);
		if(list_len(test_list1) != 1) result++;

		list_ins_tail(test_list1);
		if(list_len(test_list1) != 2) result++;

		list_ins_before(test_list1, list_tail(test_list1));
		if(list_len(test_list1) != 3) result++;

		list_ins_after(test_list1, list_tail(test_list1));
		if(list_len(test_list1) != 4) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Previous Node Check");
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;
		if(list_prev_node(test_list1, NULL) != NULL) result++;
		if(list_prev_node(NULL, test_list1->pNext) != NULL) result++;
		if(list_prev_node(NULL, test_node1 + 1000) != NULL) result++;
		test_node1 = list_ins_head(test_list1);
		if(list_prev_node(test_list1, test_list1->pNext) != NULL) result++;
		test_node2 = list_ins_head(test_list1);
		if(list_prev_node(test_list1, test_node1) != test_node2) result++;
		if(list_prev_node(test_list1, test_node2) != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Nodes By Address");
		/* removing nodes from various places */
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;

		if(list_rm_node(NULL, test_list1->pNext)!= -1) result++;
		if(list_rm_node(test_list1, NULL) != -1) result++;
		test_node1 = list_ins_head(test_list1);
		test_node2 = list_ins_head(test_list1);
		list_rm_node(test_list1, test_list1->pNext);
		if(list_len(test_list1) != 1) result++;
		test_node1 = list_tail(test_list1);
		list_rm_node(test_list1, test_node1);
		if(list_len(test_list1) != 0) result++;
		if(list_rm_node(test_list1, list_tail(test_list1)) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Nodes After Address");
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_tail(test_list1);
		if(list_rm_next(test_list1, test_node1) != 1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Removing Nodes Before Address");
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;
		if(list_rm_before(test_list1, NULL) != -1) result++;
		if(list_rm_before(NULL, NULL) != -1) result++;
		if(list_rm_before(test_list1 + 1000, NULL) != -1) result++;
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_tail(test_list1);
		if(list_rm_before(test_list1, test_node2 + 1000) != -1) result++;
		if(list_rm_before(test_list1, test_node2) != 1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Copying List");
		list_clear(test_list1);
		list_clear(test_list2);
		test_node1 = list_ins_tail(test_list1);
		test_node1->pData = &result;
		test_node2 = list_ins_tail(test_list1);
		if(list_copy(test_list2, test_list1) != 0) result++;
		if(test_list1->pNext == test_list2->pNext) result++;
		if(test_list1->count != 2) result++;
		if(test_list2->count != 2) result++;
		if(test_list1->pNext->pData != test_list2->pNext->pData) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Copying Empty List");
		list_clear(test_list1);
		list_clear(test_list2);
		if(list_copy(test_list2, test_list1) != 0) result++;
		if(test_list1->pNext != NULL) result++;
		if(test_list2->pNext != NULL) result++;
		if(test_list1->count != 0) result++;
		if(test_list2->count != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Get Node Address By Node Number - First Node");
		list_clear(test_list1);
		test_node1 = list_ins_head(test_list1);
		test_node2 = list_ins_head(test_list1);
		test_node3 = list_get_num(test_list1, 1);
		if(test_node3 != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Get Node Address By Node Number - Middle Node");
		list_clear(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		test_node2 = list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		test_node3 = list_get_num(test_list1, 5);
		if(test_node3 != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Get Node Address By Node Number - Last Node");
		list_clear(test_list1);
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_tail(test_list1);
		test_node3 = list_get_num(test_list1, 2);
		if(test_node3 != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Get Node Address By Node Number - Empty List");
		list_clear(test_list1);
		test_node1 = list_get_num(test_list1, 1);
		if(test_node1 != NULL) result++;
		test_node1 = list_get_num(test_list1, 55);
		if(test_node1 != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Swap Nodes In List");
		list_clear(test_list1);
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_tail(test_list1);
		test_node3 = list_ins_tail(test_list1);
		pTrack[1] = test_node1->pNext;
		pTrack[2] = test_node2->pNext;
		if(list_node_swap(test_node1, test_node2) != 0) result++;
		if(test_node1->pNext != pTrack[2]) result++;
		if(test_node2->pNext != pTrack[1]) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Reverse - Pointer Tracking");
		list_clear(test_list1);
		for(i = 0; i < 5; i++) {
			pTrack[i] = list_ins_tail(test_list1);
			pTrack[i]->pData = &pTrack[i]->pData;
		}
		test_list1 = list_reverse(test_list1);
		for(i = 1, j = 4; i <= 4; i++, j--) {
			test_node1 = list_get_num(test_list1, i);
			if(test_node1->pData != pTrack[j]) result++;
		}
	test_msg_end(result);

	test_msg_start("Test Linked List - List Next Preprocessor");
		list_clear(test_list1);
		list_clear(test_list2);
		test_node1 = NULL;
		test_node2 = NULL;
		test_node1 = list_ins_head(test_list1);
		test_node2 = list_ins_head(test_list1);
		if(list_next(test_node1) == test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Default Payload");
		list_clear(test_list1);
		test_node1 = NULL;
		test_node2 = NULL;
		test_node1 = list_ins_tail(test_list1);
		test_node2 = list_ins_tail(test_list1);
		if(test_node1->pData != NULL) result++;

		/* make data point to something and test again... */
		test_node1->pData = test_node1;
		if(list_data(test_node1) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Is Head Preprocessor");
		if(list_is_head(test_list1, test_node2) != 0) result++;
		if(list_is_head(test_list1, test_node1) != 1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Is Tail Preprocessor");
		if(list_is_tail(test_node2) != 1) result++;
		if(list_is_tail(test_node1) != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - List Head Preprocessor");
		if(list_head(test_list1) != test_node1) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Append Lists - Pointer Tracking");
		list_clear(test_list1);
		list_clear(test_list2);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		list_ins_tail(test_list1);
		pTrack[0] = list_ins_tail(test_list1);
		pTrack[1] = list_ins_tail(test_list2);
		list_ins_tail(test_list2);
		list_ins_tail(test_list2);
		list_append(test_list1, test_list2);
		if(test_list1->count != 7) result++;
		if(!list_search(test_list1, pTrack[0])) result++;
		if(!list_search(test_list1, pTrack[1])) result++;
		if(pTrack[0] != list_get_num(test_list1, 4)) result++;
		if(pTrack[1] != list_get_num(test_list1, 5)) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Create Data Array - Pointer Tracking");
		list_clear(test_list1);
		pTrack[0] = list_ins_tail(test_list1);
		pTrack[0] = pTrack[0]->pData = &test_list1;
		pTrack[1] = list_ins_tail(test_list1);
		pTrack[1] = pTrack[1]->pData = &test_list2;
		pTrack[2] = list_ins_tail(test_list1);
		pTrack[2] = pTrack[2]->pData = &pTrack;
		pTrack[3] = list_ins_tail(test_list1);
		pTrack[3] = pTrack[3]->pData = &test_node1;
		pTrack[4] = list_ins_tail(test_list1);
		pTrack[4] = pTrack[4]->pData = &test_node2;
		pArr[5] = &test_list1;
		if(list_data_array(test_list1, pArr, 6) != 0) result++;
		if(pArr[0] != pTrack[0]) result++;
		if(pArr[1] != pTrack[1]) result++;
		if(pArr[2] != pTrack[2]) result++;
		if(pArr[3] != pTrack[3]) result++;
		if(pArr[4] != pTrack[4]) result++;
		if(pArr[5] != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Create Node Array - Pointer Tracking");
		list_clear(test_list1);
		pTrack[0] = list_ins_tail(test_list1);
		pTrack[1] = list_ins_tail(test_list1);
		pTrack[2] = list_ins_tail(test_list1);
		pTrack[3] = list_ins_tail(test_list1);
		pTrack[4] = list_ins_tail(test_list1);
		pArr[5] = &test_list1;
		if(list_node_array(test_list1, pArr, 6) != 0) result++;
		if(pArr[0] != pTrack[0]) result++;
		if(pArr[1] != pTrack[1]) result++;
		if(pArr[2] != pTrack[2]) result++;
		if(pArr[3] != pTrack[3]) result++;
		if(pArr[4] != pTrack[4]) result++;
		if(pArr[5] != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Linked List - Search List");
		list_clear(test_list1);
		if(list_search(test_list1, test_node1) != 0) result++;
		test_node1 = list_ins_head(test_list1);
		if(list_search(test_list1, test_node1) != 1) result++;
		if(list_search(test_list1, test_node2) != 0) result++;
		if(list_search(test_list1, test_node3) != 0) result++;
		if(list_search(test_list1, NULL) != 0) result++;
		if(list_search(test_list1, (List_Node *)test_list1) != 0) result++;
		test_node2 = list_ins_head(test_list1);
		if(list_search(test_list1, test_node1) != 1) result++;
		if(list_search(test_list1, test_node2) != 1) result++;
		if(list_search(test_list1, test_node3) != 0) result++;
		if(list_search(test_list1, NULL) != 0) result++;
		if(list_search(test_list1, (List_Node *)test_list1) != 0) result++;
		list_clear(test_list1);
		if(list_search(test_list1, test_node1) != 0) result++;
		if(list_search(test_list1, test_node2) != 0) result++;
		if(list_search(test_list1, test_node3) != 0) result++;
		if(list_search(test_list1, NULL) != 0) result++;
		if(list_search(test_list1, (List_Node *)test_list1) != 0) result++;
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
	Queue_Head *test_q1 = vq_new();
	Queue_Head *test_q2 = vq_new();

	Queue_Node *test_node1 = NULL;
	Queue_Node *test_node2 = NULL;
	Queue_Node *test_node3 = NULL;

	Queue_Node *pTrack[5];

	test_msg_start("Test Queue - Creating New Queue");
		if(!test_q1) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Pushing Data Into Queue");
		while(data[i] != '\0')
		{
			test_node1 = vq_enq(test_q1);
			/* reserve memory for node payload - pointer to memory in pData */
			pCh = malloc(sizeof(char));
			*pCh = data[i];
			test_node1->pData = pCh;
			i++;
		}
	test_msg_end(result);

	test_msg_start("Test Queue - Popping Data Off Of Queue");
		i = 0;
		while(data[i] != '\n')
		{
			test_node1 = vq_peek(test_q1);
			/* verify data of this node */
			pCh = test_node1->pData;
			if(*pCh != data[i]) result++;
			vq_deq(test_q1);
			i++;
		}
	test_msg_end(result);

	test_msg_start("Test Queue - Popping Data Off Empty Queue");
		vq_clear(test_q1);
		if(vq_deq(test_q1) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Tracking Queue Size");
		vq_clear(test_q1);
		if(vq_size(test_q1) != 0) result++;
		vq_enq(test_q1);
		if(vq_size(test_q1) != 1) result++;
		test_node1 = vq_peek(test_q1);
		if(vq_size(test_q1) != 1) result++;
		vq_deq(test_q1);
		if(vq_size(test_q1) != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Tracking Node Address With Enqueue and Dequeue");
		vq_clear(test_q1); test_node1 = NULL; test_node2 = NULL;
		test_node1 = vq_enq(test_q1);
		test_node2 = vq_enq(test_q1);
		if(vq_peek(test_q1) != test_node1) result++;
		vq_deq(test_q1);
		if(vq_peek(test_q1) != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Copying Queue");
		vq_clear(test_q1);
		vq_clear(test_q2);
		test_node1 = vq_enq(test_q1);
		test_node1->pData = &result;
		test_node2 = vq_enq(test_q1);
		if(vq_copy(test_q2, test_q1) != 0) result++;
		if(test_q1->pNext == test_q2->pNext) result++;
		if(test_q1->count != 2) result++;
		if(test_q2->count != 2) result++;
		if(test_q1->pNext->pData != test_q2->pNext->pData) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Copying Empty Queue");
		vq_clear(test_q1);
		vq_clear(test_q2);
		if(vq_copy(test_q2, test_q1) != 0) result++;
		if(test_q1->pNext != NULL) result++;
		if(test_q2->pNext != NULL) result++;
		if(test_q1->count != 0) result++;
		if(test_q2->count != 0) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Get Node Address By Node Number - First Node");
		vq_clear(test_q1);
		test_node1 = vq_enq(test_q1);
		test_node2 = vq_enq(test_q1);
		test_node3 = vq_get_num(test_q1, 1);
		if(test_node3 != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Get Node Address By Node Number - Middle Node");
		vq_clear(test_q1);
		vq_enq(test_q1);
		vq_enq(test_q1);
		vq_enq(test_q1);
		vq_enq(test_q1);
		test_node2 = vq_enq(test_q1);
		vq_enq(test_q1);
		vq_enq(test_q1);
		vq_enq(test_q1);
		vq_enq(test_q1);
		test_node3 = vq_get_num(test_q1, 5);
		if(test_node3 != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Get Node Address By Node Number - Last Node");
		vq_clear(test_q2);
		test_node1 = list_ins_tail(test_q2);
		test_node2 = list_ins_tail(test_q2);
		test_node3 = list_get_num(test_q2, 2);
		if(test_node3 != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Get Node Address By Node Number - Empty List");
		vq_clear(test_q2);
		test_node1 = vq_get_num(test_q2, 1);
		if(test_node1 != NULL) result++;
		test_node1 = vq_get_num(test_q2, 55);
		if(test_node1 != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Queue - Swap Nodes In List");
		vq_clear(test_q2);
		test_node1 = vq_enq(test_q2);
		test_node2 = vq_enq(test_q2);
		test_node3 = vq_enq(test_q2);
		pTrack[1] = test_node1->pNext;
		pTrack[2] = test_node2->pNext;
		if(vq_node_swap(test_node1, test_node2) != 0) result++;
		if(test_node1->pNext != pTrack[2]) result++;
		if(test_node2->pNext != pTrack[1]) result++;
	test_msg_end(result);

	return result;
}

/* test outcome of sort algorithm - all data should be sorted */
int test_sort_data(int data[], int lo, int hi)
{
	int i = lo, result = 0;
	while(i < hi)
	{
		if(!(data[i] <= data[i+1])) result++;
		i++;
	}
	return result;
}

/* test specific position of data */
int test_sort_data_loc(int data[])
{
	int i = 0, result = 0;
	while(i < 10) {
		if(data[i] != i) result++;
		i++;
	}
	return result;
}

/* set pre-selected data in array */
void sort_set_array(int data[])
{
	assert(data != NULL);
	data[0] = 4;
	data[1] = 5;
	data[2] = 7;
	data[3] = 9;
	data[4] = 8;
	data[5] = 1;
	data[6] = 6;
	data[7] = 0;
	data[8] = 3;
	data[9] = 2;
}

/* fill random length array with random data */
void sort_rnd_data_fill(int *data, int length, int min, int max)
{
	int i = 0;
	random_seed();
	while(i < length) {
		data[i]= random_int(min, max);
		i++;
	}
}

int test_sort()
{
	int i, result = 0, length, min_data_val, max_data_val;
	int *temp_data;
	int data[10];

	test_msg_start("Test Selection Sort - Preset Array");
		sort_set_array(data);
		sort_selection(data, 0, 9);
		result += test_sort_data(data, 0, 9);
		result += test_sort_data_loc(data);
	test_msg_end(result);

	test_msg_start("Test Selection Sort - Random Data");
		for(i = 0; i < SORT_TESTS; i++) {
			random_seed();
			min_data_val = random_int(INT_MIN+1, (INT_MAX/2)-1);
			max_data_val = random_int(min_data_val, (INT_MAX/2)-1);
			length = random_int(500, 1000); /* get length of a new array */
			temp_data = malloc(sizeof(int) * length);
			sort_rnd_data_fill(temp_data, length, min_data_val, max_data_val);
			sort_selection(temp_data, 0, length);
			result += test_sort_data(temp_data, 0, length);
			free(temp_data);
			temp_data = NULL;
		}
	test_msg_end(result);

	test_msg_start("Test Insertion Sort - Preset Array");
		sort_set_array(data);
		sort_insertion(data, 0, 9);
		result += test_sort_data(data, 0, 9);
		result += test_sort_data_loc(data);
	test_msg_end(result);

	test_msg_start("Test Insertion Sort - Random Data");
		for(i = 0; i < SORT_TESTS; i++) {
			random_seed();
			min_data_val = random_int(INT_MIN+1, (INT_MAX/2)-1);
			max_data_val = random_int(min_data_val, (INT_MAX/2)-1);
			length = random_int(500, 1000); /* get length of a new array */
			temp_data = malloc(sizeof(int) * length);
			sort_rnd_data_fill(temp_data, length, min_data_val, max_data_val);
			sort_insertion(temp_data, 0, length);
			result += test_sort_data(temp_data, 0, length);
			free(temp_data);
			temp_data = NULL;
		}
	test_msg_end(result);

	test_msg_start("Test Quick Sort (Recursive) - Preset Array");
		sort_set_array(data);
		sort_quick(data, 0, 9);
		result += test_sort_data(data, 0, 9);
		result += test_sort_data_loc(data);
	test_msg_end(result);

	test_msg_start("Test Quick Sort (Recursive) - Random Data");
		for(i = 0; i < SORT_TESTS; i++) {
			random_seed();
			min_data_val = random_int(INT_MIN+1, (INT_MAX/2)-1);
			max_data_val = random_int(min_data_val, (INT_MAX/2)-1);
			length = random_int(500, 1000); /* get length of a new array */
			temp_data = malloc(sizeof(int) * length);
			sort_rnd_data_fill(temp_data, length, min_data_val, max_data_val);
			sort_quick(temp_data, 0, length);
			result += test_sort_data(temp_data, 0, length);
			free(temp_data);
			temp_data = NULL;
		}
	test_msg_end(result);

	test_msg_start("Test Quick Sort - Preset Array");
		sort_set_array(data);
		sort_quick_norecurse(data, 0, 9);
		result += test_sort_data(data, 0, 9);
		result += test_sort_data_loc(data);
	test_msg_end(result);

	test_msg_start("Test Quick Sort - Random Data");
		for(i = 0; i < SORT_TESTS; i++) {
			random_seed();
			min_data_val = random_int(INT_MIN+1, (INT_MAX/2)-1);
			max_data_val = random_int(min_data_val, (INT_MAX/2)-1);
			length = random_int(500, 1000); /* get length of a new array */
			temp_data = malloc(sizeof(int) * length);
			sort_rnd_data_fill(temp_data, length, min_data_val, max_data_val);
			sort_quick_norecurse(temp_data, 0, length);
			result += test_sort_data(temp_data, 0, length);
			free(temp_data);
			temp_data = NULL;
		}
	test_msg_end(result);

	return result;
}

int test_hash()
{
	int result = 0;
	Hash h;
	test_msg_start("Test Hash - Prime Number Generator");
		if(is_prime(0)) result++;
		if(is_prime(1)) result++;
		if(!is_prime(2)) result++;
		if(!is_prime(3571)) result++;
		if(is_prime(3570)) result++;
	test_msg_end(result);

	test_msg_start("Test Hash - Twin Prime Number Generator");
		if(next_twinprime(6) != 7) result++;
		if(next_twinprime(72) != 73) result++;
		if(next_twinprime(1000) != 1021) result++;
		if(next_twinprime(79154) != 79231) result++;
		if(next_twinprime(INT_MAX) != -1) result++;
	test_msg_end(result);

	test_msg_start("Test Hash - Create New Hash");
	 	h = hash_new_prime(100);
	 	if(hash_empty(h) != 0) result++;
	 	if(h.size != 103) result++;
	 	if(h.data == NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Hash - Insert and Verify Data");
		hash_insert(h, "hello", 6);
		if(hash_search(h, "hello", 6) == NULL) result++;
		if(hash_search(h, "goodbye", 7) != NULL) result++;
		if(hash_search(h, "", 0) != NULL) result++;
	test_msg_end(result);

	test_msg_start("Test Hash - Fill Hash and Clear Data");

		/* if(hash_full(h) != 0) result++; */
	test_msg_end(result);

	test_msg_start("Test Hash - Fill Hash and Remove Specific Data");
	test_msg_end(result);

	test_msg_start("Test Hash - Insert and Verify Data");
	test_msg_end(result);

	return result;
}

int test_all()
{
	int result = 0;
	result += test_random();
	result += test_linked_list();
	result += test_vstack();
	result += test_vqueue();
	result += test_sort();
	/* result += test_hash(); HASH IS NOT COMPLETE */
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
