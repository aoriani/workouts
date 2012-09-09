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
        
        list_finalize(&list);
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
        
        list_finalize(&list);
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
        
       list_finalize(&list);
}


void test_insert_at(){
        listint_t list;
        list_init(&list);
        
        //Insert first
        list_insert_at(&list,0,1);
        ASSERT(list.used == 1);
        ASSERT(list.array[0] == 1);
        //Insert second
        list_insert_at(&list,1,3);
        ASSERT(list.used == 2);
        ASSERT(list.array[1] == 3);
        //Insert between
        list_insert_at(&list,1,2);
        ASSERT(list.used == 3);
        ASSERT(list.array[0] == 1);
        ASSERT(list.array[1] == 2);
        ASSERT(list.array[2] == 3);
        //insert beyond and close to power of 8
        list_insert_at(&list,7,8);
        ASSERT(list.used == 8);
        ASSERT(list.capacity == 16);
        ASSERT(list.array[0] == 1);
        ASSERT(list.array[1] == 2);
        ASSERT(list.array[2] == 3);
        ASSERT(list.array[7] == 8);
        
        list_finalize(&list);        
}

void test_contains(){
        listint_t list;
        list_init(&list);
        
        //check not elements
        ASSERT(list_contains(&list, 51) == FALSE);
        
        for(int i = 0; i < 50; i++){
                list_insert_back(&list,i);
        }
        
        ASSERT(list_contains(&list, 10) == TRUE);
        ASSERT(list_contains(&list, 51) == FALSE);
        
        list_finalize(&list);        
}

void test_pop_back(){


}

int main(){

        testcase testcases[]={
                test_init,
                test_insert_front,
                test_insert_back,
                test_insert_at,
                test_contains        
        };

        const int ntest_cases = sizeof(testcases)/sizeof(testcase);
        
        for (int i=0; i < ntest_cases; i++){
                (*testcases[i])();
        }

        puts("All tests passed !\n");

        return 0;
}
