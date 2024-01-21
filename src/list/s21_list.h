#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
// #include <memory>
#include <initializer_list>  // предоставляет инициализационный список
// #include "s21_list_iterator.h"
namespace s21 {
  template <typename T>
  class list;

  template <typename T>
class member {
public:
    member() {
        this->value = 0;
        this->next = nullptr;
        this->before = nullptr;
    };

    member(T value, member* next=nullptr, member* before=nullptr)
        : value(value), next(next), before(before){}

    member(const member& other)
        : value(other.value), next(std::move(other.next)), before(other.before) {}
    
    ~member() { destroy(); }

    void destroy() {
        this->next = nullptr;
        this->before = nullptr;
        this->value = 0;
    }

    T value;
    member<T>* next;
    member<T>* before;

};



template <typename T>
class ListIterator {
 public:
  ListIterator() { ptr_ = nullptr; };
  ListIterator(member<T>* ptr) : ptr_(ptr){};

  T operator*() {
    if (!this->ptr_) {
      throw std::invalid_argument("Value is nullptr");
    }
    return this->ptr_->value;
  }
    ListIterator operator=(member<T>* ptr) { // это добавила 
    ptr_ = ptr;
  }
  ListIterator operator++(int) {
    ptr_ = ptr_->next;
    return *this;
  }

  ListIterator operator--(int) {
    ptr_ = ptr_->before;
    return *this;
  }

  ListIterator& operator++() {
    ptr_ = ptr_->next;
    return *this;
  }

  ListIterator& operator--() {
    ptr_ = ptr_->before;
    return *this;
  }

  ListIterator operator+(const typename list<T>::size_type value) {
    list<T>* tmp = ptr_;
    for (typename list<T>::size_type i = 0; i < value; i++) {
      tmp = tmp->next;
    }

    ListIterator res(tmp);
    return res;
  }

  ListIterator operator-(const typename list<T>:: size_type value) {
    member<T>* tmp = ptr_;
    for (typename list<T>::size_type i = 0; i < value; i++) {
      tmp = tmp->before;
    }
    ListIterator<T> res= new ListIterator<T>(tmp);
    return res;
  }

  bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
  bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

 private:
  member<T>* ptr_ = nullptr;
  friend class list<T>;
};

////////////////////////////////
/*________________list const iterator_______________*/
////////////////////////////////

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
  const T& operator*() { return ListIterator<T>::operator*(); }
};


//--------------------------------------------------
/*-----------------------класс листа----------------*/
/*--------------------------------------------------*/

template <typename T>
class list {
 public:
  typedef T value_type;  // определяет тип
  typedef T& reference;  // определяет тип ссылки на элемент можно использовать
                         // как возворащаемый тип из функции
  typedef const T& const_reference;  // тип ссылки на константу
  typedef ListIterator<T> iterator; // определяет тип итератора
  typedef ListConstIterator<T> const_iterator; // определяет тип константного
  // итератора
  typedef std::size_t size_type;  // определяет тип размера контейнера

  list(): begin_member(nullptr),now_point(nullptr),end_member(nullptr), _n(0){
  }
// сделано 

  list(size_type n) { // done
    create_first();
    for (size_type i = 1; i < n && n > 0; ++i) {
      add_New_member(0);
    }
  }  // construtor creates the list of size n


  list(std::initializer_list<value_type> const& items) { // done
    create_first(*(items.begin()));
    for (auto it = items.begin() + 1; it != items.end(); ++it) {
      const auto& item = *it;
      add_New_member(item);
    }
  }  // construtor creates the list listt from the initializer lis



  list(const list& l) { // можно и лучше так то // done
    if (l._n != 0) {
      list<T> tmp;
      tmp.begin_member = l.begin_member;
      tmp.end_member = l.end_member;
      tmp._n = l._n;
      this->create_first(tmp.begin_member->value);
      // tmp.begin_member=tmp.begin_member->next;
      for (auto iter = tmp.begin()++; iter !=  nullptr; iter++)
      {
        const auto& item = *iter;
        this->add_New_member(item);
      }
       tmp.begin_member = nullptr;
    tmp.end_member = nullptr;
    tmp.now_point = nullptr;
    tmp._n = 0;
    }
  };  // copy construtor




  list(list&& l) { move(l); 
  
  null_elements( l);}

  ~list() { clear(); }  // destructor

  void operator=(list&& l) {
    move(l);  // проверить работу
  }           // перегрузка оператора перемещения


  const_reference front(){
  return this->begin_member->value; //не уверена что именно такое возвращаем
}

  const_reference back(){
  return this->end_member->value; // не уверена
}


  iterator begin(){ // done
    ListIterator<T> ptr(this->begin_member);
    return ptr;
}
  iterator end(){ // done
    ListIterator<T> ptr(this->end_member);
    return ptr;
}


  bool empty() { // done
    if (this->_n > 0) {
      return false;
    }
    return true;
  };

  size_type size() { // done
    return this->_n;
  };  // возвращает сколько элементов в листе

  size_type max_size() {
    member<T> tmp;
    return (SIZE_MAX / sizeof(member<T>) /
            2);  // ну пытаюсь получить максимальный размер листа
  };  // возвращает сколько всего можно создать элементов в листе


  void clear() { // done
    if(!this->empty())
    {
        member<T>* tmp = this->begin_member;
        while (this->begin_member != nullptr) {
            tmp = this->begin_member->next;
            delete this->begin_member;
            this->begin_member = tmp;
            this->_n--;
        }
        this->begin_member = nullptr;
        this->now_point = nullptr;
        this->end_member = nullptr;
        this->_n = 0;
        tmp = nullptr;
    }
  }

  // очищает лист
  // iterator insert(iterator pos, const_reference value); // добавляет элемент
  // в определенное место и возвращает итератор void erase(iterator pos); //
  // удаляет элемент по итератору
  void push_back(const_reference value) { // done
    add_New_member(value);
  }  // добавляет элемент в конец листа

  void pop_back() { // done
    this->end_member = this->end_member->before;
    this->end_member->next->destroy();  // страшная конструкция
    this->_n -= 1;
  }  // удаляет элемент с конца

  void push_front(const_reference value) { // done
    member<T>* new_front = new member<T>(value, this->begin_member, nullptr);
    this->begin_member->before = new_front;
    this->begin_member = new_front;
    this->now_point = new_front;
    this->_n++;
  }  // добавляет элемент в начало листа

  void pop_front() {
    {
      this->begin_member = this->begin_member->next;
      this->begin_member->before->destroy();  // страшная конструкция
      this->_n -= 1;
    }
  }  // удаление первого элемента

  void swap(list& other) {
    list<T>* tmp = new list<T>();
    tmp = other;
    other = *this;
    *this = tmp;  // ну надо будет проверить
  };

  void merge(list& other);
  void splice(const_iterator pos, list& other){
  if (!other.empty()) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      this->insert(pos, *it);
    }
    other.clear();
  }
}

  void reverse();
  void unique(); // после реализации сортировки 
  void sort();
  ///////////////////////

  void move(list l) {
    this->begin_member = l.begin_member;
    this->end_member = l.end_member;
    this->now_point = begin_member;
    this->_n = l._n;
    
  };

  void null_elements(list&& l){
    l.begin_member = nullptr;
    l.end_member = nullptr;
    l.now_point = nullptr;
    l._n = 0;
  }
  
  T return_last(){
    return this->end_member->value;
  }

  void create_first(T value = 0) {
    member<T>* first = new member<T>(value, nullptr, nullptr);
    this->begin_member = first;
    this->now_point = first;
    this->end_member = first;
    this->_n = 1;
  }

  void next_el() { // done
    if (now_point->next == nullptr) {
      throw "Limit of the container is exceeded";
    }
    // member<T>* tmp = this->now_point->next;
    this->now_point = this->now_point->next;
  };  // переходим к следующему элементу

  T get_elenemt() { return now_point->value; } // done

  void add_New_member(T value_member = 0) {  // создаем члена в конце листа и
                                             // end теперь указывает на него
    this->end_member->next = new member<T>(value_member, nullptr, this->end_member);
    this->end_member->next->before = this->end_member;
    this->end_member = this->end_member->next;

    this->_n += 1;
  }

  void operator()(T value) { now_point->value = value; }

 private:
  member<T>* begin_member;  //ну думаю что мы знаем что у нас идет первым
   member<T>* now_point;
  member<T>*
      end_member;  // ну мы же можем знать какой элемент у нас последний да?
  size_type _n;  // колличество элементов
};
}  // namespace s21

#endif /*S21_LIST_H*/