#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_hash.h"

int is_prime(int num)
{
	int i;
	assert(num >= 0);
	if(num == 1 || num == 0) return 0;
	for(i = 2 ; i <= num / 2; i++)
		if(num % i == 0) return 0;
	return 1;
}

int next_twinprime(int num)
{
	assert(num >= 2);
	while(num < INT_MAX) {
		num++;
		if(is_prime(num) && is_prime(num-2))return num;
	}
	return -1;
}

Hash hash_new(int len)
{
	Hash h;
	assert(len >= 2);
	h.size = len;
	h.data = malloc(sizeof(int)*len);
	return h;
}

Hash hash_new_prime(int len)
{
	Hash h;
	assert(len >= 2);
	len = next_twinprime(len);
	h.size = len;
	h.data = malloc(sizeof(int)*len);
	return h;
}

int hash_data(void *data, int num, size_t size)
{
	int slot = 0;
	while(num >= 0)
	{
		/* slot += (void *) (data) + (num * size); */
		slot += (int)data + size * num;
		num--;
	}
	return slot;
}

int hash_insert(Hash h, void * data, size_t length)
{
	int slot;
	assert(data != NULL);
	/*slot = hash_data(data, length);
	if(h[slot]->data == NULL) *//* insert data in first node */;

	return 0;
}

void * hash_search(Hash h, void * data, size_t length)
{
	return NULL;
}

int hash_remove(Hash h, void * data, size_t length)
{
	assert(data != NULL);
	return 0;
}

int hash_empty(Hash h)
{
	return 0;
}

int hash_full(Hash h)
{
	return 0;
}

void hash_clear(Hash h)
{

}

void hash_print(Hash h)
{

}

void hash_delete(Hash h)
{
	free(&h);
}
