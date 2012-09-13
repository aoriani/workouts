CC=gcc
VALGRING=valgrind
GCOV=gcov
CFLAGS=-std=c99 -g3 -O0 -Wall -pedantic
SOURCES=arraylist.c listint.c
EXECUTABLE=arraylist


all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)

clean:
	rm *.gcov *.gcda *.gcno

valgrind:
	$(VALGRIND) ./$(EXECUTABLE)
	
gcov: CFLAGS+=-fprofile-arcs -ftest-coverage
gcov: all

	

