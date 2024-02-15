#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_

#include <initializer_list>  // предоставляет инициализационный список
#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class queue : private list<T> {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;

  queue() { this->neutral_earthing(); }

  queue(std::initializer_list<value_type> const& items) {
    list<T>::create_first(*(items.begin()));
    for (auto it = items.begin() + 1; it != items.end(); ++it) {
      const auto& item = *it;
      list<T>::add_New_member(item);
    }
  }

  queue(const queue& q) : list<T>(q) {}

  queue(queue&& q) {
    list<T>::move(q);
    q.clear();
  }

  ~queue() { list<T>::clear(); }

  void operator=(queue& q) { list<T>::copy(q); };

  void operator=(queue&& q) {
    list<T>::move(q);  // проверить работу
    q.clear();
  }

  const_reference front() { return list<T>::front(); };

  const_reference back() { return list<T>::back(); };

  bool empty() { return list<T>::empty(); }

  size_type size() { return list<T>::size(); };

  void push(const_reference value) { list<T>::push_back(value); }

  void pop() { list<T>::pop_front(); }

  template <typename... Args>

  void insert_many_back(Args&&... args) {
    list<T>::insert_many_back(std::forward<Args>(args)...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    list<T>::insert_many_front(std::forward<Args>(args)...);
  }

  void swap(queue& other) { list<T>::swap(other); }
};

}  // namespace s21

#endif  //  CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_