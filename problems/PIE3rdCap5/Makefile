.PHONY: clean

CFLAGS += -Wall -pedantic -g

all: bintreeHeap bacon

bintreeHeap: bintree2heap.cpp 
	$(CXX) $(CFLAGS) $< -o $@

bacon: bacon.cpp
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	@rm -f bintreeHeap bacon
	
