bad:	driver.c stack.c
	gcc -o $@ $^

good:	driver2_0.c stack2_0.c
	gcc -o $@ $^

stack_test:	stack_test.c stack.c
	gcc -o $@ $^ -lcunit

test:	stack_test
	@./stack_test


clean:
	rm -f bad good stack_test *.xml *.o

