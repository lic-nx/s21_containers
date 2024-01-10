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
            }


    // template <typename T>
    //  member<T>::member(T value){
    //     this->value = value;
    //     this->before = nullptr;
    //     this->next = nullptr;
    // }
    template <typename T>
    member<T>::member(const member& other):value(other.value), next(std::move(other.next)), before(other.before){}


    // template <typename T>
    // void member<T>::initializer_member_next(member* update) {   
    //           next = update;

    //         }

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




// -------------------------------------------------------------------------------- //

    template <typename T>
    list<T>::list(){
        // T value = NULL;
        member<T> participant; // создаю пустой член захах
        begin = &participant; // запоминаем первый элемент
        now_point = &participant;
        end = &participant;
    }

    template <typename T>
    list<T>::list(size_type n){
      member<T>* first = new member<T>(0, nullptr, nullptr); 
      begin = first;
      now_point = first;
      end = first;
      for (size_type i = 1; i < n && n > 0; ++i){
          add_New_member();
      }
      this->_n = n;

    }
   

    template <typename T>
    list<T>::list(std::initializer_list<value_type> const &items){
        member<T>* first = new member<T>(*(items.begin()), nullptr, nullptr);
        begin = first;
        now_point = first;
        end = first;
        for (auto it = items.begin()+1; it != items.end(); ++it) {
            const auto& item = *it;
            add_New_member(item);
            // Ваш код для обработки каждого элемента item
        }

        // for(const auto& item : items){
        //     add_New_member(item);
        // }
        this->_n = items.size();
    }

    template <typename T>
    list<T>::list(const list &l){
        
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
        this->now_point = nullptr;
        this->end = nullptr;

        _n = 0;
    }


    template <typename T>
    void list<T>::add_New_member(T value_member){ // создаем члена в конце листа и end теперь указывает на него 
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
        return now_point->value;
    }


    template <typename T>
    T list<T>::next_el(){
        if (now_point->next == nullptr){
            throw "Limit of the container is exceeded";
            }
            member<T>* tmp = now_point->next;
            *this->now_point = *tmp;
      return now_point->value;
    }


// сама длбавтила для проверки добавления элемента
     template <typename T>
    void list<T>::operator()(T value){
        now_point->value = value;

    }

}
int main (){
    s21::list<int> test({1,2,3});
    std:: cout<<test.get_elenemt()<<"\n"<<test.next_el();
    return 1;
}