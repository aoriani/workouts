#include "listint.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Define a prettier assert if we're using GCC
#ifdef __GNUC__
	#define ASSERT(expr) if (!(expr)) { \
	                        fprintf(stderr,"In %s@%s:%d: assertion failed - %s\n", __PRETTY_FUNCTION__,__FILE__,__LINE__,#expr);\
	                        abort(); \
	                       }
							
#else
	#define ASSERT(expr) assert((expr))
#endif

typedef void (*testcase)(void); 


void test_init(){
        listint_t list;
        list_init(&list);
        ASSERT(list.used == 0);
        ASSERT(list.capacity == 4);
        ASSERT(list.array != NULL);
}

void test_insert_front(){
        listint_t list;
        list_init(&list);
        list_insert_front(&list,0);
        ASSERT(list.used == 1);
        ASSERT(list.array[0] == 0);
        //cause a resize
        list_insert_front(&list,1);
        list_insert_front(&list,2);
        list_insert_front(&list,3);
        list_insert_front(&list,4);
        ASSERT(list.used == 5);
        ASSERT(list.capacity == 8);
        for(int i = 0; i < list.used; i++){
                ASSERT(list.array[4-i] == i);
        }
}

void test_insert_back(){
        listint_t list;
        list_init(&list);
        list_insert_back(&list,0);
        ASSERT(list.used == 1);
        ASSERT(list.array[0] == 0);
        //cause a resize
        list_insert_back(&list,1);
        list_insert_back(&list,2);
        list_insert_back(&list,3);
        list_insert_back(&list,4);
        ASSERT(list.used == 5);
        ASSERT(list.capacity == 8);
        for(int i = 0; i < list.used; i++){
                ASSERT(list.array[i] == i);
        }
}

int main(){

        testcase testcases[]={
                test_init,
                test_insert_front,
                test_insert_back        
        };

        const int ntest_cases = sizeof(testcases)/sizeof(testcase);
        
        for (int i=0; i < ntest_cases; i++){
                (*testcases[i])();
        }

        puts("All tests passed !\n");

        return 0;
}
