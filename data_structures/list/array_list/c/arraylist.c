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
        
        ASSERT(list_size(&list) == 0);
        ASSERT(list_capacity(&list) == 4);
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
        ASSERT(list_size(&list) == 5);
        ASSERT(list_capacity(&list) == 8);
        for(int i = 0; i < list.used; i++){
                ASSERT(list_element_at(&list,4-i) == i);
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
        ASSERT(list_size(&list) == 5);
        ASSERT(list_capacity(&list) == 8);
        for(int i = 0; i < list.used; i++){
                ASSERT(list_element_at(&list,i) == i);
        }
        
       list_finalize(&list);
}


void test_insert_at(){
        listint_t list;
        list_init(&list);
        
        //Insert first
        list_insert_at(&list,0,1);
        ASSERT(list_size(&list) == 1);
        ASSERT(list.array[0] == 1);
        //Insert second
        list_insert_at(&list,1,4);
        ASSERT(list_size(&list) == 2);
        ASSERT(list.array[1] == 4);
        //Insert between
        list_insert_at(&list,1,3);
        ASSERT(list_size(&list) == 3);
        ASSERT(list_element_at(&list,0) == 1);
        ASSERT(list_element_at(&list,1) == 3);
        ASSERT(list_element_at(&list,2) == 4);
        list_insert_at(&list,1,2);
        ASSERT(list_size(&list) == 4);
        ASSERT(list_element_at(&list,0) == 1);
        ASSERT(list_element_at(&list,1) == 2);
        ASSERT(list_element_at(&list,2) == 3);
        ASSERT(list_element_at(&list,3) == 4);
        //insert beyond and close to power of 8
        list_insert_at(&list,7,8);
        ASSERT(list_size(&list) == 8);
        ASSERT(list_capacity(&list) == 16);
        ASSERT(list_element_at(&list,0) == 1);
        ASSERT(list_element_at(&list,1) == 2);
        ASSERT(list_element_at(&list,2) == 3);
        ASSERT(list_element_at(&list,3) == 4);
        ASSERT(list_element_at(&list,7) == 8);
       
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
        listint_t list;
        list_init(&list);
        
        //Add one an then remove
        list_insert_back(&list,1906);
        ASSERT(list_size(&list) == 1);
        ASSERT(list_pop_back(&list) == 1906);
        ASSERT(list_size(&list) == 0);
        
        //Test reducing capacity
        for (int i = 0; i < 5 ; i++){
                list_insert_back(&list,i);
        }        
        ASSERT(list_capacity(&list) == 8);
        for(int j = 4; j >= 0; j--){
                ASSERT(list_pop_back(&list) == j);
        }
        ASSERT(list_capacity(&list) == 4);
        
        list_finalize(&list);
}


void test_pop_front(){
        listint_t list;
        list_init(&list);
        
        //Add one an then remove
        list_insert_back(&list,1906);
        ASSERT(list_size(&list) == 1);
        ASSERT(list_pop_front(&list) == 1906);
        ASSERT(list_size(&list) == 0);
        
        //Test reducing capacity
        for (int i = 0; i < 5 ; i++){
                list_insert_back(&list,i);
        }        
        ASSERT(list_capacity(&list) == 8);
        for(int j = 0; j < 5; j++){
                ASSERT(list_pop_front(&list) == j);
        }
        ASSERT(list_capacity(&list) == 4);
        
        list_finalize(&list);
}

void test_remove(){
        listint_t list;
        list_init(&list);
        
        //Remove empty list
        ASSERT(list_remove(&list,55) == FALSE);
        
        //Add one then remove 
        list_insert_back(&list,1);
        ASSERT(list_remove(&list,0) == FALSE);
        ASSERT(list_size(&list) == 1);
        ASSERT(list_remove(&list,1) == TRUE);
        ASSERT(list_size(&list) == 0);
        
        list_insert_back(&list,1);
        list_insert_back(&list,2);
        list_insert_back(&list,3);
        list_insert_back(&list,4);
        //Remove in some random order
        ASSERT(list_remove(&list,3) == TRUE);
        ASSERT(list_size(&list) == 3);        
        ASSERT(list_element_at(&list,0) == 1);
        ASSERT(list_element_at(&list,1) == 2);
        ASSERT(list_element_at(&list,2) == 4);
        //Remove 
        ASSERT(list_remove(&list,1) == TRUE);
        ASSERT(list_size(&list) == 2);
        ASSERT(list_element_at(&list,0) == 2);
        ASSERT(list_element_at(&list,1) == 4);
        
        ASSERT(list_remove(&list,2) == TRUE);
        ASSERT(list_size(&list) == 1);
        ASSERT(list_element_at(&list,0) == 4);
        
        ASSERT(list_remove(&list,4) == TRUE);
        ASSERT(list_size(&list) == 0);
        ASSERT(list_remove(&list,4) == FALSE);

        list_finalize(&list);
}

int main(){

        testcase testcases[]={
                test_init,
                test_insert_front,
                test_insert_back,
                test_insert_at,
                test_contains,
                test_pop_back,
                test_pop_front,
                test_remove,        
        };

        const int ntest_cases = sizeof(testcases)/sizeof(testcase);
        
        for (int i=0; i < ntest_cases; i++){
                (*testcases[i])();
        }

        puts("All tests passed !\n");

        return 0;
}
