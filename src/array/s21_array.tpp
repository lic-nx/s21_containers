#ifndef CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_TPP_

namespace s21 {

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) {
  if (items.size() > N) {
    throw std::out_of_range("Too many initializer values");
  }
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N>& other) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N>&& other) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(other.data_[i]);
  }
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array<T, N>& other) {
  // if (this != &other) {
  //     delete[] data_;
  //     std::swap(data_, other.data_);
  // }
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(other.data_[i]);
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& other) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(other.data_[i]);
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) throw std::out_of_range("Index is out of range.");
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) throw std::out_of_range("Index is out of range.");
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  // if (pos >= N) throw std::out_of_range("Index is out of range.");
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return data_ + N;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const {
  return !N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N>& other) {
  for (std::size_t i = 0; i < N; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const value_type& val) {
  for (std::size_t i = 0; i < N; ++i) {
    data_[i] = val;
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_ARRAY_S21_ARRAY_TPP_