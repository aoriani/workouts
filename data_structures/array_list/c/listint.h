#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>

typedef int bool;
#define TRUE 1
#define FALSE 0


//The ADT representing the list
typedef struct listint_t{
	unsigned int used, capacity;
	int* array;
}listint_t;

//Initialize the list
void list_init(listint_t* list);

//Insert value on front of the list
void list_insert_front(listint_t* list, int value);

//Insert value in the back of the list
void list_insert_back(listint_t* list, int value);

//Insert value in the position especified by pos
void list_insert_at(listint_t* list, unsigned int pos, int value);

//Returns the current size of the list
inline unsigned int list_size(const listint_t* list){
	return list->used;
}

//Retuns the current capacity of the list
inline unsigned int list_capacity(const listint_t* list){
	return list->capacity;
}

//Verify if an element it is in the list
bool list_contains(const listint_t* list,int value);

//Return the element at the specified position
inline int list_element_at(const listint_t* list, unsigned int pos){
	assert(pos < list->used);
	return list->array[pos];
}

//Remove an especified element from the list
//Return true if removed, false otherwise
bool list_remove(listint_t* list, int value);

//Removes the  element from the front return it
int list_pop_front(listint_t* list);

//Removes the  element from the back return it
int list_pop_back(listint_t* list);

//Free memory associated the list
void list_finalize(listint_t* list);

#endif // LIST_H_
