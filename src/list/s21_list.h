#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_

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
    // this->value;
    this->next = nullptr;
    this->before = nullptr;
  };

  member(T value, member* next = nullptr, member* before = nullptr)
      : value(value), next(next), before(before) {}

  member(const member& other)
      : value(other.value), next(std::move(other.next)), before(other.before) {}

  ~member() { destroy(); }

  void destroy() {
    this->next = nullptr;
    this->before = nullptr;
    // this->value;
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
  ListIterator operator=(member<T>* ptr) {  // это добавила
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

  ListIterator operator-(const typename list<T>::size_type value) {
    member<T>* tmp = ptr_;
    for (typename list<T>::size_type i = 0; i < value; i++) {
      tmp = tmp->before;
    }
    ListIterator<T> res = new ListIterator<T>(tmp);
    return res;
  }

  bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
  bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

  bool operator>=(ListIterator other) {
    return this->ptr_->value >= other.ptr_->value;
  }
  bool operator<=(ListIterator other) {
    return this->ptr_->value <= other.ptr_->value;
  }
  bool operator<(ListIterator other) {
    return this->ptr_->value < other.ptr_->value;
  }
  bool operator>(ListIterator other) {
    return this->ptr_->value > other.ptr_->value;
  }

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
  typedef ListIterator<T> iterator;  // определяет тип итератора
  typedef ListConstIterator<T> const_iterator;  // определяет тип константного
  // итератора
  typedef std::size_t size_type;  // определяет тип размера контейнера

  list()
      : begin_member(nullptr), now_point(nullptr), end_member(nullptr), _n(0) {}
  // сделано

  list(size_type n) {  // done
    create_first();
    for (size_type i = 1; i < n && n > 0; ++i) {
      add_New_member(0);
    }
  }  // construtor creates the list of size n

  list(std::initializer_list<value_type> const& items) {  // done
    create_first(*(items.begin()));
    for (auto it = items.begin() + 1; it != items.end(); ++it) {
      const auto& item = *it;
      add_New_member(item);
    }
  }  // construtor creates the list listt from the initializer lis

  list(const list& l) {  // можно и лучше так то // done
    copy(l);
  };  // copy construtor

  void copy(const list& l) {
    if (l._n != 0) {
      list<T> tmp;
      tmp.begin_member = l.begin_member;
      tmp.end_member = l.end_member;
      tmp._n = l._n;
      this->create_first(tmp.begin_member->value);
      // tmp.begin_member=tmp.begin_member->next;
      for (auto iter = tmp.begin()++; iter != nullptr; iter++) {
        const auto& item = *iter;
        this->add_New_member(item);
      }
      tmp.neutral_earthing();
    }
  }

  list(list&& l) {
    move(l);
    l.clear();
  }

  ~list() { clear(); }  // destructor

  list<T>& operator=(list&& l) {
    move(l);  // проверить работу
    l.clear();
    return *this;
  }  // перегрузка оператора перемещения

  void operator=(list& l) { copy(l); }

  const_reference front() {
    return this->begin_member->value;  //не уверена что именно такое возвращаем
  }

  const_reference back() {
    return this->end_member->value;  // не уверена
  }

  iterator begin() {  // done
    ListIterator<T> ptr(this->begin_member);
    return ptr;
  }
  iterator end2() {  // done
    ListIterator<T> ptr(this->end_member);
    return ptr;
  }

  iterator end() {  // done
    this->end_member->next = new member<T>;
    this->end_member->next->before = this->end_member;
    this->end_member = this->end_member->next;
    ListIterator<T> ptr(this->end_member);
    return ptr;
  }

  bool empty() {  // done
    if (this->_n > 0) {
      return false;
    }
    return true;
  };

  size_type size() {  // done
    return this->_n;
  };  // возвращает сколько элементов в листе

  size_type max_size() {
    member<T> tmp;
    return (SIZE_MAX / sizeof(member<T>) /
            2);  // ну пытаюсь получить максимальный размер листа
  };  // возвращает сколько всего можно создать элементов в листе

  void clear() {  // done
    if (!this->empty()) {
      member<T>* tmp = this->begin_member;
      while (this->begin_member != nullptr) {
        tmp = this->begin_member->next;
        delete this->begin_member;
        this->begin_member = tmp;
        this->_n--;
      }
      this->neutral_earthing();
      tmp = nullptr;
    }
  }

  void erase(iterator pos) {
    if (pos == this->begin()) {
      this->pop_front();
    } else if (pos == this->end2()) {
      this->pop_back();
    } else {
      member<T>* tmp_member = pos.ptr_;
      pos.ptr_->before->next = tmp_member->next;
      pos.ptr_->next->before = tmp_member->before;
      tmp_member->destroy();
      delete tmp_member;
      this->_n--;
    }
  }
  // очищает лист
  iterator insert(iterator pos, const_reference value) {
    if (pos.ptr_ != nullptr) {
      member<T>* tmp_member = new member<T>(value);
      if (pos == this->begin()) {
        this->push_front(value);

      } else if (pos == this->end2()) {
        this->push_back(value);
      } else {
        tmp_member->next = pos.ptr_;
        tmp_member->before = pos.ptr_->before;
        pos.ptr_->before->next = tmp_member;
        pos.ptr_->before = tmp_member;
        tmp_member = nullptr;
      }
      delete tmp_member;
    } else {
      this->add_New_member(value);
      pos = this->begin();
    }
    return pos;
  }

  void push_back(const_reference value) {  // done
    T value_tmp = value;
    add_New_member(value_tmp);
  }  // добавляет элемент в конец листа

  void pop_back() {  // done
    this->end_member = this->end_member->before;
    this->end_member->next->destroy();  // страшная конструкция
    this->_n -= 1;
  }  // удаляет элемент с конца

  void push_front(const_reference value) {  // done
    if (!this->empty()) {
      member<T>* new_front = new member<T>(value, this->begin_member, nullptr);
      this->begin_member->before = new_front;
      this->begin_member = new_front;
      this->now_point = new_front;
      this->_n++;
    } else {
      this->add_New_member(value);
    }
  }  // добавляет элемент в начало листа

  void pop_front() {  // done
    this->begin_member = this->begin_member->next;
    delete this->begin_member->before;  // страшная конструкция
    this->_n -= 1;
    this->now_point = this->begin_member;
  }  // удаление первого элемента

  void swap(list& other) {
    member<T>* tmp;
    tmp = other.begin_member;
    other.begin_member = this->begin_member;
    this->begin_member = tmp;  // ну надо будет проверить

    size_t s_tmp = other._n;
    other._n = this->_n;
    this->_n = s_tmp;

    tmp = other.end_member;
    other.end_member = this->end_member;
    this->end_member = tmp;
  };

  void merge(list& other) {
    this->begin_member =
        merge_two_lists(this->begin_member, other.begin_member);  //
    this->_n += other._n;
    while (this->end_member->next != nullptr) {
      this->end_member = this->end_member->next;
    }
    other.neutral_earthing();
  }

  void splice(const_iterator pos, list& other) {
    iterator tmp = pos;
    if (!other.empty()) {
      for (iterator it = other.begin(); it != other.end2(); ++it) {
        this->insert(tmp, *it);
      }
      other.clear();
    }
  }

  void reverse() {  // может стопаться из-за первого элемента
    if (!this->empty()) {
      member<T>* tmp_member = this->begin_member;
      // size_type step = 0;
      for (size_type i = 0; i < this->size(); i++) {
        std::swap(tmp_member->before, tmp_member->next);
        tmp_member = tmp_member->before;
      }
      std::swap(this->begin_member, this->end_member);
    }
  }
  void unique() {
    if (!this->empty()) {
      for (iterator now_ptr = this->begin(); now_ptr != this->end2();) {
        iterator tmp = now_ptr;
        tmp++;
        if (tmp.ptr_ == nullptr) {
          return;
        } else if (*now_ptr == *tmp) {
          erase(tmp);
        } else {
          now_ptr++;
        }
      }
    }
  }  // после реализации сортировки

  void sort() {
    if (this->_n > 1) {
      // member<T>*  tmp = this->begin_member;
      this->begin_member = this->recursSort();
    }
  };

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {  // бонус
    for (const auto& arg : {args...}) {
      insert(pos, arg);
    }
    return pos;
  };

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
    // return pos;
  };

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_front(arg);
    }
  };
  ////////////////////////

  member<T>* recursSort() {
    list<T> leftList;
    list<T> rightList;
    if (this->_n <= 1) {
      return this->begin_member;
    }
    this->now_point = this->begin_member;

    for (size_type i = 0; i < this->_n / 2; i++) {
      this->now_point = this->now_point->next;
    }

    leftList.begin_member = this->begin_member;
    leftList.end_member = this->now_point->before;
    leftList.end_member->next = nullptr;
    rightList.begin_member = this->now_point;
    rightList.begin_member->before = nullptr;
    rightList.end_member = this->end_member;

    member<T>* tmp =
        merge_two_lists(leftList.recursSort(), rightList.recursSort());
    // leftList.neutral_earthing();
    // rightList.neutral_earthing();
    return tmp;
    // this->begin_member = leftList.begin_member;
  }

  void move(list l) {
    this->begin_member = l.begin_member;
    this->end_member = l.end_member;
    this->now_point = this->begin_member;
    this->_n = l._n;
    l.neutral_earthing();
  };

  // void null_elements(list&& l){
  //   l.begin_member = nullptr;
  //   l.end_member = nullptr;
  //   l.now_point = nullptr;
  //   l._n = 0;
  // }

  void neutral_earthing() {
    this->begin_member = nullptr;
    this->end_member = nullptr;
    this->now_point = nullptr;
    this->_n = 0;
  }

  member<T>* merge_two_lists(member<T>* left, member<T>* right) {
    member<T>* return_member = nullptr;
    if (left == nullptr) {
      return right;
    } else if (right == nullptr) {
      return left;
    }
    if (left->value <= right->value) {
      return_member = left;
      return_member->next = merge_two_lists(left->next, right);
    } else if (left->value > right->value) {
      return_member = right;
      return_member->next = merge_two_lists(left, right->next);
    }
    return return_member;
  }

  void create_first(T value = 0) {
    member<T>* first = new member<T>(value);
    this->begin_member = first;
    this->now_point = first;
    this->end_member = first;
    this->_n = 1;
    first = nullptr;
  }

  void next_el() {  // done
    if (now_point->next == nullptr) {
      throw "Limit of the container is exceeded";
    }
    // member<T>* tmp = this->now_point->next;
    this->now_point = this->now_point->next;
  };  // переходим к следующему элементу

  T get_elenemt() { return now_point->value; }  // done

  void add_New_member(T value_member = NULL) {  // создаем члена в конце листа и
    // end теперь указывает на него
    if (this->_n > 0) {
      this->end_member->next =
          new member<T>(value_member, nullptr, this->end_member);
      // this->end_member->next->before = this->end_member;
      this->end_member = this->end_member->next;
      this->_n += 1;
    } else {
      create_first(value_member);
    }
  }

  void operator()(T value) { now_point->value = value; }

 private:
  member<T>* begin_member;  //ну думаю что мы знаем что у нас идет первым
  member<T>* now_point;
  member<T>*
      end_member;  // ну мы же можем знать какой элемент у нас последний да?
  size_type _n;    // колличество элементов
};
}  // namespace s21

#endif  //  CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_