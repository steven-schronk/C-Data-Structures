#ifndef LIB_RANDOM_H_
#define LIB_RANDOM_H_

/* generate random number from min to max */
int random_int(int min, int max);

/* use clock in system to create random seed for number generator */
void random_seed();

#endif /* LIB_RANDOM_H_ */
