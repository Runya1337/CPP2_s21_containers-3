#ifndef CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_SET_H_
#define CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_SET_H_

namespace s21 {
template <typename KeyValue>
class Set {
 public:
  using value_type = KeyValue;
  using iterator = Iterator<KeyValue, KeyValue>;
  using const_iterator = ConstIterator<KeyValue, KeyValue>;
  using size_type = size_t;
  using Allocator = std::allocator<KeyValue>;

  Set() : tree_(){};

  Set(std::initializer_list<value_type> const& items) : tree_() {
    for (auto i = items.begin(); i != items.end(); ++i) {
      this->insert(*i);
    }
  };
  Set(const Set& s) : tree_(s.get_tree()){};
  Set(Set<KeyValue>&& s) = default;
  Set<KeyValue>& operator=(Set&& s) {
    if (this != &s) {
      tree_ = std::move(s.tree_);
    }
    return *this;
  };
  ~Set() {}

  iterator begin() { return tree_.begin(); };
  iterator end() { return tree_.end(); };
  bool empty() { return tree_.IsEmpty(); };

  int size() {
    Branch<KeyValue, KeyValue>* root = tree_.GetRoot();
    return (root != nullptr) ? root->size_ : 0;
  };

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(KeyValue);
  };

  void clear() {
    if (this->tree_.GetRoot()) {
      Branch<KeyValue, KeyValue>* root = this->tree_.GetRoot();
      this->tree_.Clear(root);
      this->tree_.SetRoot(nullptr);
    }
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<Set ::iterator, bool>> result;
    ((result.emplace_back(insert(std::forward<Args>(args))), ...));
    return result;
  }

  std::pair<iterator, bool> insert(const KeyValue& value) {
    std::pair<typename Set<KeyValue>::iterator, bool> result;
    this->tree_.Insert(value, 0);
    if (this->tree_.GetInserted()) {
      result =
          std::pair<typename Set<KeyValue>::iterator, bool>(find(value), true);
    } else {
      result =
          std::pair<typename Set<KeyValue>::iterator, bool>(find(value), false);
    }
    return result;
  };

  void erase(iterator pos) {
    if (pos != nullptr) {
      tree_.Remove_friend(tree_.GetRoot(), *pos);
    }
  };

  void swap(Set<KeyValue>& other) { tree_.Swap(other.tree_); };

  void merge(Set<KeyValue>& other) {
    if (this != &other) {
      for (auto i = other.begin(); i != other.end(); i++) {
        insert(*i);
      }
    }
    other.clear();
  };

  bool contains(const KeyValue& key) { return tree_.Search(key) != nullptr; };
  iterator find(const KeyValue& key) { return iterator(tree_.Search(key)); };
  const AVLTree<KeyValue, KeyValue>& get_tree() const { return tree_; };

 protected:
  AVLTree<KeyValue, KeyValue> tree_;
  Allocator allocator;
};

}  // namespace s21
#endif  // CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_SET_H_