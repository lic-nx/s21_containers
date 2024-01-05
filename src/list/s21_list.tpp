#include "s21_list.h"
#include "../s21_iterators.h"

template <typename T>
list<T>::list(){
    Iterator start();
    // T value = NULL;
    // member<T> participant(value, nullptr, nullptr); // создаю пустой член захах
}

template <typename T>
list<T>::list(size_type n){
    member<T> first(value, nullptr, nullptr);
    for (size_type i = 0; i < n && n > 0; ++i){
        member<T> second(value, nullptr, second);
    }
    _n = n;
}

template <typename T>
size_type max_size(){
    member<t> tmp;
    return(SIZE_MAX/sizeof(member<value, member>)); // ну пытаюсь получить максимальный размер листа
}