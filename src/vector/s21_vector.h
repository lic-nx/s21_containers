#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;  // определяет тип
  using reference = T &;  // определяет тип ссылки на элемент
  using const_reference = const T &;  // тип ссылки на константу
  using iterator = T *;  // тип для итерации по контейнеру
  using const_iterator = const T *;
  using size_type = size_t;  // определяет тип размера контейнера

  vector();  // конструктор по умолчанию
  vector(size_type n);  // конструктор создания вектора размера n
  vector(std::initializer_list<value_type> const
             &items);  // конструктор списка инициализаторов, создает вектор,
                       // инициализированный с помощью std::initializer_list
  vector(const vector &other);      // копирование
  vector(vector &&other) noexcept;  // перемещение
  ~vector();                        // деструктор
  vector &operator=(const vector &other);
  vector &operator=(vector &&other);  // перегрузка оператора присваивания для
                                      // движущегося объекта

  // Vector Element access

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data();

  // Vector Iterators

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Vector Capacity

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // Vector Modifiers

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // insert_many

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type size_;
  size_type capacity_;
  value_type *data_;
  void resize(size_type size);
  void Deallocate();
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_