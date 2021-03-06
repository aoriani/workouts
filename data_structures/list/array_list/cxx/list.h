#ifndef ORION_LIST_H
#define ORION_LIST_H

#include <cstdlib>
#include <stdexcept>
#include <new>

using std::size_t;

namespace orion{

    template <typename T>
    class List{
        private:
            static const size_t INITIAL_CAPACITY;
        
            size_t size;
            size_t capacity;
            T* array;
            
            void resize_array(size_t new_capacity);
            inline void downsizeIfNeeded(){
                //check if we need to downsize list
                if((size > 0 ) && (size < capacity/4)){
                    //if we using below 1/4, reduce array in half
                    resize_array(capacity/2);
                }
            }
            
        public:
            List();
            List(const List& list);
            ~List();
            const List& operator=(const List& list);
            inline size_t getSize() const { return size;}
            inline size_t getCapacity() const { return capacity;}
            inline bool isEmpty() { return size == 0;}
            void insert_front(const T& elem);
            void insert_back(const T& elem);
            T pop_front();
            T pop_back();
            bool contains(const T& elem);
            bool remove(const T& elem);
            const T& operator[] (const size_t index) const;
            T& operator[] (const size_t index);
            
            class Iterator;// forward declaration
            Iterator begin();
            Iterator end();
            
            class Iterator{
            
                friend class List<T>;    
                
                private:
                    List* list;
                    size_t currentPos;
                    
                    Iterator(List* list, size_t pos):list(list),currentPos(pos){}
                    
                public:
                    bool operator==(const Iterator& it) const;
                    bool operator!=(const Iterator& it) const;
                    T& operator*();
                    T* operator->();
                    Iterator& operator++(); //prefix form
                    Iterator operator++(int); //sufix form     
            };             
    };
}

//==============================================================================
template<typename T>
const size_t orion::List<T>::INITIAL_CAPACITY = 4;

//==============================================================================
template<typename T>
orion::List<T>::List():size(0),capacity(orion::List<T>::INITIAL_CAPACITY){
    array = new T[capacity];
}

//==============================================================================
template<typename T>
orion::List<T>::List(const List<T>& list):size(list.size), capacity(list.capacity){
    array = new T[capacity];
    for(size_t i = 0; i < size; i++){
        // we cannot assume trivial copy-construtor and use memcpy
        array[i] = list.array[i];
    }
}

//==============================================================================
template<typename T>
orion::List<T>::~List(){
    delete [] array;
    array = 0;
}

//==============================================================================
template<typename T>
const orion::List<T>& orion::List<T>::operator= (const List<T>& list){
    //Avoid self-assignment 
    if(this != &list){
        //TODO: use implicit sharing
        //Check if we need a new array
        if( capacity != list.capacity){
            delete[] array;
            array = new T[list.capacity];
        }
        
        capacity = list.capacity;
        size = list.size;
        for(size_t i = 0; i < size; i++){
            array[i] = list.array[i];
        }   
    }
    
    return (*this);      
}

//==============================================================================
template<typename T>
void orion::List<T>::resize_array(size_t new_capacity){
    if(new_capacity < size){
        throw std::length_error("New capacity cannot be lower than current"
                                        "size");
    }
    T* previous_array = array;
    capacity = new_capacity;
    array = new T[capacity];
    for (size_t i = 0; i < size; i++){
        array[i] = previous_array[i];
    }
    delete [] previous_array;
}

//==============================================================================
template<typename T>
void orion::List<T>::insert_front(const T& elem){
    if(size + 1 > capacity){
        resize_array(2*capacity);
    }    
    
    //open space in the front
    for(size_t i = size; i> 0; i--){
        array[i] = array[i-1];
    }
    
    array[0] = elem;
    size++;
}

//==============================================================================
template<typename T>
void orion::List<T>::insert_back(const T& elem){
    if(size + 1 > capacity){
        resize_array(2*capacity);
    } 

    array[size++] = elem;
}

//==============================================================================
template<typename T>
T orion::List<T>::pop_front(){
    if(size == 0){
        throw std::length_error("Cannot pop empty list");
    }
    
    T elem = array[0];
    
    //copy over
    for(size_t i = 0; i < (size-1); i++){
        array[i] = array[i+1];
    } 
    size--;
    
    downsizeIfNeeded();

    return elem;
}

//==============================================================================
template<typename T>
T orion::List<T>::pop_back(){
    if(size == 0){
        throw std::length_error("Cannot pop empty list");
    }
    
    T elem = array[--size];

    downsizeIfNeeded();
        
    return elem;   
}

//==============================================================================
template<typename T>
bool orion::List<T>::contains(const T& elem){
    for(size_t i = 0; i < size; i++){
        if(array[i] == elem){
            return true;
        }
    }
    return false;
}

//==============================================================================
template<typename T>
bool orion::List<T>::remove(const T& elem){
    for(size_t i = 0; i < size; i++){
        if(array[i] == elem){
            
            //copy over
            for(size_t j = i; j < (size-1); j++){
                array[j]=array[j+1];
            } 
                        
            size--;
            downsizeIfNeeded();
            return true;
        }
    }
    return false;
}

//==============================================================================
template<typename T>
const T& orion::List<T>::operator[](const size_t index) const{
    if((index < 0) || (index >= size)){
        throw std::range_error("Index out of bounds");
    }
    
    return array[index];
}

//==============================================================================
template<typename T>
T& orion::List<T>::operator[](const size_t index){
    if((index < 0) || (index >= size)){
        throw std::range_error("Index out of bounds");
    }
    
    return array[index];
}

//==============================================================================
template<typename T>
typename orion::List<T>::Iterator orion::List<T>::begin(){
    return Iterator(this,0);
}

//==============================================================================
template<typename T>
typename orion::List<T>::Iterator orion::List<T>::end(){
    return Iterator(this,size);
}

//==============================================================================
template<typename T>
bool orion::List<T>::Iterator::operator==(const List<T>::Iterator& it) const{
    if (this  == &it){
        return true;
    }else {
        return ((list == it.list) && (currentPos == it.currentPos));
    }
}

//==============================================================================
template<typename T>
bool orion::List<T>::Iterator::operator!=(const List<T>::Iterator& it) const{
    return !( (*this) == it);

}

//==============================================================================
template<typename T>
T& orion::List<T>::Iterator::operator*(){
    return (*list)[currentPos];
}

//==============================================================================
template<typename T>
T* orion::List<T>::Iterator::operator->(){
    return &((*list)[currentPos]);
}

//==============================================================================
template<typename T>
//dependent scope needs typename so compilers know Iterator is a type not a var
typename orion::List<T>::Iterator& orion::List<T>::Iterator::operator++(){
    currentPos = (currentPos < list->getSize())?(currentPos+1):list->getSize();
    return (*this);
}

//==============================================================================
template<typename T>
//dependent scope needs typename so compilers know Iterator is a type not a var
typename orion::List<T>::Iterator orion::List<T>::Iterator::operator++(int){
    //do a copy to return 
    Iterator tmp = (*this);      
    currentPos = (currentPos < list->getSize())?(currentPos+1):list->getSize();
    return tmp;
}

//==============================================================================
#endif //ORION_LIST_H

