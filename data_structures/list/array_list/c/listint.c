#include "listint.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_CAPACITY 4

#define MAX(x,y) ((x)>(y))?(x):(y)

//==========================================================================
void list_init(listint_t* list){
	assert(list != NULL);
	list->capacity = 4;
	list->used = 0;
	list->array = (int*) malloc(list->capacity * sizeof(int));
	memset(list->array,0,list->capacity * sizeof(int));
	assert(list->array != NULL);
	
}

//==========================================================================
static void list_resize_array(listint_t* list, int size){
	//Ensure we have enough room to copy the array
	assert(size >= list->used);
	
	int* newarray = (int*) malloc(size * sizeof(int));
	memset(newarray,0,size * sizeof(int));
	assert(newarray != NULL);
	memcpy(newarray,list->array, list->used * sizeof (int));
	
	list->capacity = size;
	free(list->array);
	list->array = newarray;
}

//==========================================================================
void list_insert_front(listint_t* list, int value){
	//Check if we need to resize
	if((list->used + 1) > list->capacity){
		list_resize_array(list, (2 * list->capacity));
	}
	
	//move elements to one position left
	memmove((list->array)+1, list->array, list->used * sizeof(int));
	list->array[0] = value;
	list->used++;
}
						  						  
//==========================================================================
void list_insert_back(listint_t* list, int value){
	//Check if we need to resize
	if((list->used + 1) > list->capacity){
		list_resize_array(list, (2 * list->capacity));
	}
	
	list->array[list->used] = value;
	list->used++;
}

//==========================================================================
//Rounds up to the next power of 2. If value is a power of 2, it returns value
static unsigned int roundup2pw(unsigned int value){
	unsigned int i = 0u;
	while (value !=0) {
		value >>= 1u;
		i++;
	}
	
	return 1u<<i;
}

//==========================================================================
void list_insert_at(listint_t* list, unsigned int pos, int value){
	
	unsigned int new_used = MAX(list->used+1, pos+1);

	//Check if we need to resize
	if((new_used) > list->capacity){
		list_resize_array(list, roundup2pw(new_used));
	}
	
	//Open space in the array
	if (pos < list->used){
	    memmove((list->array + pos + 1),(list->array + pos),
	                                        (list->used - pos)*sizeof(int));
	}
    
    list->array[pos] = value;
    list->used = new_used;
}

//==========================================================================
bool list_contains(const listint_t* list,int value){
	for (unsigned int i = 0u; i < list->used; i++) {
		if (list->array[i] == value){
			return TRUE;
		}
	}
	return FALSE;
}

//==========================================================================
static inline void list_downsize_ifneed(listint_t* list){
	if ((list->used > 0) && (list->used < (list->capacity/4))) {
		list_resize_array(list,list->capacity/2);
	}
}

//==========================================================================
void list_finalize(listint_t* list){
        free(list->array);
        list->array = NULL;
        list->capacity = list->used = 0;
}

//==========================================================================
bool list_remove(listint_t* list, int value){

	for (unsigned int i = 0u; i < list->used; i++) {
		if (list->array[i] == value){
			//We found our element to remove
			list->used--;
			memmove(list->array + i, list->array + i + 1,
			                             (list->used-i)*sizeof(int));
			return TRUE;
		}
	}
	return FALSE;	
}

//==========================================================================
int list_pop_front(listint_t* list){
	assert(list->used > 0);
	int result = list->array[0];
	list->used--;
	
	//move all the other elements to cover the hole open by the 0th element
	memmove(list->array, (list->array+1), list->used * sizeof(int));
	
	//Verify need for downsize
        list_downsize_ifneed(list);	
	
	return result;
}

//==========================================================================
int list_pop_back(listint_t* list){
	assert(list->used > 0);
	int result = list->array[--list->used];
	
	//Verify need for downsize
        list_downsize_ifneed(list);
	
	return result;
}





