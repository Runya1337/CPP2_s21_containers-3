#ifndef CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_MAP_H_
#define CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_MAP_H_

#include <vector>

#include "s21_avl_tree.h"

namespace s21 {
template <typename KeyType, typename ValueType>
class Map {
 public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = size_t;
  using Allocator = std::allocator<KeyType>;
  using iterator = Iterator<KeyType, ValueType>;
  using const_iterator = ConstIterator<KeyType, ValueType>;
  bool isEmpty() { return tree_.IsEmpty(); }
  iterator find(const KeyType& key) { return iterator(tree_.Search(key)); };
  Map() : tree_() {}
  Map(std::initializer_list<value_type> const& items) {
    for (auto& item : items) {
      this->insert(item);
    }
  }
  Map(const Map& m) : tree_(m.tree_) {}
  Map(Map&& m) noexcept : tree_(std::move(m.tree_)) {}
  Map& operator=(const Map& m) {
    if (this != &m) {
      tree_ = m.tree_;
    }
    return *this;
  }
  Map& operator=(Map&& m) noexcept {
    if (this != &m) {
      tree_ = std::move(m.tree_);
    }
    return *this;
  }
  ~Map() {}

  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = tree_.Insert(value.first, value.second);
    iterator it(result);
    return {it, false};
  }
  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return insert({key, obj});
  }
  void merge(Map& other) {
    if (this == &other) return;
    for (Iterator<KeyType, ValueType> i = other.begin(); i != nullptr; i++) {
      insert_or_assign(i.GetCurrent()->key_, i.GetCurrent()->value_);
    }
    other.tree_.SetRoot(nullptr);
  }
  std::pair<iterator, bool> insert_or_assign(const KeyType& key,
                                             const ValueType& obj) {
    auto branch_search = tree_.Search(key);
    bool inserted = false;
    if (branch_search == nullptr) {
      branch_search = tree_.Insert(key, obj);
      inserted = true;
    } else {
      branch_search->second = obj;
    }
    return {iterator(branch_search), inserted};
  }
  iterator begin() { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  bool empty() const { return tree_.IsEmpty(); }
  int size() { return tree_.GetSizeFriend(); }
  void clear() { tree_.Clear(tree_.GetRoot()); }
  mapped_type& operator[](const key_type& key) {
    auto tmp = tree_.Search(key);
    if (tmp == nullptr) {
      auto res = tree_.Insert(key, mapped_type());
      return res->value_;
    }
    return tmp->value_;
  }
  mapped_type& at(const key_type& key) {
    auto tmp = find(key);
    if (tmp == end() || tmp == nullptr) {
      throw std::out_of_range("Index out of range");
    }
    return (tmp->second);
  }
  void erase(iterator pos) {
    if (pos != nullptr) {
      tree_.Remove_friend(tree_.GetRoot(), pos.GetCurrent()->key_);
    }
  }
  size_type max_size() const { return Allocator().max_size(); }
  bool contains(const KeyType& key) {
    bool result = (tree_.Search(key) != nullptr);
    return result;
  }
  void swap(Map& other) noexcept { tree_.Swap(other.tree_); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    insert_many_helper(results, std::forward<Args>(args)...);
    return results;
  }

  template <typename... Args>
  void insert_many_helper(std::vector<std::pair<iterator, bool>>& results,
                          KeyType key, ValueType value, Args&&... args) {
    auto result = insert({key, value});
    results.emplace_back(result);
    if constexpr (sizeof...(args) > 0) {
      insert_many_helper(results, std::forward<Args>(args)...);
    }
  }

 private:
  AVLTree<key_type, mapped_type> tree_;
};

}  // namespace s21
#endif  // CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_MAP_H_
