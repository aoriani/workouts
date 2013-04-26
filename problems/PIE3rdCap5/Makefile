.PHONY: clean

CFLAGS += -Wall -pedantic -g

all: bintreeHeap

bintreeHeap: bintree2heap.cpp 
	$(CXX) $(CFLAGS) $< -o $@

clean:
	@rm -f bintreeHeap
	
