CC=g++
AR=ar
CFLAGS=-std=c++03 -Wall -pedantic -O0 -g3
GTEST_DIR=../../../support/test/cxx/gtest-1.6.0
GTEST_SOURCE=$(GTEST_DIR)/src/gtest-all.cc
GTEST_OBJECT=gtest-all.o
GTEST_STATIC_LIB=libgtest.a
HEADERS=list.h
SOURCES=list_test.cpp
EXECUTABLE=arraylist


arraylist:$(HEADERS) $(SOURCES) $(GTEST_STATIC_LIB)
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include $(SOURCES) $(GTEST_STATIC_LIB) -lpthread -o $@
	

$(GTEST_STATIC_LIB):
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include -I$(GTEST_DIR) -c $(GTEST_SOURCE)
	$(AR) -rv $@ $(GTEST_OBJECT)
	
	
clean:
	rm *.o *.a
	
valgrind:
	valgrind ./$(EXECUTABLE)
