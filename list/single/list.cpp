#include <iostream>
#include <cassert>

class LinkedList 
{
    private:    
        struct Node
        {
            Node* next;
            int value;
            
            Node(int val);
        };
                
    public:
        class Iterator
        {
            friend class ::LinkedList;
            
            private:
                Node* current;
                Iterator(Node* current);
            public:
                bool hasNext() const;
                const int next();
        };
        
        Node* head;
        
        
        
        LinkedList();
        ~LinkedList();
        void insertAtFront(int value);
        bool remove(int value);
        Iterator* iterator() const;
        
};

LinkedList::Node::Node(int val)
{
    next = 0;
    value = val;
}

LinkedList::LinkedList()
{
    head = NULL;
}

LinkedList::~LinkedList()
{
    //No elements
    if(head == NULL) return;
    
    //Some element
    Node* predecessor = head;
    do{
       Node* current = predecessor->next;
       delete predecessor;
       predecessor = current;
    }while(predecessor != NULL);
}

void LinkedList::insertAtFront(int value)
{
    Node* newNode = new LinkedList::Node(value);
    newNode->next = head;
    head = newNode;
}

bool LinkedList::remove(int val)
{
    //Empty list
    if(head == NULL){
        return false;
    }else if (head->value == val){ //head has the value
        Node* aux = head;
        head = head->next;
        delete aux;
        return true;
    }else{
        Node* predecessor = head;
        Node* current = head->next;
        
        while(current != NULL){
            if(current->value == val){
                predecessor->next = current->next;
                delete current;
                return true;
            }else{
                predecessor = current;
                current = current->next;
            }
        }
        return false;
    }  
}

LinkedList::Iterator* LinkedList::iterator() const{
    LinkedList::Iterator* iterator = new Iterator(head);
    return iterator;
}

bool LinkedList::Iterator::hasNext() const{
    return (current != NULL);
}


LinkedList::Iterator::Iterator(Node* current){
    this->current = current;
}
const int LinkedList::Iterator::next(){
    if(current == NULL){
        throw "No more elements";
    }
    
    const int result = current->value;
    current = current->next;
    
    return result; 
}

void printList(const LinkedList& list){
    LinkedList::Iterator* iterator = list.iterator();
    
    while(iterator->hasNext()){
        std::cout<<iterator->next()<<" ";
    }
    std::cout<<std::endl;
    delete iterator;
}

int main(){

    LinkedList list;
    std::cout<<"Teste"<<std::endl;
    
    list.insertAtFront(1);
    list.insertAtFront(2);
    list.insertAtFront(3);
    list.insertAtFront(4);
    
    printList(list);
    
    assert(list.remove(3));
    printList(list);
    assert(list.remove(4));
    printList(list);
    assert(list.remove(1));
    printList(list);
    assert(list.remove(2));
    printList(list);
    assert(list.remove(5) == false);
    
    return 0;
}

