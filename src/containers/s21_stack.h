#ifndef CPP2_S21_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_S21_STACK_H_

namespace s21 {
template <class T, class Container = List<T> >
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s) noexcept;
  ~Stack();
  Stack &operator=(Stack &&s) noexcept;

  const_reference top();

  bool empty() const;
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Stack &other);

  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  Container list_;
};

template <class value_type, class Container>
Stack<value_type, Container>::Stack() : list_() {}

template <class value_type, class Container>
Stack<value_type, Container>::Stack(
    std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push(*i);
  }
}

template <class value_type, class Container>
Stack<value_type, Container>::Stack(const Stack &s) : list_(s.list_) {}

template <class value_type, class Container>
Stack<value_type, Container>::Stack(Stack &&s) noexcept
    : list_(std::move(s.list_)) {}

template <class value_type, class Container>
Stack<value_type, Container>::~Stack() = default;

template <class value_type, class Container>
Stack<value_type, Container> &Stack<value_type, Container>::operator=(
    Stack &&s) noexcept {
  if (this != &s) {
    list_ = std::move(s.list_);
  }
  return *this;
}

template <class value_type, class Container>
typename Stack<value_type, Container>::const_reference
Stack<value_type, Container>::top() {
  return list_.front();
}

template <class value_type, class Container>
bool Stack<value_type, Container>::empty() const {
  return list_.empty();
}

template <class value_type, class Container>
typename Stack<value_type, Container>::size_type
Stack<value_type, Container>::size() {
  return list_.size();
}

template <class value_type, class Container>
void Stack<value_type, Container>::push(const_reference value) {
  list_.push_front(value);
}

template <class value_type, class Container>
void Stack<value_type, Container>::pop() {
  return list_.pop_front();
}

template <class value_type, class Container>
void Stack<value_type, Container>::swap(Stack &other) {
  std::swap(list_, other.list_);
}

template <class value_type, class Container>
template <class... Args>
void Stack<value_type, Container>::insert_many_front(Args &&...args) {
  for (const auto &item : {args...}) {
    push(item);
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_STACK_H_
