#include "s21_list.h"
// #include "../s21_iterators.h"
namespace s21{
    template <typename T>
    member<T>::member(){
        this->value = 0;
        this->before = nullptr;
        this->next = nullptr;
    }


    template <typename T>
    member<T>::member(T value, std::shared_ptr<member<T>> next, member* before){
        this->value = value;
        this->before = before;
        this->next = next;
    }

    // template <typename T>
    //  member<T>::member(T value){
    //     this->value = value;
    //     this->before = nullptr;
    //     this->next = nullptr;
    // }
    template <typename T>
    member<T>::member(const member& other):value(other.value), next(std::move(other.next)), before(other.before){}


    template <typename T>
    void member<T>::initializer_member_next(member* update) {   
              next = std::make_shared<member>(update);
            }

    template <typename T>
    member<T>::~member(){
                next = nullptr;
                before = nullptr;
                value = 0;
                
            };




    template <typename T>
    list<T>::list(){
        // T value = NULL;

        member<T> participant; // создаю пустой член захах
        std::cout<< participant.value<<"\n";
        begin = &participant; // запоминаем первый элемент
    }

    template <typename T>
    list<T>::list(size_type n){

        member<T> first(nullptr, nullptr, nullptr); // 
        end = &first;
        for (size_type i = 0; i < n && n > 0; ++i){
            add_New_member();
        }
        _n = n;
    }
   

    template <typename T>
    list<T>::list(std::initializer_list<value_type> const &items){

    }

    template <typename T>
    list<T>::~list(){
        begin = nullptr;
        end = nullptr;
        _n = 0;
    }


    template <typename T>
    void list<T>::add_New_member(T value_member){ // создаем члена в конце листа и end теперь указывает на него 
        member<T>* child_member(value_member, nullptr, &end);
        end = child_member;
    }



    // template <typename T>
    // std::size_t list<T>:: max_size(){
    //     member<T> tmp;
    //     return(SIZE_MAX/sizeof(member<value, member>)); // ну пытаюсь получить максимальный размер листа
    // }

    template <typename T>
    T list<T>::get_elenemt(){
        return begin->value;
    }

}
int main (){
    s21::list<int> test(3);
    std:: cout<<test.get_elenemt()<<"\n";
    return 1;
}