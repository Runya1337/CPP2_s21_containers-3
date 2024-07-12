#ifndef CPP2_S21_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_VECTOR_H_

namespace s21 {
template <class T>
class Vector {
 public:
  template <bool Const>
  class VectorIterator {
   public:
    using value_type = std::conditional_t<Const, std::add_const_t<T>, T>;
    using pointer = std::conditional_t<Const, const T *, T *>;
    using reference = std::conditional_t<Const, const T &, T &>;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;

    VectorIterator() noexcept = default;
    explicit VectorIterator(pointer vector) : vector_(vector) {}

    template <bool OtherConst>
    constexpr VectorIterator(const VectorIterator<OtherConst> &other) noexcept
        : vector_(other.operator->()) {}

    reference operator*() { return *vector_; }
    pointer operator->() const { return &(*vector_); }
    reference operator[](int m) { return *vector_ + m; }
    reference value() { return *vector_; }

    VectorIterator &operator++() {
      ++vector_;
      return *this;
    }
    VectorIterator &operator--() {
      --vector_;
      return *this;
    }
    VectorIterator operator++(int) {
      VectorIterator ptr(*this);
      ++vector_;
      return ptr;
    }
    VectorIterator operator--(int) {
      VectorIterator ptr(*this);
      --vector_;
      return ptr;
    }
    VectorIterator &operator+=(int n) {
      vector_ += n;
      return *this;
    }
    VectorIterator &operator-=(int n) {
      vector_ -= n;
      return *this;
    }
    VectorIterator operator+(int n) const {
      VectorIterator ptr(*this);
      return ptr += n;
    }
    VectorIterator operator-(int n) const {
      VectorIterator ptr(*this);
      return ptr -= n;
    }
    difference_type operator-(VectorIterator const &r) const {
      return vector_ - r.vector_;
    }
    bool operator<(VectorIterator const &r) const {
      return vector_ < r.vector_;
    }
    bool operator<=(VectorIterator const &r) const {
      return vector_ <= r.vector_;
    }
    bool operator>(VectorIterator const &r) const {
      return vector_ > r.vector_;
    }
    bool operator>=(VectorIterator const &r) const {
      return vector_ >= r.vector_;
    }
    bool operator!=(const VectorIterator &r) const {
      return vector_ != r.vector_;
    }
    bool operator==(const VectorIterator &r) const {
      return vector_ == r.vector_;
    }

   private:
    pointer vector_;
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using iterator = VectorIterator<false>;
  using const_iterator = VectorIterator<true>;
  using size_type = std::size_t;

  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;
  ~Vector();
  Vector &operator=(Vector &&v) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  pointer data();

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back() noexcept;
  void swap(Vector &other) noexcept;

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type size_;
  size_type capacity_;
  pointer head_;
};

template <class value_type>
Vector<value_type>::Vector() : size_(0U), capacity_(0U), head_(nullptr) {}

template <class value_type>
Vector<value_type>::Vector(size_type n)
    : size_(n),
      capacity_(n),
      head_(reinterpret_cast<pointer>(
          new int8_t[sizeof(value_type) * capacity_]())) {}

template <class value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items)
    : size_(items.size()),
      capacity_(items.size()),
      head_(reinterpret_cast<pointer>(
          new int8_t[sizeof(value_type) * capacity_])) {
  int i = 0;
  for (const auto &item : items) {
    head_[i] = item;
    ++i;
  }
}

template <class value_type>
Vector<value_type>::Vector(Vector &&v) noexcept
    : size_(v.size_), capacity_(v.capacity_), head_(v.head_) {
  v.head_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <class value_type>
Vector<value_type>::Vector(const Vector &v)
    : size_(v.size_), capacity_(v.capacity_) {
  head_ = new value_type[capacity_]();
  for (size_type i = 0; i < size_; ++i) {
    head_[i] = v.head_[i];
  }
}

template <class value_type>
Vector<value_type> &Vector<value_type>::operator=(Vector &&v) noexcept {
  if (head_ != nullptr) {
    delete[] head_;
  }
  head_ = v.head_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  v.head_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
  return *this;
}

template <class value_type>
Vector<value_type>::~Vector() {
  for (size_type i = 0; i < size_; ++i) {
    (head_ + i)->~value_type();
  }
  ::operator delete(head_);
}

template <class value_type>
typename Vector<value_type>::reference Vector<value_type>::at(size_type pos) {
  if (pos >= size()) {
    throw std::out_of_range("Index is out of range");
  }
  return head_[pos];
}

template <class value_type>
typename Vector<value_type>::reference Vector<value_type>::operator[](
    size_type pos) {
  return head_[pos];
}

template <class value_type>
typename Vector<value_type>::const_reference Vector<value_type>::front() const {
  return *head_;
}

template <class value_type>
typename Vector<value_type>::const_reference Vector<value_type>::back() const {
  return *(head_ + size_ - 1);
}

template <class value_type>
typename Vector<value_type>::pointer Vector<value_type>::data() {
  return head_;
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::begin()
    const noexcept {
  return iterator(head_);
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::end() const noexcept {
  return iterator(head_ + size_);
}

template <class value_type>
typename Vector<value_type>::const_iterator Vector<value_type>::cbegin()
    const noexcept {
  return const_iterator(head_);
}

template <class value_type>
typename Vector<value_type>::const_iterator Vector<value_type>::cend()
    const noexcept {
  return const_iterator(head_ + size_);
}

template <class value_type>
bool Vector<value_type>::empty() const {
  return begin() == end();
}

template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::size() const {
  return size_;
}

template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::capacity() const {
  return capacity_;
}

template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::max_size() const {
  return SIZE_MAX / sizeof(value_type);
}

template <class value_type>
void Vector<value_type>::reserve(size_type size) {
  if (size > capacity_) {
    auto newData = reinterpret_cast<pointer>(
        new int8_t[sizeof(value_type) * capacity_ == 0 ? 1 : capacity_]);
    std::uninitialized_copy(head_, head_ + size_, newData);
    for (size_type i = 0; i < size_; ++i) {
      (head_ + i)->~value_type();
    }
    delete[] reinterpret_cast<int8_t *>(head_);
    head_ = newData;
    capacity_ = size;
  }
}

template <class value_type>
void Vector<value_type>::shrink_to_fit() {
  if (size_ != capacity_) {
    auto newData =
        reinterpret_cast<pointer>(new int8_t[sizeof(value_type) * size_]);
    std::uninitialized_copy(head_, head_ + size_, newData);
    for (size_type i = 0; i < size_; ++i) {
      (head_ + i)->~value_type();
    }
    delete[] reinterpret_cast<int8_t *>(head_);
    head_ = newData;
    capacity_ = size_;
  }
}

template <class value_type>
void Vector<value_type>::clear() noexcept {
  size_ = 0;
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type index = pos - begin();
  if (size_ == capacity_) {
    reserve(capacity_ * 2);
  }
  for (size_type i = size_; i > index; --i) {
    head_[i] = std::move(head_[i - 1]);
  }
  head_[index] = value;
  ++size_;
  return begin() + index;
}

template <class value_type>
template <class... Args>
typename Vector<value_type>::iterator Vector<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  Vector<value_type> tmp{args...};
  iterator index = begin() + (pos - cbegin());
  for (size_type i = 0; i < tmp.size(); ++i) {
    index = insert(index, tmp[i]);
    index++;
  }
  return index;
}

template <class value_type>
template <class... Args>
void Vector<value_type>::insert_many_back(Args &&...args) {
  Vector<value_type> tmp{args...};
  for (size_type i = 0; i < tmp.size(); ++i) {
    push_back(tmp[i]);
  }
}

template <class value_type>
void Vector<value_type>::erase(iterator pos) {
  if (pos >= begin() && pos < end()) {
    iterator it = pos;
    iterator next = pos + 1;
    while (next < end()) {
      *it = *next;
      ++it;
      ++next;
    }
    --size_;
  }
}

template <class value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(2 * (capacity_ == 0 ? 1 : capacity_));
  }
  new (head_ + size_) value_type(value);
  ++size_;
}

template <class value_type>
void Vector<value_type>::pop_back() noexcept {
  if (size_ > 0) {
    (head_ + size_ - 1)->~value_type();
    --size_;
  }
}

template <class value_type>
void Vector<value_type>::swap(Vector &other) noexcept {
  using std::swap;
  swap(size_, other.size_);
  swap(capacity_, other.capacity_);
  swap(head_, other.head_);
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_VECTOR_H_
