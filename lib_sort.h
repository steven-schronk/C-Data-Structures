#ifndef LIB_SORT_H_
#define LIB_SORT_H_

typedef struct {
	int left;
	int right;
} Sort_Data;

int sort_get_smallest(int[], int, int);

void sort_swap(int[], int, int);

void sort_selection(int[] , int, int);

void sort_insertion(int[], int, int);

void sort_heap(int[], int);

void sort_quick(int[], int, int);

void sort_quick_norecurse(int[], int, int);

int sort_partition(int[], int, int);

void sort_shift_down(int, int[], int, int);

Sort_Data *sort_data_new(int, int);

#endif /* LIB_SORT_H_ */
