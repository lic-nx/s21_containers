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
        begin = nullptr; // запоминаем первый элемент
        now_point = nullptr;
        end = nullptr;
    }

    template <typename T>
    list<T>::list(size_type n){
      member<T>* first = new member<T>(0, nullptr, nullptr); 
      this->begin = first;
      this->_n = 1;
      this->now_point = first;
      this->end = first;
      for (size_type i = 1; i < n && n > 0; ++i){
          add_New_member();
      }

    }
   
    template <typename T>
    void list<T>::create_first(T value){
         member<T>* first = new member<T>(value, nullptr, nullptr);
        this->begin = first;
        this->now_point = first;
        this->end = first;
        this->_n = 1;
    }

    template <typename T>
    list<T>::list(std::initializer_list<value_type> const &items){
        create_first(*(items.begin()));
        for (auto it = items.begin()+1; it != items.end(); ++it) {
            const auto& item = *it;
            add_New_member(item);
        }
        
    }

    template <typename T>
    list<T>::list(const list &l){
        if (l._n != 0){
            create_first(l.begin->value);
            l.now_point = l.begin;
            while(l.now_point->next != nullptr){
                add_New_member(l.now_point->value);
                l.next_el();
            }
        }
    }

    template <typename T>
    list<T>::list(list &&l){
        move(l); // проверить 
    }

    template <typename T>
    void list<T>::move(list &&l){
        this->begin = l.begin;
        this->end = l.end;
        this->now_point = begin;
        this->_n = l._n;
        l.begin = nullptr;
        l.end=nullptr;
        l.now_point=nullptr;
        l._n=0;
    }
    template <typename T>
    list<T>::~list(){
        clear();
    }


    template <typename T>
    typename  list<T>::size_type list<T>::size(){
        return this->_n;
    }

    template <typename T>
    bool list<T>::empty(){
        if (this->_n > 0){
            return true;
        }
        return false;
    }

    template <typename T>
    typename  list<T>::size_type list<T>:: max_size(){
        member<T> tmp;
        return(SIZE_MAX/sizeof(member<T>)/2); // ну пытаюсь получить максимальный размер листа
    }

 template <typename T>
    void list<T>::clear(){
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
    void list<T>::push_back(const_reference value){
        add_New_member(value);
    }
template <typename T>
    void list<T>::pop_back(){
        this->end = this->end->before;
        this->end->next->destroy();  // страшная конструкция
    }

template <typename T>
    void list<T>::pop_front(const_reference value){
        member<T>* new_front = new member<T>(value, this->begin, nullptr);
        this->begin->before =new_front;
        this->begin = new_front;
        
    }

template <typename T>
    void list<T>::pop_front(){
        this->begin = this->begin->next;
        this->begin->before->destroy();  // страшная конструкция
    }

    template <typename T>
    void list<T>::swap(list& other){
        list<T>* tmp = new();
        tmp = other;
        other = *this;
        *this = tmp; // ну надо будет проверить
    }
    
    template <typename T>
    void list<T>::merge(list& other){
        
    }

// этот блок вызывает вопросы тип а что все такое похожее
    template <typename T>
    typename list<T>::const_reference list<T>::front(){ 
        return this->begin;
    }

    template <typename T>
    typename list<T>::const_reference list<T>::back(){ 
        return this->end;
    }


    // template <typename T>
    // typename list<T>::iterator list<T>::begin(){ 
    //     return this->begin;
    // }

    // template <typename T>
    // typename list<T>::iterator list<T>::end(){ 
    //     return this->end;
    // }
//////////////////////////////////




    template <typename T>
    void list<T>::add_New_member(T value_member){ // создаем члена в конце листа и end теперь указывает на него 
        member<T>* child_member = new member<T>(value_member, nullptr, end);
        this->end->next = child_member;
        this->end = child_member;
        this->_n += 1;
    }

    template <typename T>
    T list<T>::get_elenemt(){ 
        return now_point->value;
    }


    template <typename T>
    void list<T>::next_el(){
        if (now_point->next == nullptr){
            throw "Limit of the container is exceeded";
            }
            member<T>* tmp = now_point->next;
            *this->now_point = *tmp;
    }


// сама длбавтила для проверки добавления элемента
    template <typename T>
    void list<T>::operator()(T value){
        now_point->value = value;

    }

    template <typename T>
    void list<T>::operator=(list &&l){
        move(l);  // проверить работу

    }

}
int main (){
    s21::list<int> test({1,2,3});
    std:: cout<<test.get_elenemt()<<"\n"<<test.get_elenemt();
    return 1;
}