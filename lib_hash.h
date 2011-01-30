#ifndef LIB_HASH_H_
#define LIB_HASH_H_

#define EMPTY 0

typedef struct hash {
	int * data;
	int size;
} Hash;

/*
	create new hash with len length
	returns null pointer when hash could not be created.
*/
Hash hash_new(int len);

/*
	same as hash_new accept:
	tests input length - determine if number is double prime.
	If not, finds next larger double prime for size of hash.
*/
Hash hash_new_prime(int len);

/* insert data into hash, must be sent with size of data */
int hash_insert(Hash h, void * data, size_t length);

/* search hash for data value, return address of data */
void * hash_search(Hash h, void * data, size_t length);

/* remove data from hash, must be sent with size of data removed */
int hash_remove(Hash h, void * data, size_t length);

/* test for empty hash - no data stored */
int hash_empty(Hash h);

/* test for hash that is completely full */
int hash_full(Hash h);

/* remove all data from hash */
void hash_clear(Hash h);

/* print hash contents to stdout - used for debugging */
void hash_print(Hash h);

/* delete hash and all its contents */
void hash_delete(Hash h);

/* find next double prime number - used for lenth of arrays */
int is_prime(int num);

/* find next prime number where number-2 is also prime */
int next_twinprime(int num);

#endif /* LIB_HASH_H_ */
