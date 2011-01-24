#include <stdio.h>
#include <stdlib.h>

#include "lib_sort.h"
#include "lib_ll.h"
#include "lib_vstack.h"

void sort_selection(int list[], int lo, int hi)
{
	int s, j;
	for(j = lo; j < hi; j++)
	{
		s = sort_get_smallest(list, j ,hi);
		sort_swap(list, j, s);
	}
}

void sort_insertion(int list[], int lo, int hi)
{
	int j, k, key;
	for(j = lo+1; j <= hi; j++)
	{
		key = list[j];
		k = j -1;
		while(k >= lo && key < list[k])
		{
			list[k+1] = list[k];
			--k;
		}
		list[k+1] = key;
	}
}

void sort_heap(int num[], int n)
{
	int k, item;
	for(k = n/2; k >= 1; k--) sort_shift_down(num[k], num, k, n);
	for(k = n; k > 1; k--)
	{
		item = num[k];
		num[k] = num[1];
		sort_shift_down(item, num, 1, k-1);
	}
}

void sort_quick(int a[], int lo, int hi)
{
	if(lo < hi)
	{
		int dp = sort_partition(a, lo, hi);
		sort_quick(a, lo, dp-1);
		sort_quick(a, dp+1, hi);
	}
}

void swap(int list[], int i, int j) {
	int hold = list[i];
	list[i] = list[j];
	list[j] = hold;
}

int partition2(int a[], int lo, int hi)
{
	int pivot = a[lo];
	--lo; ++hi;
	while(lo < hi) {
		do --hi; while(a[hi] > pivot);
		do ++lo; while(a[lo] < pivot);
		if(lo < hi) swap(a, lo, hi);
	}
	return hi;
}

void sort_quick_norecurse(int a[], int lo, int hi)
{
	int stackItems = 1, maxStackItems = 1;
	int dp;
	Stack_Head *pHead = vstack_new();
	Stack_Node *pNode = NULL;
	Sort_Data *pData = NULL;
	pNode = vstack_push(pHead);
	pNode->pData = sort_data_new(lo, hi);
	while(pHead->count != 0)
	{
		--stackItems;
		pNode = vstack_peek(pHead);
		pData = pNode->pData;
		vstack_pop(pHead);
		if(pData->left < pData->right){
			dp = partition2(a, pData->left, pData->right);
			if(dp - pData->left + 1 < pData->right - dp) {
				vstack_push_data(pHead, sort_data_new(dp+1, pData->right)); /* update the push function to accept data */
				vstack_push_data(pHead, sort_data_new(pData->left, dp));
			} else {
				vstack_push_data(pHead, sort_data_new(pData->left, dp));
				vstack_push_data(pHead, sort_data_new(dp+1, pData->right));
			}
			stackItems += 2;
		}
		if(stackItems > maxStackItems)maxStackItems = stackItems;
	}
}

void sort_shift_down(int key, int num[], int root, int last)
{
	int bigger = 2 * root;
	while(bigger <= last)
	{
		if(bigger < last)
				if(num[bigger+1] > num[bigger]) bigger++;
		if(key >= num[bigger]) break;
		num[root] = num[bigger];
		root = bigger;
		bigger = 2 * root;
	}
	num[root] = key;
}

int sort_partition(int a[], int lo, int hi)
{
	int pivot = a[lo];
	int last_sm = lo, j;
	for(j = lo + 1; j <= hi; j++)
	{
		if(a[j] < pivot)
		{
			++last_sm;
			sort_swap(a, last_sm, j);
		}
	}
	sort_swap(a, lo, last_sm);
	return last_sm;
}

int sort_get_smallest(int list[], int lo, int hi)
{
	int j, small = lo;
	for(j = lo + 1; j <= hi; j++)
		if(list[j] < list[small]) small = j;
	return small;
}

void sort_swap(int list[], int i , int j)
{
	int hold = list[i];
	list[i] = list[j];
	list[j] = hold;
}

Sort_Data *sort_data_new(int a, int b)
{
	Sort_Data *pData = malloc(sizeof(Sort_Data));
	pData->left = a;
	pData->right = b;
	return pData;
}
