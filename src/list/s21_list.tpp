#include "s21_list.h"
#include "../s21_iterators.h"

template <typename T>
list<T>::list(){
    T value = NULL;
    member<T> participant(value, nullptr, nullptr); // создаю пустой член захах
    begin = participant; // запоминаем первый элемент
}

template <typename T>
list<T>::list(size_type n){
    member<T> first(value, nullptr, nullptr);
    end = first;
    for (size_type i = 0; i < n && n > 0; ++i){
        add_New_member();
    }
    _n = n;
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items){

}


template <typename T>
void list<T>:: add_New_member(T& value_member = NULL){ // создаем члена в конце листа и end теперь указывает на него 
    member<T> child_member(value_member, nullptr, &end)
    end = member;
}



template <typename T>
size_type list<T>:: max_size(){
    member<t> tmp;
    return(SIZE_MAX/sizeof(member<value, member>)); // ну пытаюсь получить максимальный размер листа
}