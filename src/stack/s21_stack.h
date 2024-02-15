#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_

#include <initializer_list>  // предоставляет инициализационный список
#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class stack : private list<T> {
 public:
  using value_type = T;  // определяет тип
  using reference = value_type &;  // определяет тип ссылки на элемент
  using const_reference = const value_type &;  // тип ссылки на константу
  using size_type = std::size_t;  // определяет тип размера контейнера

  stack() { this->neutral_earthing(); };  // создание стека
  stack(std::initializer_list<value_type> const &items) {
    list<T>::create_first(*(items.begin()));
    for (auto it = items.begin() + 1; it != items.end(); ++it) {
      const auto &item = *it;
      list<T>::push_front(item);
    }
  };  // конструктор инициализации
  stack(const stack &s) : list<T>(s){};  // копируем

  stack(stack &&s) {
    list<T>::move(s);
    s.clear();
  };                               // перемещаем
  ~stack() { list<T>::clear(); };  // деструктор

  const_reference top() {
    return list<T>::front();
  };  // получаем верхний элемент
  bool empty() { return list<T>::empty(); };  // пуст ли контейнер
  size_type size() { return list<T>::size(); }  // возвращает число элементов

  void operator=(stack &&s) {
    list<T>::move(s);  // проверить работу
    s.clear();
  }  // тоже как конструктор перемещения

  void operator=(stack &s) { list<T>::copy(s); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    list<T>::insert_many_front(std::forward<Args>(args)...);
  }

  void push(const_reference value) {
    list<T>::push_front(value);
  };  // положить элемент вверх
  void pop() { list<T>::pop_front(); }  // удаление верхнего элемента
  void swap(stack &other) { list<T>::swap(other); };  // смена местами элементов

  value_type create_stack();
};
}  // namespace s21
#endif  //  CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_