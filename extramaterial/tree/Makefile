CC_COMPILER = gcc-5
CC_FLAGS    = -Wall -g

test:	test.c set.o tree.o
	$(CC_COMPILER) $(CC_FLAGS) $^ -o $@

set.o:	set.c
	$(CC_COMPILER) $(CC_FLAGS) $? -c -o $@

tree.o:	tree.c
	$(CC_COMPILER) $(CC_FLAGS) $? -c -o $@

clean:
	rm -f *.o set test test.dSYM
