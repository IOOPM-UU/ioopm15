CC     = clang
CCOPTS = -g -ggdb -Wall -Werror -std=c11 -D_GNU_SOURCE

CODEFILES=$(shell ls *.c *.h)

all: doc test

main: main.c network.o util.o
	$(CC) $(CCOPTS) network.o graph.o util.o list.o main.c -o main

doc: $(CODEFILES)
	doxygen travel_planner.doxy

network.o: graph.o network.c network.h
	$(CC) $(CCOPTS) -c network.c

graph.o: list.o graph.c graph.h util.o
	$(CC) $(CCOPTS) -c graph.c

list.o: list.c list.h util.o
	$(CC) $(CCOPTS) -c list.c

util.o: util.h util.c
	$(CC) $(CCOPTS) -c util.c

test: main list_test graph_test network_test
.PHONY: test

list_test: list_test.c list.o util.o
	$(CC) $(CCOPTS) list_test.c list.o util.o -lcunit -o list_test
	./list_test
.PHONY: list_test

graph_test: graph_test.c graph.o list.o
	$(CC) $(CCOPTS) graph_test.c graph.o list.o util.o -lcunit -o graph_test
	./graph_test
.PHONY: graph_test

network_test: network_test.c network.o graph.o list.o
	$(CC) $(CCOPTS) network_test.c network.o graph.o list.o util.o -lcunit -o network_test
	./network_test
.PHONY: network_test

clean:
	rm -f *.o
	rm -f main
	rm -f list_test
	rm -f graph_test
	rm -f network_test

.PHONY: clean
