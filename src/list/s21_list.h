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
    T value;
    member<T>* next;
    member<T>* before;
    member() {
      this->value = 0;
      this->before = nullptr;
      this->next = nullptr;
    };
    member(T value, member* next=nullptr, member* before=nullptr)
        : next(next), before(before), value(value){}

    member(const member& other)
        : value(other.value), next(std::move(other.next)), before(other.before){}
    
    ~member() { destroy(); }

    void destroy() {
      this->next = nullptr;
      this->before = nullptr;
      this->value = 0;
    }
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

  list(size_type n) {
    member<T>* first = new member<T>(1, nullptr, nullptr);
    this->begin_member = first;
    this->_n = 1;
    this->now_point = first;
    this->end_member = first;
    for (size_type i = 1; i < n && n > 0; ++i) {
      add_New_member(0);
    }
    first = nullptr;
    delete(first);
  }  // construtor creates the list of size n

  list(std::initializer_list<value_type> const& items) {
    create_first(*(items.begin()));
    for (auto it = items.begin() + 1; it != items.end(); ++it) {
      const auto& item = *it;
      add_New_member(item);
    }
  }  // construtor creates the list listt from the initializer lis

  list(const list& l) {
    if (l._n != 0) {
      create_first(l.begin_member->value);
      l.now_point = l.begin_member;
      while (l.now_point->next != nullptr) {
        add_New_member(l.now_point->value);
        l.next_el();
      }
    }
  };  // copy construtor

  list(list&& l) { move(l); }

  ~list() { clear(); }  // destructor

  void operator=(list&& l) {
    move(l);  // проверить работу
  }           // перегрузка оператора перемещения


  const_reference front(){
  return this->begin_member;
}

  const_reference back(){
  return this->end_member;
}


  iterator begin(){
    ListIterator<T> ptr(this->begin_member);
    return ptr;
}
  iterator end(){
    ListIterator<T> ptr(this->end_member);
    return ptr;
}


  bool empty() {
    if (this->_n > 0) {
      return false;
    }
    return true;
  };

  size_type size() {
    return this->_n;
  };  // возвращает сколько элементов в листе

  size_type max_size() {
    member<T> tmp;
    return (SIZE_MAX / sizeof(member<T>) /
            2);  // ну пытаюсь получить максимальный размер листа
  };  // возвращает сколько всего можно создать элементов в листе

  void clear() {
    if(!this->empty())
    {
        member<T>* tmp = this->begin_member;
        while (tmp != nullptr) {
            tmp = this->begin_member->next;
            this->begin_member->destroy();
            this->begin_member = tmp;
        }
        this->begin_member = nullptr;
        this->now_point = nullptr;
        this->end_member = nullptr;
        _n = 0;
        tmp=nullptr;
        delete(tmp);
    }
  }

  // очищает лист
  // iterator insert(iterator pos, const_reference value); // добавляет элемент
  // в определенное место и возвращает итератор void erase(iterator pos); //
  // удаляет элемент по итератору
  void push_back(const_reference value) {
    add_New_member(value);
  }  // добавляет элемент в конец листа

  void pop_back() {
    this->end_member = this->end_member->before;
    this->end_member->next->destroy();  // страшная конструкция
    this->_n -= 1;
  }  // удаляет элемент с конца

  void push_front(const_reference value) {
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
  void splice(const_iterator pos, list& other);

  void reverse();
  void unique(); // после реализации сортировки 
  void sort();
  ///////////////////////

  void move(list&& l) {
    this->begin_member = l.begin_member;
    this->end_member = l.end_member;
    this->now_point = begin_member;
    this->_n = l._n;
    l.begin_member = nullptr;
    l.end_member = nullptr;
    l.now_point = nullptr;
    l._n = 0;
  };

  void create_first(T value) {
    member<T>* first = new member<T>(value, nullptr, nullptr);
    this->begin_member = first;
    this->now_point = first;
    this->end_member = first;
    this->_n = 1;
  }

  void next_el() {
    if (now_point->next == nullptr) {
      throw "Limit of the container is exceeded";
    }
    member<T>* tmp = now_point->next;
    *this->now_point = *tmp;
  };  // переходим к следующему элементу

  T get_elenemt() { return now_point->value; }

  void add_New_member(T value_member = 0) {  // создаем члена в конце листа и
                                             // end теперь указывает на него
    member<T>* child_member = new member<T>(value_member, nullptr, end_member);
    this->end_member->next = child_member;
    this->end_member = child_member;
    this->_n += 1;
    child_member=nullptr;
    delete(child_member);
  }

  void operator()(T value) { now_point->value = value; }

 private:
  size_type _n;  // колличество элементов
  member<T>* begin_member;  //ну думаю что мы знаем что у нас идет первым
  member<T>*
      end_member;  // ну мы же можем знать какой элемент у нас последний да?
  member<T>* now_point;
};
}  // namespace s21

#endif /*S21_LIST_H*/