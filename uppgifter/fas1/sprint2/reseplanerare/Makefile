CCOPTS=-g -ggdb -Wall -Werror

CODEFILES=$(shell ls *.c *.h)

all: doc test

main: main.c network.o util.o
	clang $(CCOPTS) network.o graph.o util.o list.o main.c -o main

doc: $(CODEFILES)
	doxygen travel_planner.doxy

network.o: graph.o network.c network.h
	clang $(CCOPTS) -c network.c

graph.o: list.o graph.c graph.h util.o
	clang $(CCOPTS) -c graph.c

list.o: list.c list.h util.o
	clang $(CCOPTS) -c list.c

util.o: util.h util.c
	clang $(CCOPTS) -c util.c

test: main list_test graph_test network_test
.PHONY: test

list_test: list_test.c list.o util.o
	clang $(CCOPTS) -lcunit list_test.c list.o util.o -o list_test
	./list_test
.PHONY: list_test

graph_test: graph_test.c graph.o list.o
	clang $(CCOPTS) -lcunit graph_test.c graph.o list.o util.o -o graph_test
	./graph_test
.PHONY: graph_test

network_test: network_test.c network.o graph.o list.o
	clang $(CCOPTS) -lcunit network_test.c network.o graph.o list.o util.o -o network_test
	./network_test
.PHONY: network_test

clean:
	rm -f *.o
	rm -f main
	rm -f list_test
	rm -f graph_test
	rm -f network_test

.PHONY: clean
