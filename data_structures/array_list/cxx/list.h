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
            static unsigned roundup2power(unsigned value);
            
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
            const T& operator[] (const int index) const;
            T& operator[] (const int index);             
    };

}

//==============================================================================
template<typename T>
const size_t orion::List<T>::INITIAL_CAPACITY = 4;

//==============================================================================
template<typename T>
unsigned orion::List<T>::roundup2power(unsigned value){
    unsigned i;
    for(i=0;value; value>>=1, i++);
    return 1<<i;
}

//==============================================================================
template<typename T>
orion::List<T>::List():size(0),capacity(orion::List<T>::INITIAL_CAPACITY){
    array = new T[capacity];
    array = 0;
}

//==============================================================================
template<typename T>
orion::List<T>::List(const List<T>& list):size(list.size), capacity(list.capacity){
    array = new T[capacity];
    for(int i = 0; i < size; i++){
        // we cannot assume trivial copy-construtor and use memcpy
        array[i] = list.array[i];
    }
}

//==============================================================================
template<typename T>
orion::List<T>::~List(){
    delete [] array;
}

//==============================================================================
template<typename T>
const orion::List<T>& orion::List<T>::operator= (const List<T>& list){
    //Avoid self-assignment 
    if(this != &list){
        //TODO: use implicit sharing
        delete[] array;
        capacity = list.capacity;
        size = list.size;
        array = new T[capacity];
        for(int i = 0; i < size; i++){
            array[i] = list.array[i];
        }   
    }      
}


//==============================================================================
template<typename T>
void orion::List<T>::resize_array(size_t new_capacity){
    if(new_capacity < size){
        throw std::length_error("New capacity cannot be lower than current"
                                        "size");
    }
    T* previous_array = array;
    array = new T[new_capacity];
    for (int i = 0; i < size; i++){
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
    for(int i = size; i> 0; i--){
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

    array[++size] = elem;
}

//==============================================================================
template<typename T>
T orion::List<T>::pop_front(){
    if(size == 0){
        throw std::length_error("Cannot pop empty list");
    }
    
    T elem = array[0];
    
    //copy over
    for(int i = 0; i < (size-1); i++){
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
    
    T elem = array[size--];
    return elem;   
}

//==============================================================================
template<typename T>
bool orion::List<T>::contains(const T& elem){
    for(int i = 0; i < size; i++){
        if(array[i] == elem){
            return true;
        }
    }
    return false;
}

//==============================================================================
template<typename T>
bool orion::List<T>::remove(const T& elem){
    for(int i = 0; i < size; i++){
        if(array[i] == elem){
            
            //copy over
            for(int j = i; j < (size-1); j++){
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
const T& orion::List<T>::operator[](const int index) const{
    if((index < 0) || (index >= size)){
        throw std::range_error("Index out of bounds");
    }
    
    return array[index];
}

//==============================================================================
template<typename T>
T& orion::List<T>::operator[](const int index){
    if((index < 0) || (index >= size)){
        throw std::range_error("Index out of bounds");
    }
    
    return array[index];
}
#endif //ORION_LIST_H
