#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

namespace s21 {
template <class T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using size_type = std::size_t;

  struct Node {
   public:
    Node(value_type data) {
      this->data_ = data;
      this->prev_ = nullptr;
      this->next_ = nullptr;
    }
    Node *prev_;
    Node *next_;
    value_type data_;
  };

  template <bool Const>
  class ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::conditional_t<Const, std::add_const_t<T>, T>;
    using node_pointer = std::conditional_t<Const, Node const *, Node *>;
    using difference_type = std::ptrdiff_t;
    using pointer = std::conditional_t<Const, const T *, T *>;
    using reference = std::conditional_t<Const, const T &, T &>;

    constexpr ListIterator() noexcept = default;
    constexpr ListIterator(node_pointer data) : node_(data) {}

    template <bool OtherConst>
    constexpr ListIterator(const ListIterator<OtherConst> &other) noexcept
        : node_(const_cast<node_pointer>(other.get_node())) {}

    reference operator*() const { return node_->data_; }
    pointer operator->() const { return &(operator*()); }
    ListIterator &operator++() {
      node_ = node_->next_;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator tmp(*this);
      operator++();
      return tmp;
    }
    ListIterator &operator--() {
      node_ = node_->prev_;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator tmp(*this);
      operator--();
      return tmp;
    }
    bool operator==(const ListIterator &other) const {
      return node_ == other.node_;
    }
    bool operator!=(const ListIterator &other) const {
      return !operator==(other);
    }
    node_pointer get_node() const { return node_; }

   private:
    node_pointer node_ = nullptr;
  };

  using iterator = ListIterator<false>;
  using const_iterator = ListIterator<true>;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l) noexcept;
  ~List();
  List &operator=(List &&l) noexcept;

  const_reference front();
  const_reference back();

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  size_type size_;
  Node *head_;
  Node *merge_sort(Node *head);
  Node *merge_sorted(Node *left, Node *right);
};

template <class value_type>
List<value_type>::List() : size_(0U) {
  Node *ptr = new Node(value_type());
  head_ = ptr;
  head_->next_ = ptr;
  head_->prev_ = ptr;
}

template <class value_type>
List<value_type>::List(size_type n) : size_(0U) {
  Node *ptr = new Node(value_type());
  head_ = ptr;
  head_->next_ = ptr;
  head_->prev_ = ptr;
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <class value_type>
List<value_type>::List(std::initializer_list<value_type> const &items)
    : size_(0U) {
  Node *ptr = new Node(value_type());
  head_ = ptr;
  for (const auto &item : items) {
    push_back(item);
  }
}

template <class value_type>
List<value_type>::List(const List &l) : size_(0) {
  Node *prev = new Node(value_type());
  head_ = prev;
  Node *current = l.head_->next_;
  while (current != l.head_) {
    Node *new_node = new Node(current->data_);
    prev->next_ = new_node;
    new_node->prev_ = prev;
    prev = new_node;
    current = current->next_;
    ++size_;
  }
  prev->next_ = head_;
  head_->prev_ = prev;
}

template <class value_type>
List<value_type>::List(List &&l) noexcept {
  head_ = l.head_;
  size_ = l.size_;
  l.head_ = nullptr;
  l.size_ = 0;
}

template <class value_type>
List<value_type>::~List() {
  clear();
  delete head_;
}

template <class value_type>
List<value_type> &List<value_type>::operator=(List &&l) noexcept {
  clear();
  head_ = l.head_;
  size_ = l.size_;
  l.head_ = nullptr;
  l.size_ = 0;
  return *this;
}

template <class value_type>
typename List<value_type>::const_reference List<value_type>::front() {
  return *begin();
}

template <class value_type>
typename List<value_type>::const_reference List<value_type>::back() {
  iterator temp = end();
  --temp;
  return *temp;
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::begin() const noexcept {
  return iterator(head_->next_);
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::end() const noexcept {
  return iterator(head_);
}

template <class value_type>
typename List<value_type>::const_iterator List<value_type>::cbegin()
    const noexcept {
  return const_iterator(head_->next_);
}

template <class value_type>
typename List<value_type>::const_iterator List<value_type>::cend()
    const noexcept {
  return const_iterator(head_);
}

template <class value_type>
bool List<value_type>::empty() const {
  return begin() == end();
}

template <class value_type>
typename List<value_type>::size_type List<value_type>::size() const {
  return size_;
}

template <class value_type>
typename List<value_type>::size_type List<value_type>::max_size() const {
  return SIZE_MAX / sizeof(value_type);
}

template <class value_type>
void List<value_type>::clear() {
  while (size_) {
    pop_front();
  }
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::insert(
    iterator pos, const_reference value) {
  Node *new_node = new Node(value);
  if (size_ == 0) {
    new_node->prev_ = new_node->next_ = head_;
    head_->next_ = head_->prev_ = new_node;
  } else {
    Node *next_node = pos.get_node();
    new_node->prev_ = next_node->prev_;
    new_node->next_ = next_node;
    next_node->prev_ = next_node->prev_->next_ = new_node;
  }
  ++size_;
  return iterator(new_node);
}

template <class value_type>
template <class... Args>
typename List<value_type>::iterator List<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  const_iterator index = pos;
  for (const auto &item : {args...}) {
    index = insert(index, item);
    index++;
  }
  return index;
}

template <class value_type>
template <class... Args>
void List<value_type>::insert_many_back(Args &&...args) {
  for (const auto &item : {args...}) {
    push_back(item);
  }
}

template <class value_type>
template <class... Args>
void List<value_type>::insert_many_front(Args &&...args) {
  List<value_type> tmp{args...};
  tmp.reverse();
  for (const auto &item : tmp) {
    push_front(item);
  }
}

template <class value_type>
void List<value_type>::erase(iterator pos) {
  Node *to_erase = pos.get_node();
  to_erase->prev_->next_ = to_erase->next_;
  to_erase->next_->prev_ = to_erase->prev_;
  delete to_erase;
  --size_;
}

template <class value_type>
void List<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <class value_type>
void List<value_type>::pop_back() {
  iterator temp = end();
  --temp;
  erase(temp);
}

template <class value_type>
void List<value_type>::push_front(const_reference value) {
  insert(begin(), value);
}

template <class value_type>
void List<value_type>::pop_front() {
  erase(begin());
}

template <class value_type>
void List<value_type>::swap(List &other) {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
}

template <class value_type>
void List<value_type>::merge(List &other) {
  if (this != &other) {
    iterator this_iter = begin();
    iterator other_iter = other.begin();
    while (!other.empty()) {
      if (this->empty() || this_iter == end() || *this_iter > *other_iter) {
        insert(this_iter, *other_iter);
        other.erase(other_iter++);
      } else {
        ++this_iter;
      }
    }
  }
}

template <class value_type>
void List<value_type>::splice(const_iterator pos, List &other) {
  Node *previous = pos.get_node()->prev_;
  Node *current = const_cast<Node *>(pos.get_node());
  Node *other_first = other.begin().get_node();
  Node *other_last = std::prev(other.end()).get_node();

  current->prev_ = other_last;
  other_last->next_ = previous->next_;
  previous->next_ = other_first;
  other_first->prev_ = previous;

  other.head_->prev_ = other.head_->next_ = other.head_;
  size_ += other.size_;
  other.size_ = 0;
}

template <class value_type>
void List<value_type>::reverse() {
  for (size_type i = 0; i <= size(); ++i) {
    std::swap(head_->prev_, head_->next_);
    head_ = head_->prev_;
  }
}

template <class value_type>
void List<value_type>::unique() {
  if (size_ > 1) {
    iterator current = begin();
    iterator next = current;
    ++next;
    while (next != end()) {
      if (*current == *next) {
        erase(next);
        next = current;
        ++next;
      } else {
        current = next;
        ++next;
      }
    }
  }
}

template <class value_type>
void List<value_type>::sort() {
  if (size_ > 1) {
    Node *first_node = head_->next_;
    Node *last_node = std::prev(end()).get_node();
    Node *head = head_;

    first_node->prev_ = nullptr;
    last_node->next_ = nullptr;

    first_node = merge_sort(first_node);
    first_node->prev_ = head;
    head_->next_ = first_node;
    Node *temp = head_;
    while (temp->next_ != nullptr) {
      temp = temp->next_;
    }
    temp->next_ = head_;
    head_->prev_ = temp;
  }
}

template <class value_type>
typename List<value_type>::Node *List<value_type>::merge_sort(Node *head) {
  if (head == nullptr || head->next_ == nullptr) {
    return head;
  }
  Node *slow = head;
  Node *fast = head->next_;
  while (fast != nullptr && fast->next_ != nullptr) {
    slow = slow->next_;
    fast = fast->next_->next_;
  }
  Node *second_half = slow->next_;
  slow->next_ = nullptr;
  Node *left = merge_sort(head);
  Node *right = merge_sort(second_half);
  return merge_sorted(left, right);
}

template <class value_type>
typename List<value_type>::Node *List<value_type>::merge_sorted(Node *left,
                                                                Node *right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  Node *result = nullptr;
  if (left->data_ <= right->data_) {
    result = left;
    result->prev_ = nullptr;
    result->next_ = merge_sorted(left->next_, right);
    result->next_->prev_ = result;
  } else {
    result = right;
    result->prev_ = nullptr;
    result->next_ = merge_sorted(left, right->next_);
    result->next_->prev_ = result;
  }
  return result;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_
