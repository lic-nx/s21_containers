#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_TPP_

namespace s21 {

template <typename T>
vector<T>::vector() : size_(0), capacity_(0), data_(nullptr) {}

template <typename T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), data_(new value_type[n]) {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()),
      capacity_(items.size()),
      data_(new value_type[items.size()]) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::vector(const vector &other)
    : size_(other.size_),
      capacity_(other.capacity_),
      data_(new value_type[other.capacity_]) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
vector<T>::vector(vector &&other) noexcept
    : size_(std::move(other.size_)),
      capacity_(std::move(other.capacity_)),
      data_(std::move(other.data_)) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T>
vector<T>::~vector() {
  Deallocate();
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&other) {
  if (this != &other) {
    Deallocate();
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }
  return *this;
}

// Vector Element access

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index is out of range.");
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Index is out of range.");
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return data_;
}

// Vector Iterators

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return iterator(data_ + size_);
}

// Vector Capacity

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(T) / 2;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    return;
  }
  value_type *new_data = new value_type[size];
  std::copy(data_, data_ + size_, new_data);
  delete[] data_;
  data_ = new_data;
  capacity_ = size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type *new_data = new value_type[size_];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}

// Vector Modifiers

template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const T &value) {
  size_type position = pos - begin();
  if (position > size_) {
    throw std::out_of_range("Position to insert is out of range.");
  }
  if (size_ == capacity_) {
    if (capacity_ != 0) {
      reserve(capacity_ * 2);
    } else {
      reserve(1);
    }
  }
  iterator new_pos = begin() + position;
  std::move(new_pos, end(), new_pos + 1);
  *new_pos = value;
  ++size_;

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - data_;
  for (size_type i = index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }
  size_--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      reserve(1);
    } else {
      reserve(capacity_ * 2);
    }
  }
  data_[size_] = value;
  size_++;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    size_--;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> v;
  for (const auto &arg : {args...}) {
    v.push_back(arg);
  }

  iterator iter = begin() + (pos - cbegin());
  for (size_type i = 0; i < v.size(); ++i) {
    iter = insert(iter, v[i]);
    ++iter;
  }
  return iter;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}

template <typename T>
void vector<T>::Deallocate() {
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_TPP_