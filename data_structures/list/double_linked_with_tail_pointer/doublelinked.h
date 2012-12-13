#ifndef DOUBLE_LINKED_LIST_H__
#define DOUBLE_LINKED_LIST_H__


#include <iostream>
using std::cout;
using std::endl;

#include <cassert>

template <typename T>
class DoubleLinkedList{  
    
    
    public:
        DoubleLinkedList();
        DoubleLinkedList(const DoubleLinkedList&);
        ~DoubleLinkedList();
        const DoubleLinkedList& operator=(const DoubleLinkedList& list);
        void insertFront(const T& elem);
        void insertBack(const T& elem);
        bool insertAfter(const T& insertAfterElem, const T& elem);
        bool remove (const T& elem);
        void printList();
        void printListReverse();
    
    private:
        struct Node{
            T data;
            Node* next;
            Node* previous;
        };
    
        Node *head, *tail;
        
        void clearNodes(Node* start);

};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(){
    head = tail = 0;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& l){
    head = tail = 0;
    if (!l.head) return ; // nothing to copy
    
    Node* newnode = new Node;
    assert(newnode);
    newnode->data = l.head->data;
    newnode->previous = newnode->next = 0;
    head = tail = newnode;
    
    Node* auxL = l.head->next;
    while(auxL){
        newnode = new Node;
        newnode->data = auxL->data;
        newnode->previous = tail;
        newnode->next = 0;
        tail->next = newnode;
        tail = newnode;
        auxL = auxL->next;
    }

}


template <typename T>
void DoubleLinkedList<T>::clearNodes(Node* start){
    Node *prev = start, *current = start;
    while(current){
        current = current->next;
        delete prev;
        prev = current;
    }
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    clearNodes(head);    
    head = tail = 0;
}


template <typename T>
const DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& l){
    if( this != &l){
        
        //Copy phase      
        Node *auxthis = head, *auxL = l.head;
        while(auxthis && auxL){
            auxthis->data = auxL->data;
            tail = auxthis;
            auxthis = auxthis->next; auxL = auxL->next;
        }
        
        if(!auxthis && auxL) { //dst list is shorter
            while (auxL){
                Node* newnode = new Node;
                assert(newnode);
                newnode->data = auxL->data;
                newnode->next = 0;
                newnode->previous = tail;
                if(!tail) {// dst list was empty
                    head = newnode;
                }else{
                    tail->next = newnode;
                }
                tail = newnode;
                auxL = auxL->next;
            }
        }else if (auxthis && !auxL){ //dst list should nbe trimmed
            //terminate list
            tail->next = 0;
            
            //delete excess
            clearNodes(auxthis);
            
            if(!l.head) { //src list is empty
                head = tail = 0;
            }
        }
    
    }
    return *this;
}

template <typename T>
void DoubleLinkedList<T>::insertFront(const T& elem){
    Node* newnode = new Node;
    assert (newnode);
    newnode->data = elem;
    newnode->previous = 0;
    newnode->next = head;
    if(head){ 
        head->previous = newnode;
    } else { //insert the first element on the list
        tail = newnode;
    }
    head = newnode;
}


template <typename T>
void DoubleLinkedList<T>::insertBack(const T& elem){
    Node* newnode = new Node;
    assert(newnode);
    newnode->data = elem;
    newnode->next = 0;
    newnode->previous = tail;
    if (tail) {//it is not the first node
        tail->next = newnode;
    }else{
        head = newnode;
    }
    tail = newnode;
}

template <typename T>
bool DoubleLinkedList<T>::insertAfter(const T& insertAfterElem, const T& elem){
    if(!head) return false; // return empty
    
    Node* aux = head;
    while(aux){
        if(aux->data == insertAfterElem){
            Node* newnode = new Node;
            newnode->data = elem;
            newnode->next = aux->next;
            newnode->previous = aux;
            aux->next = newnode;
            if(tail == aux){ //new tail
                tail = newnode;
            }else{
                newnode->next->previous = newnode;
            }            
            return true;
        }
        aux = aux->next;
    }
    return false;
}


template <typename T>
bool  DoubleLinkedList<T>::remove(const T& elem){
    if(!head) return false; //empty list
    
    Node* aux = head;
    //find node to be removed
    while(aux){
        if(aux->data == elem){
            if( tail == head) { //single element list
                head = tail = 0;
            }else if(aux == head){ //removing head
                aux->next->previous = 0;
                head = aux->next;
            }else if ( aux == tail){ //removing tail
                 aux->previous->next = 0;
                 tail = aux->previous;
            }else{ // removing in the middle
                aux->previous->next = aux->next;
                aux->next->previous = aux->previous;
            }
            delete aux;
            return true;
        }
         aux = aux->next; // advances aux
    }
    return false; // did not found
    
}

template <typename T>
void DoubleLinkedList<T>::printList(){
    Node* aux = head;
    
    while (aux){
        cout<<aux->data<<" ";
        aux = aux->next;
    }
    cout<<endl;
}

template <typename T>
void DoubleLinkedList<T>::printListReverse(){
    Node* aux = tail;
    
    while (aux){
        cout<<aux->data<<" ";
        aux = aux->previous;
    }
    cout<<endl;
}



#endif //DOUBLE_LINKED_LIST_H__
