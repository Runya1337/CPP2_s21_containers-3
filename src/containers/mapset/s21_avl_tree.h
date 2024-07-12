#ifndef CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_AVL_TREE_H_
#define CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_AVL_TREE_H_

namespace s21 {
template <typename KeyType, typename ValueType>
class Branch {
 public:
  KeyType key_;
  ValueType value_;
  int height_;
  KeyType first;
  ValueType second;
  int size_;
  bool isSentinel_;
  Branch<KeyType, ValueType> *left_;
  Branch<KeyType, ValueType> *right_;
  Branch<KeyType, ValueType> *parent_;

  Branch(const KeyType &key, const ValueType &value)
      : key_(key),
        value_(value),
        height_(1),
        size_(1),
        isSentinel_(false),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr){};

  Branch(KeyType &key, ValueType &value)
      : key_(key),
        value_(value),
        height_(1),
        first(key),
        second(value),
        size_(1),
        isSentinel_(false),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr){};

  ~Branch() = default;
};

template <typename KeyType, typename ValueType>
class Iterator {
 public:
  using key_type = KeyType;
  using reference = KeyType &;
  using const_reference = const KeyType &;
  using pointer = KeyType *;

  Iterator(Branch<KeyType, ValueType> *node = nullptr,
           Branch<KeyType, ValueType> *root = nullptr)
      : node_(node), root_(root) {}

  Iterator(const Iterator &) = default;
  Iterator &operator=(const Iterator &) = default;
  ~Iterator() = default;

  Iterator operator+(const size_t value) {
    Iterator tmp = *this;
    for (size_t i = 0; i < value; i++) {
      ++tmp;
    }
    return tmp;
  }

  Iterator &operator++() {
    if (node_ != nullptr) {
      if (node_->right_ != nullptr) {
        node_ = node_->right_;
        while (node_->left_ != nullptr) {
          node_ = node_->left_;
        }
      } else {
        Branch<KeyType, ValueType> *parent = node_->parent_;
        while (parent != nullptr && node_ == parent->right_) {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  int GetSize(Branch<KeyType, ValueType> *node) {
    int answer = 0;
    if (node) {
      answer = node->size_;
    }
    return answer;
  };

  Iterator &operator--() { return OperatorHelper(); }
  Iterator operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
  }
  bool operator==(const Iterator &other) const { return node_ == other.node_; }
  bool operator!=(const Iterator &other) const { return node_ != other.node_; }

  reference operator*() const {
    if (node_ == nullptr) {
      throw std::logic_error("Iterator don't have value");
    }
    return node_->key_;
  }

  Branch<KeyType, ValueType> *operator->() const { return node_; }

  Branch<KeyType, ValueType> *MaximumKey_iter(
      Branch<KeyType, ValueType> *node) {
    Branch<KeyType, ValueType> *node_search = node;
    while (node_search->right_ != nullptr) {
      node_search = node_search->right_;
    }
    return node_search;
  }

  Branch<KeyType, ValueType> *GetCurrent() { return node_; }

  Iterator &OperatorHelper() {
    if (node_ != nullptr) {
      if (node_->left_ != nullptr) {
        node_ = node_->left_;
        while (node_->right_ != nullptr) {
          node_ = node_->right_;
        }
      } else {
        Branch<KeyType, ValueType> *parent = node_->parent_;
        while (parent != nullptr && node_ == parent->left_) {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
    return *this;
  }

  Branch<KeyType, ValueType> *GetRootIter() const { return this->root_; };

 protected:
  Branch<KeyType, ValueType> *node_;
  Branch<KeyType, ValueType> *root_;
};

template <typename KeyType, typename ValueType>
class ConstIterator : public Iterator<const KeyType, const ValueType> {
 public:
  using Iterator<const KeyType, const ValueType>::Iterator;

  using typename Iterator<const KeyType, const ValueType>::key_type;
  using typename Iterator<const KeyType, const ValueType>::reference;
  using typename Iterator<const KeyType, const ValueType>::const_reference;
  using typename Iterator<const KeyType, const ValueType>::pointer;
};

template <typename KeyType, typename ValueType>
class AVLTree {
 public:
  AVLTree() : root(nullptr), inserted(false){};
  AVLTree(const AVLTree &other) : root(CopyTree(other.GetRoot())){};

  ~AVLTree() {
    if (GetRoot() != nullptr) {
      Clear(root);
    }
  };

  AVLTree<KeyType, ValueType> &operator=(AVLTree &&other) noexcept {
    if (this != &other) {
      Clear(root);
      root = other.root;
      other.root = nullptr;
    }
    return *this;
  };

  AVLTree<KeyType, ValueType> &operator=(const AVLTree &other) {
    if (this != &other) {
      Clear(root);
      root = CopyTree(other.root);
    }
    return *this;
  }

  Branch<KeyType, ValueType> *Insert(KeyType key, ValueType value) {
    root = Insert(root, key, value, nullptr);
    return root;
  };

  void SetRepated(bool set_setting) { repeate_ = set_setting; }
  Branch<KeyType, ValueType> *GetRoot() const { return this->root; };

  void Swap(AVLTree<KeyType, ValueType> &other) {
    std::swap(root, other.root);
  };

  void Clear(Branch<KeyType, ValueType> *node) {
    if (node != nullptr) {
      Clear(node->left_);
      Clear(node->right_);
      delete node;
    }
    root = nullptr;
  };

  bool GetInserted() { return inserted; };
  Branch<KeyType, ValueType> *MaximumKey(Branch<KeyType, ValueType> *node) {
    Branch<KeyType, ValueType> *node_search = node;
    while (node_search->right_ != nullptr) {
      node_search = node_search->right_;
    }
    return node_search;
  };

  Branch<KeyType, ValueType> *GetMin() { return FindMin(GetRoot()); }
  Branch<KeyType, ValueType> *GetMax() {
    Branch<KeyType, ValueType> *current = GetRoot();
    while (current != nullptr && current->right_ != nullptr) {
      current = current->right_;
    }
    return current;
  }

  Iterator<KeyType, ValueType> begin() {
    using IteratorType = std::conditional_t<std::is_const_v<KeyType>,
                                            ConstIterator<KeyType, ValueType>,
                                            Iterator<KeyType, ValueType>>;
    return IteratorType(GetMin(), GetRoot());
  }

  Iterator<KeyType, ValueType> end() {
    using IteratorType = std::conditional_t<std::is_const_v<KeyType>,
                                            ConstIterator<KeyType, ValueType>,
                                            Iterator<KeyType, ValueType>>;
    return IteratorType(GetMax(), GetRoot());
  }

  bool IsEmpty() const { return root == nullptr; }
  void SetRoot(Branch<KeyType, ValueType> *node) { root = node; }

  Branch<KeyType, ValueType> *Remove_friend(Branch<KeyType, ValueType> *node,
                                            KeyType key) {
    return Remove(node, key);
  }

  Branch<KeyType, ValueType> *Search(KeyType key) {
    Branch<KeyType, ValueType> *node_search = root;
    while (node_search != nullptr && node_search->key_ != key) {
      node_search =
          key < node_search->key_ ? node_search->left_ : node_search->right_;
    }
    return node_search;
  };

  int GetSizeFriend() { return GetSize(GetRoot()); };
  bool GetRepated() { return repeate_; }

 private:
  Branch<KeyType, ValueType> *root;
  bool inserted;
  bool repeate_ = false;

  int GetSize(Branch<KeyType, ValueType> *node) {
    if (node != nullptr) {
      return node->size_;
    }
    return 0;
  };

  int GetHeight(Branch<KeyType, ValueType> *node) {
    if (!node) {
      return -1;
    }
    return node->height_;
  };

  void UpdateSize(Branch<KeyType, ValueType> *node) {
    if (node) {
      node->size_ = 1 + GetSize(node->left_) + GetSize(node->right_);
      UpdateSize(node->left_);
      UpdateSize(node->right_);
    }
  };

  int BalanceFactor(Branch<KeyType, ValueType> *node) {
    if (!node) return 0;
    return (GetHeight(node->left_) - GetHeight(node->right_));
  };

  void UpdateHeight(Branch<KeyType, ValueType> *node) {
    int hl = GetHeight(node->left_);
    int hr = GetHeight(node->right_);
    node->height_ = (hl > hr ? hl : hr) + 1;
  };

  Branch<KeyType, ValueType> *Balance(Branch<KeyType, ValueType> *node) {
    UpdateHeight(node);

    if (BalanceFactor(node) == 2) {
      if (BalanceFactor(node->left_) == -1) {
        node->left_ = RotateLeft(node->left_);
        UpdateSize(node->left_);
      }
      node = RotateRight(node);
      GetHeight(node);
    }

    if (BalanceFactor(node) == -2) {
      if (BalanceFactor(node->right_) == 1) {
        node->right_ = RotateRight(node->right_);
        UpdateSize(node->right_);
      }
      node = RotateLeft(node);
      UpdateSize(node);
    }
    UpdateSize(node);
    UpdateHeight(node);
    return node;
  };

  Branch<KeyType, ValueType> *RotateLeft(Branch<KeyType, ValueType> *node) {
    Branch<KeyType, ValueType> *newRoot = node->right_;
    node->right_ = newRoot->left_;
    if (newRoot->left_) {
      newRoot->left_->parent_ = node;
    }
    newRoot->left_ = node;
    newRoot->parent_ = node->parent_;
    node->parent_ = newRoot;
    UpdateHeight(newRoot);
    UpdateHeight(node);
    return newRoot;
  };

  Branch<KeyType, ValueType> *RotateRight(Branch<KeyType, ValueType> *node) {
    Branch<KeyType, ValueType> *newRoot = node->left_;
    node->left_ = newRoot->right_;
    if (newRoot->right_) {
      newRoot->right_->parent_ = node;
    }
    newRoot->right_ = node;
    newRoot->parent_ = node->parent_;
    node->parent_ = newRoot;
    UpdateHeight(newRoot);
    UpdateHeight(node);
    return newRoot;
  };

  Branch<KeyType, ValueType> *RemoveMin(Branch<KeyType, ValueType> *node) {
    if (!node->left_) return node->right_;
    node->left_ = RemoveMin(node->left_);
    return Balance(node);
  };

  Branch<KeyType, ValueType> *CopyTree(Branch<KeyType, ValueType> *node) {
    if (node == nullptr) {
      return nullptr;
    }
    Branch<KeyType, ValueType> *new_node =
        new Branch<KeyType, ValueType>(node->key_, node->value_);
    new_node->size_ = node->size_;
    new_node->left_ = CopyTree(node->left_);
    new_node->right_ = CopyTree(node->right_);
    new_node->parent_ = node->parent_;
    return new_node;
  }
  Branch<KeyType, ValueType> *FindMin(Branch<KeyType, ValueType> *node) {
    if (node == nullptr || node->left_ == nullptr) {
      return node;
    };
    return FindMin(node->left_);
  };

  Branch<KeyType, ValueType> *Remove(Branch<KeyType, ValueType> *node,
                                     KeyType key) {
    if (!node) return nullptr;
    if (key < node->key_) {
      node->left_ = Remove(node->left_, key);
    } else if (key > node->key_) {
      node->right_ = Remove(node->right_, key);
    } else {
      if (node->left_ == nullptr && node->right_ == nullptr) {
        node->~Branch();
        return nullptr;
      } else if (node->left_ == nullptr) {
        Branch<KeyType, ValueType> *temp = node->right_;
        delete node;
        return temp;
      } else if (node->right_ == nullptr) {
        Branch<KeyType, ValueType> *temp = node->left_;
        delete node;
        return temp;
      }
      Branch<KeyType, ValueType> *temp = FindMin(node->right_);
      node->key_ = temp->key_;
      node->value_ = temp->value_;
      node->right_ = Remove(node->right_, temp->key_);
    };
    return Balance(node);
  }

  Branch<KeyType, ValueType> *Insert(Branch<KeyType, ValueType> *node,
                                     KeyType key, ValueType value,
                                     Branch<KeyType, ValueType> *parent) {
    this->inserted = false;
    if (!node) {
      node = new Branch<KeyType, ValueType>(key, value);
      node->parent_ = parent;
      this->inserted = true;
      return Balance(node);
    }
    if (key < node->key_) {
      node->left_ = Insert(node->left_, key, value, node);
    } else if (key > node->key_) {
      node->right_ = Insert(node->right_, key, value, node);
    } else if (key == node->key_) {
      if (repeate_) {
        if (node->left_ != nullptr) {
          node->right_ = Insert(node->right_, key, value, node);
        } else {
          node->left_ = Insert(node->left_, key, value, node);
        }
      }
    }
    return Balance(node);
  };
};

}  // namespace s21
#endif  // CPP2_SRC_CONTAINERS_SRC_MAPSET_S21_AVL_TREE_H_
