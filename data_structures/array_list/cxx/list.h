#ifndef ORION_LIST_H
#define ORION_LIST_H

#include <cstdlib>

using std::size_t;

namespace orion{

    template <typename T>
    class List{
        private:
            size_t size;
            size_t capacity
            T* array;
            
            void resize_array(size_t size)
            unsigned roundup2power(unsigned value);
            
        public:
            List();
            List(const List& list);
            ~List();
            const List& operator=(const List& list);
            inline size_t size() const;
            inline size_t capacity() const;
            void insert_front(const T& elem);
            void insert_back(const T& elem);
            T pop_front();
            T pop_back();
            bool contains(const T& elem);
            bool remove(const T& elem);
            const T& operator[] (int index) const;
            T& operator[] (int index);
             
    };

}


#endif ORION_LIST_H
