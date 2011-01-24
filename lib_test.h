#ifndef LIB_TEST_H_
#define LIB_TEST_H_

/* Unit tests for the data structures. */

/* convenient method to exit with message for user */
void exit_error(const char*);

/* Prints standardized message about the type of test */
void test_msg_start(char*);

/* Prints results of test message - exits if failed */
void test_msg_end(int);

int test_ll_new();

int test_all();

#endif /* LIB_TEST_H_ */
