#ifndef CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() = default;
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  ~array() = default;
  array &operator=(const array &other);
  array &operator=(array &&a);

  // Array Element access

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data();

  // array Iterators

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // array Capacity

  bool empty() const;
  size_type size();
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type data_[N] = {};
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_H_