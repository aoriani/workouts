#include<stdio.h>
#include <assert.h>


/*
 * Returns the mth-to-last element in single linked-list
 *
 * If a know the size of the list I can calc how many link I should traverse
 * But in this case I don't know so I have to walk through the whole list
 */


typedef struct node_t{
    char data;
    struct node_t* next;
}node_t;

/**
 * Returns the data  for the mth element starting from the end of the list
 *
 * @param m the element to be return
 * @param head the the head of the list
 * @param result , store the data from the requested element
 *
 * @returns 1 if such elements exist and it is safe to read data. O otherwise 
 */

int m_to_last(int m, node_t* head, char* result){
    node_t *aux = head, *mtolast = head;
    int distance = 0;
    
    //Sanity check
    if(head == NULL || result == NULL || m < 0) return 0;
    
    while(aux->next != NULL){
        aux = aux->next;
        if(distance < m) distance++;
        else mtolast=mtolast->next;         
    }

    //walked enough to get a result?
    if(distance == m){
        *result = mtolast->data;
        return 1;
    }else return 0;

}

int main(){
    node_t a,b,c,d,e;
    a.data = 'a';
    b.data = 'b';
    c.data = 'c';
    d.data = 'd';
    e.data = 'e';
 
    a.next=&b;b.next=&c;c.next=&d;d.next=&e;e.next=NULL;
    
    char result;
    
    assert(m_to_last(0,NULL,&result) == 0);
    assert(m_to_last(-1, &a, &result) == 0);
    assert(m_to_last(0, &a, &result) == 1);
    assert (result == 'e');
    assert(m_to_last(3, &a, &result) == 1);
    assert (result == 'b');

    assert(m_to_last(3, &e, &result) == 0);
    assert(m_to_last(0, &e, &result) == 1);
    assert (result == 'e');
    
    return 0;
}

