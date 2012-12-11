CFLAGS= -W -Wall -O2

all: hare.o
	gcc $(CFLAGS)  hare.o -o hare

hare.o: hare.c 
	gcc $(CFLAGS) -c hare.c 

clean:
	rm -f hare.o

