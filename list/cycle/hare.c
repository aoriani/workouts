#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Memory allocation macros */
#define CHK_PTR(ptr) if(ptr == NULL) { \
                            fprintf(stderr,"Null pointer - %s:%d-%s\n", __FILE__ , __LINE__, __PRETTY_FUNCTION__ ); \
                            abort(); \
                            }

#define ALLOC_NODE() ({ void* __mem = malloc(sizeof(Node)); CHK_PTR(__mem);memset(__mem,0,sizeof(Node));(Node*) __mem;})



/** Unit testing macros */

#define ASSERT_TRUE(expr,error_string) if (!(expr)) {\
                                            fprintf (stderr,"FAILED: %s in %s at %s:%d: %s\n", \
                                                        #expr,__PRETTY_FUNCTION__,__FILE__,__LINE__,error_string); \
                                       }

#define ASSERT_FALSE(expr,error_string) ASSERT_TRUE(!(expr),error_string)
                            


typedef struct Node{
    int value;
    struct Node* next;
} Node;

/**
 *   Implementation of Floyd's cycle detection algorithm
 */

int floyd_has_cycle(Node* head){
   //Empty graph
   if(head == NULL) return 0;
   
   Node *fast=head, *slow=head;
   
   while(1){
       fast = fast->next;
       if(fast == NULL) return 0;
       if(fast == slow) return 1;
       
       fast = fast->next;
       if(fast == NULL) return 0;
       if(fast == slow) return 1;
       
       slow = slow->next;
   }
}

/**
 * Implementation of Brent's cycle detection algorithm
 */


int brent_has_cycle(Node* head){
    //Empty list
    if(head == NULL) return 0;
    
    int steps = 2 ;
    Node *fast=head, *slow=head;
    
    while(1){
        int i;
        for(i = 0; i < steps; i++){
            fast = fast->next;
            if(fast == NULL){
                return 0;
            }else if(fast == slow){
                return 1;
            } 
        }
        
        //Teleport turtle
        slow = fast;
        steps *= 2;        
    }
}

//Test cases

void testEmptyList(void){
    ASSERT_FALSE(floyd_has_cycle(NULL),"Empty list should not have cycles");
    ASSERT_FALSE(brent_has_cycle(NULL),"Empty list should not have cycles");
}

void testSingleElementListNoCycle(void){
    Node a;
    a.next = NULL;
    
    ASSERT_FALSE(floyd_has_cycle(&a),"Single list should not have cycles");
    ASSERT_FALSE(brent_has_cycle(&a),"Single list should not have cycles");
}

void testSingleElementListCycle(void){
    Node a;
    a.next = &a;
    
    ASSERT_TRUE(floyd_has_cycle(&a),"Single list should have cycles");
    ASSERT_TRUE(brent_has_cycle(&a),"Single list should have cycles");
}

void testTwoElementListNoCycle(void){
    Node* a = ALLOC_NODE();
    Node* b = ALLOC_NODE();   
    a->next = b;
    
    ASSERT_FALSE(floyd_has_cycle(a),"Two element list should not have cycles");
    ASSERT_FALSE(brent_has_cycle(a),"Two element list should not have cycles");
    
    free(a);
    free(b);
}

void testTwoElementListCycle(void){
    Node* a = ALLOC_NODE();
    Node* b = ALLOC_NODE();   
    a->next = b;
    b->next = a;
    
    ASSERT_TRUE(floyd_has_cycle(a),"Two element list should not have cycles");
    ASSERT_TRUE(brent_has_cycle(a),"Two element list should not have cycles");
    
    free(a);
    free(b);
}

void testBigCycleList(void){
    Node a,b,c,d,e,f,g,h,i;
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    g.next = &h;
    h.next = &i;
    i.next = &d;
    
    ASSERT_TRUE(floyd_has_cycle(&a),"big list should not have cycles");
    ASSERT_TRUE(brent_has_cycle(&a),"big  list should not have cycles");

}

//Run test suite
int main(void){

    printf("Running test empty list..\n");
    testEmptyList();

    printf("Running single element list with no cycle..\n");
    testSingleElementListNoCycle();
    
    printf("Running single element list with cycle..\n");
    testSingleElementListCycle();
    
    printf("Running two element list with no cycle..\n");
    testTwoElementListNoCycle();

    printf("Running two element list with cycle..\n");
    testTwoElementListCycle();

    printf("Running two element list with cycle..\n");
    testTwoElementListCycle();

    printf("Running big list with cycle..\n");
    testBigCycleList();
    
    return EXIT_SUCCESS;
}
