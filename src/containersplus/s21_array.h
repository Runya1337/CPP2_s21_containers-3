#ifndef CPP2_S21_CONTAINERSPLUS_S21_ARRAY_H_
#define CPP2_S21_CONTAINERSPLUS_S21_ARRAY_H_

namespace s21 {
template <class T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  Array() = default;
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a) = default;
  Array(Array &&a) noexcept = default;
  ~Array() = default;
  Array &operator=(Array &&a) noexcept = default;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin() noexcept;
  iterator end() noexcept;

  bool empty();
  size_type size();
  size_type max_size();

  void swap(Array &other) noexcept;
  void fill(const_reference value);

 private:
  value_type head_[N];
};

template <class value_type, std::size_t N>
Array<value_type, N>::Array(std::initializer_list<value_type> const &items) {
  size_type i = 0;
  for (const auto &item : items) {
    head_[i] = item;
    ++i;
  }
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::at(
    size_type pos) {
  if (pos >= size()) {
    throw std::out_of_range("Index is out of range");
  }
  return head_[pos];
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::operator[](
    size_type pos) {
  return head_[pos];
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::front()
    const {
  return head_[0];
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::back()
    const {
  return head_[N - 1];
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::iterator Array<value_type, N>::data() {
  return head_;
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::iterator Array<value_type, N>::begin() noexcept {
  return head_;
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::iterator Array<value_type, N>::end() noexcept {
  return head_ + N;
}

template <class value_type, std::size_t N>
bool Array<value_type, N>::empty() {
  return begin() == end();
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::size_type Array<value_type, N>::size() {
  return N;
}

template <class value_type, std::size_t N>
typename Array<value_type, N>::size_type Array<value_type, N>::max_size() {
  return N;
}

template <class value_type, std::size_t N>
void Array<value_type, N>::swap(Array &other) noexcept {
  std::swap(head_, other.head_);
}

template <class value_type, std::size_t N>
void Array<value_type, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    head_[i] = value;
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERSPLUS_S21_ARRAY_H_
