
#include "s21_list.h"
// #include "../s21_iterators.h"

namespace s21{

 template <typename T>
 member<T>::member():value(NULL), next(std::move(NULL)), before(NULL){}
template <typename T>
member<T>::member(T value, std::shared_ptr<member> next, member* before)
             : next(std::move(next)), before(before), value(value){
                // this = std::make_shared<member>();
                if (before != nullptr) {
                    before->initializer_member_next(*this);
                }
            }

template <typename T>
T member<T>::value_get(){
    return value;
};
template <typename T>
member<T>:: ~member(){
                next = NULL;
                before = NULL;
                value = 0;
                
            };

template <typename T>
void member<T>::initializer_member_next(member update) {   
              next = std::make_shared<member>(update);
            }



template <typename T>
list<T>::list()
            {
                T value = NULL;
                member<T> participant(value, nullptr, nullptr); // создаю пустой член захах
                begin = participant; // запоминаем первый элемент
                end = participant;// раз первый то и последний 
                }


template <typename T>
void list<T>::add_New_member(T& value_member){ // создаем члена в конце листа и end теперь указывает на него 
                member<T> child_member(value_member, nullptr, &end);
                end = *child_member;
            }


}

