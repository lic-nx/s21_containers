#ifndef S21_LIST_ITERATOR_H_
#define S21_LIST_ITERATOR_H_

#include <iostream>
// #include <memory>
#include <initializer_list>  // предоставляет инициализационный список

#include "s21_list.h"

namespace s21 {
////////////////////////////////
/*________________list iterator_______________*/
////////////////////////////////
template <typename value_type>
class ListIterator {
 public:
  ListIterator() { ptr_ = nullptr; }
  ListIterator(member* ptr) : ptr_(ptr){};

  T operator*() {
    if (!this->ptr_) {
      throw std::invalid_argument("Value is nullptr");
    }
    return this->ptr_->value;
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

  ListIterator operator+(const size_type value) {
    list<T>* tmp = ptr_;
    for (size_type i = 0; i < value; i++) {
      tmp = tmp->next;
    }

    ListIterator res(tmp);
    return res;
  }

  ListIterator operator-(const size_type value) {
    member* tmp = ptr_;
    for (size_type i = 0; i < value; i++) {
      tmp = tmp->before;
    }
    ListIterator res(tmp);
    return res;
  }

  bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
  bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

 private:
  member* ptr_ = nullptr;
  friend class list<T>;
};

////////////////////////////////
/*________________list const iterator_______________*/
////////////////////////////////

template <typename value_type>
class ListConstIterator : public ListIterator<T> {
 public:
  ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
  const T& operator*() { return ListIterator<T>::operator*(); }
};
}  // namespace s21

#endif  // S21_LIST_ITERATOR_H_