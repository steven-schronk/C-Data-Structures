#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_test.h"
#include "lib_ll.h"

#define PASSED 0
#define FAILED 1

void exit_error(const char *err_msg)
{
	fprintf(stderr, "ERROR %s\n", err_msg);
	/*
	if(pInfile != NULL) { fclose(pInfile); }
	if(pOutfile != NULL) { fclose(pOutfile); }
	*/
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
		printf("FAILED\n");
		exit_error("UNIT TESTING FAILED");
	}
}

/* unit tests begin here */

int test_linked_list()
{
	int result = 0;
	List_Node *test_node = NULL;
	List_Node *test_node2 = NULL;
	List_Head *test_list = list_new();

	test_msg_start("Testing Linked List Creation");
	if(test_list == NULL) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List Empty Length - Using Variable");
	if(test_list->count != 0) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List Empty Length - Using Length Function");
	if(list_len(test_list) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Adding Node To Empty List");
	if(list_ins_tail(test_list) == NULL) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Adding Node To Non-Empty List");
	if(list_ins_tail(test_list) == NULL) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Clearing List With More Than One Node");
	list_clear(test_list);
	if(test_list->count != 0) result++;
	if(list_len(test_list) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Clearing List With No Nodes");
	list_clear(test_list);
	if(test_list->count != 0) result++;
	if(list_len(test_list) != 0 ) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List End - No Nodes");
	list_clear(test_list);
	if(list_tail(test_list) != NULL) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List End - One Node Only");
	list_clear(test_list);
	test_node = list_ins_tail(test_list);
	if(test_node == NULL) result++;
	if(list_tail(test_list) != test_node) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List End - More Than One Node");
	list_clear(test_list);
	list_ins_tail(test_list);
	test_node = list_ins_tail(test_list);
	if(test_node == NULL) result++;
	if(list_tail(test_list) != test_node) result++;
	test_msg_end(result);

	/*
	test_msg_start("Testing Linked List - Deleting List");
	list_delete(test_list);
	if(list_len(test_list) != -1) result++;
	test_msg_end(result);
	*/

	test_msg_start("Testing Linked List - Removing Node From List With More Than One Node");
	list_clear(test_list);
	test_node = list_ins_tail(test_list);
	test_node2 = list_ins_head(test_list);
	list_rm_node(test_list, test_node);
	if(test_list->pNext != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Removing Node From Empty List");
	list_clear(test_list);
	test_node = (List_Node*)&test_list; /* pointer points to known bad location */
	/* should not crash but return gracefully */
	if(list_rm_node(test_list, test_node) != -1) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Inserting Node After");
	list_clear(test_list);
	test_node = NULL;
	test_node2 = NULL;
	test_node = list_ins_tail(test_list);
	test_node2 = list_ins_after(test_list, test_node);

	 /* test beginning */
	if(test_list->pNext != test_node) result++;
	 /*...and end nodes. */
	if(list_tail(test_list) != test_node2) result++;
	/* end node next should be null */
	if(list_tail(test_list)->pNext != NULL) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Inserting Node Before");
	list_clear(test_list);
	test_node = NULL;
	test_node2 = NULL;
	test_node = list_ins_head(test_list);
	test_node2 = list_ins_before(test_list, test_node);

	/* test beginning */
	if(test_list->pNext != test_node2) result++;
	/*...and end nodes. */
	if(list_tail(test_list) != test_node) result++;
	/* end node next should be null */
	if(list_tail(test_list)->pNext != NULL) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Test Lengths");
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

	/* removing nodes from various places */
	list_rm_node(test_list, test_list->pNext);
	if(list_len(test_list) != 3) result++;

	list_rm_node(test_list, list_tail(test_list));
	if(list_len(test_list) != 2) result++;

	test_msg_end(result);

	test_msg_start("Testing Linked List - List Next Preprocessor");
	list_clear(test_list);
	test_node = NULL;
	test_node2 = NULL;
	test_node = list_ins_tail(test_list);
	test_node2 = list_ins_tail(test_list);
	if(list_next(test_node) == test_node) result++;
	if(list_next(test_node) != test_node2) result++;
	/* add stuff here */
	test_msg_end(result);

	test_msg_start("Testing Linked List - List Data Preprocessor");
	/* default payload should be null */
	if(list_data(test_node2) != NULL) result++;

	/* make data point to something and test again... */
	test_node2->pData = test_node2;
	if(list_data(test_node2) != test_node2) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - List Is Head Preprocessor");
	if(list_is_head(test_list, test_node2) != 0) result++;
	if(list_is_head(test_list, test_node) != 1) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - List Is Tail Preprocessor");
	if(list_is_tail(test_node2) != 1) result++;
	if(list_is_tail(test_node) != 0) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - List Head Preprocessor");
	if(list_head(test_list) != test_node) result++;
	test_msg_end(result);

	test_msg_start("Testing Linked List - Inserting Node Before");
	/* add stuff here */
	test_msg_end(result);

	return result;
}

int test_all()
{
	int result = 0;
	result += test_linked_list();
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
