CC = gcc

OBJS = lib_test.o lib_hash.o lib_ll.o lib_random.o lib_sort.o lib_vbtree.o
PROG = dstruct
INSTALLDIR = /usr/local/bin

dstruct: CFLAGS = -Wall -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers

dstruct: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)

all: dstruct

