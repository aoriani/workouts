#include <iostream>

class foo{
    public:void do_foo(){std::cout<<"Foo!"<<std::endl;}
};

template<typename T>
struct delegate_foo{
    static const bool value = false;
};

template<>
struct delegate_foo<foo>{
    static const bool value = true;
};

template <bool b>
struct foomaker{
    template <typename T>
    static void foo(T& f){
        std::cout<<"Bar"<<std::endl;
    }  
};

template <>
struct foomaker<true>{
    template <typename T>
    static void foo(T& f){
        f.do_foo();
    }  
};

template <typename T>
void call_foo(T& f){
    foomaker<delegate_foo<T>::value>::foo(f);
}


int main(){

    foo a;
    char c='a';
    call_foo(a);
    call_foo(c);

    return 0;
    
}
