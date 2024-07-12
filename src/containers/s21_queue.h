#ifndef CPP2_S21_CONTAINERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_S21_QUEUE_H_

namespace s21 {
template <class T, class Container = List<T>>
class Queue {
 public:
  using value_type = T;
  //  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue();
  Queue &operator=(Queue &&q) noexcept;

  const_reference front();
  const_reference back();

  bool empty() const;
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Queue &other);

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  Container list_;
};

template <class value_type, class Container>
Queue<value_type, Container>::Queue() : list_() {}

template <class value_type, class Container>
Queue<value_type, Container>::Queue(
    std::initializer_list<value_type> const &items)
    : list_(items) {}

template <class value_type, class Container>
Queue<value_type, Container>::Queue(const Queue &q) : list_(q.list_) {}

template <class value_type, class Container>
Queue<value_type, Container>::Queue(Queue &&q) noexcept
    : list_(std::move(q.list_)) {}

template <class value_type, class Container>
Queue<value_type, Container>::~Queue() = default;

template <class value_type, class Container>
Queue<value_type, Container> &Queue<value_type, Container>::operator=(
    Queue &&q) noexcept {
  if (this != &q) {
    list_ = std::move(q.list_);
  }
  return *this;
}

template <class value_type, class Container>
typename Queue<value_type, Container>::const_reference
Queue<value_type, Container>::front() {
  return list_.front();
}

template <class value_type, class Container>
typename Queue<value_type, Container>::const_reference
Queue<value_type, Container>::back() {
  return list_.back();
}

template <class value_type, class Container>
bool Queue<value_type, Container>::empty() const {
  return list_.empty();
}

template <class value_type, class Container>
typename Queue<value_type, Container>::size_type
Queue<value_type, Container>::size() {
  return list_.size();
}

template <class value_type, class Container>
void Queue<value_type, Container>::push(const_reference value) {
  list_.push_back(value);
}

template <class value_type, class Container>
void Queue<value_type, Container>::pop() {
  return list_.pop_front();
}

template <class value_type, class Container>
void Queue<value_type, Container>::swap(Queue &other) {
  std::swap(list_, other.list_);
}

template <class value_type, class Container>
template <class... Args>
void Queue<value_type, Container>::insert_many_back(Args &&...args) {
  for (const auto &item : {args...}) {
    push(item);
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_QUEUE_H_
