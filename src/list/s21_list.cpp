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
    member<T>::member(T value, member* next, member* before): next(next), before(before), value(value) {
                // this = std::make_shared<member>();
                if (before != NULL) {
                    before->initializer_member_next(this);
                }
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
              next = update;
            }

    template <typename T>
    member<T>::~member(){
               destroy();               
            };


    template <typename T>
    void member<T>::destroy(){
      next = nullptr;
      before = nullptr;
      value = 0;
    }


    template <typename T>
    list<T>::list(){
        // T value = NULL;

        member<T> participant; // создаю пустой член захах
        std::cout<< participant.value<<"\n";
        begin = &participant; // запоминаем первый элемент
    }

    template <typename T>
    list<T>::list(size_type n){
      std::cout<< "create " << 0 << " \n";
      member<T>* first = new member<T>(0, nullptr, nullptr); 
      begin = first;
      end = first;
      for (size_type i = 1; i < n && n > 0; ++i){
          add_New_member(i);
          std::cout<< "create " << i << " \n";
      }
      std::cout<< end->value << " end \n";
      _n = n;
    }
   

    template <typename T>
    list<T>::list(std::initializer_list<value_type> const &items){

    }

    template <typename T>
    list<T>::~list(){
        member<T>* tmp = this->begin;
      while (begin->next != nullptr){
        tmp = this->begin->next;
        delete this->begin;
        this->begin = tmp;
      }
        this->begin = nullptr;
        this->end = nullptr;
        _n = 0;
    }


    template <typename T>
    void list<T>::add_New_member(T value_member){ // создаем члена в конце листа и end теперь указывает на него 
        std::cout<< end->value << " end \n";
        member<T>* child_member = new member<T>(value_member, nullptr, end);
        this->end->next = child_member;
        this->end = child_member;
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

    template <typename T>
    T list<T>::next_el(){
      member<T>* tmp = begin->next;
      std::cout<<begin->value;
      *this->begin = *tmp;
      return begin->value;
    }

}
int main (){
    s21::list<int> test(3);
    std:: cout<<test.get_elenemt()<<"\n"<<test.next_el();
    return 1;
}