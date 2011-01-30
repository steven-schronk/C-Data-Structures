#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "lib_random.h"

int random_int(int min, int max)
{
	assert(min > INT_MIN);
	assert(max < INT_MAX / 2);
	assert(max >= min);
	return rand() % max + min;
}

void random_seed()
{
	srand(time(0));
}
