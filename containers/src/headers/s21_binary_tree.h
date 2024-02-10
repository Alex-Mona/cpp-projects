#ifndef S21_CONTAINERS_HEADERS_S21_BINARY_TREE_H_
#define S21_CONTAINERS_HEADERS_S21_BINARY_TREE_H_

#include <iostream>
#include <limits>
#include <utility>

#include "s21_comparators.h"

template <class Key, class Compare = s21::SingleComp<Key>>
class BinaryTree {
 public:
  using key_type = Key;
  using value_type = Key;
  using key_compare = Compare;
  using reference = key_type &;
  using const_reference = const key_type &;
  using size_type = size_t;

  struct Node {
    Node(key_type key, Node *right = nullptr, Node *left = nullptr,
         Node *parent = nullptr) {
      data_ = key;
      right_ = right;
      left_ = left;
      parent_ = parent;
    };
    ~Node(){};

    key_type data_;
    Node *left_;
    Node *right_;
    Node *parent_;
  };

  class Iterator {
   public:
    Iterator() : address_(nullptr){};
    Iterator(Node &node) : address_(&node){};
    Iterator(Node *node_ptr) : address_(node_ptr){};
    Iterator(const Iterator &other) : address_(other.address_){};
    Iterator(Iterator &&other) : address_(other.address_) {
      other.address_ = nullptr;
    };

    ~Iterator(){};
    Iterator &operator=(const Iterator &other) {
      this->address_ = other.address_;
      return *this;
    };

    Node *node() const { return address_; };

    value_type &operator*() const { return address_->data_; };

    Iterator &operator++() {
      if (this->address_->right_) {
        this->address_ = this->address_->right_;
        while (this->address_->left_) this->address_ = this->address_->left_;
      } else if (this->address_->parent_->left_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator.GreaterThan(tmp, this->address_->data_));
      }
      return *this;
    };

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++*this;
      return tmp;
    };

    Iterator &operator--() {
      if (this->address_->left_) {
        this->address_ = this->address_->left_;
        while (this->address_->right_) this->address_ = this->address_->right_;
      } else if (this->address_->parent_->right_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator.LessThan(tmp, this->address_->data_));
      }
      return *this;
    };

    Iterator operator--(int) {
      Iterator tmp = *this;
      --*this;
      return tmp;
    };

    Iterator operator+(int n) {
      Iterator tmp = *this;
      for (int i = 0; i < n; ++i) ++tmp;
      return tmp;
    };

    Iterator operator-(int n) {
      Iterator tmp = *this;
      for (int i = 0; i < n; ++i) --tmp;
      return tmp;
    };

    Iterator operator+=(int n) {
      for (int i = 0; i < n; ++i) ++*this;
      return *this;
    };

    Iterator operator-=(int n) {
      for (int i = 0; i < n; ++i) --*this;
      return *this;
    };

    bool operator==(const Iterator &other) {
      return address_ == other.address_;
    };

    bool operator!=(const Iterator &other) {
      return address_ != other.address_;
    };

   private:
    key_compare comparator;
    Node *address_;
  };

  class ConstIterator {
   public:
    ConstIterator() : address_(nullptr){};
    ConstIterator(Node &node) : address_(&node){};
    ConstIterator(Node *node_ptr) : address_(node_ptr){};
    ConstIterator(const ConstIterator &other) : address_(other.address_){};
    ConstIterator(ConstIterator &&other) : address_(other.address_) {
      other.address_ = nullptr;
    };
    ~ConstIterator(){};

    ConstIterator &operator=(const ConstIterator &other) {
      this->address_ = other.address_;
      return *this;
    };

    Node *node() const { return address_; };

    const_reference operator*() const { return address_->data_; };

    ConstIterator &operator++() {
      if (this->address_->right_) {
        this->address_ = this->address_->right_;
        while (this->address_->left_) this->address_ = this->address_->left_;
      } else if (this->address_->parent_->left_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator.GreaterThan(tmp, this->address_->data_));
      }
      return *this;
    };

    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++*this;
      return tmp;
    };

    ConstIterator &operator--() {
      if (this->address_->left_) {
        this->address_ = this->address_->left_;
        while (this->address_->right_) this->address_ = this->address_->right_;
      } else if (this->address_->parent_->right_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator.LessThan(tmp, this->address_->data_));
      }
      return *this;
    };

    ConstIterator operator--(int) {
      ConstIterator tmp = *this;
      --*this;
      return tmp;
    };

    ConstIterator operator+(int n) {
      ConstIterator tmp = *this;
      for (int i = 0; i < n; ++i) ++tmp;
      return tmp;
    };

    ConstIterator operator-(int n) {
      ConstIterator tmp = *this;
      for (int i = 0; i < n; ++i) --tmp;
      return tmp;
    };

    ConstIterator operator+=(int n) {
      for (int i = 0; i < n; ++i) ++*this;
      return *this;
    };

    ConstIterator operator-=(int n) {
      for (int i = 0; i < n; ++i) --*this;
      return *this;
    };

    bool operator==(const ConstIterator &other) {
      return address_ == other.address_;
    };

    bool operator!=(const ConstIterator &other) {
      return address_ != other.address_;
    };

   private:
    key_compare comparator;
    Node *address_;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  iterator begin() {
    iterator tmp(begin_nil_);
    if (size_) ++tmp;
    return tmp;
  };

  iterator end() { return iterator(end_nil_); };

  const_iterator cbegin() const {
    const_iterator tmp(begin_nil_);
    if (size_) ++tmp;
    return tmp;
  };

  const_iterator cend() const { return const_iterator(end_nil_); };

  bool empty() { return !(bool)size_; };

  size_type size() { return size_; };

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(Node));
  };

  void clear() {
    if (size_) {
      iterator it = begin();
      while (it != end()) {
        iterator tmp = it + 1;
        erase(it);
        it = tmp;
      }
    }
  };

  void erase(iterator pos) { DeleteOrExtract(pos, true); };

  void swap(BinaryTree &other) {
    Node *tmp_root = this->root_;
    Node *tmp_end_nil = this->end_nil_;
    Node *tmp_begin_nil = this->begin_nil_;
    size_type tmp = this->size_;
    this->root_ = other.root_;
    this->end_nil_ = other.end_nil_;
    this->begin_nil_ = other.begin_nil_;
    this->size_ = other.size_;
    other.root_ = tmp_root;
    other.end_nil_ = tmp_end_nil;
    other.begin_nil_ = tmp_begin_nil;
    other.size_ = tmp;
  };

 protected:
  size_type size_ = 0;
  Node *root_ = nullptr;
  Node *end_nil_;
  Node *begin_nil_;
  key_compare comparator;

  void ChangeParentsChild(Node *parent, Node *old_child, Node *new_child) {
    parent->left_ == old_child ? parent->left_ = new_child
                               : parent->right_ = new_child;
  };

  void DeleteOrExtract(iterator pos, bool del) {
    if (pos.node() && pos.node() != end_nil_ && pos.node() != begin_nil_) {
      key_type tmp = *pos;
      Node *node = root_;
      Node *parent = Search(tmp, node);

      if (IsLeaf(node)) {
        DeleteLeaf(node);
      } else if (Node *child = HasOneChild(node)) {
        DeleteWithChild(node, child);
      } else {
        if (node->left_ == begin_nil_ && node->right_ == end_nil_) {
          DeleteRoot();
        } else if (node->left_ != begin_nil_ && node->right_ != end_nil_) {
          DeleteWithWwo(node, parent);
        } else {
          if (node->left_ == begin_nil_) {
            DeleteWithNilInLeft(node, parent);
          } else {
            DeleteWithNilInRight(node, parent);
          }
        }
      }
      if (del) delete node;
      --size_;
    }
  };

  std::pair<iterator, bool> InsertOrPaste(const key_type &key,
                                          Node *node = nullptr) {
    Node *insertible = !node ? new Node(key) : node;
    std::pair<iterator, bool> pair(iterator(insertible), true);
    if (!root_) {
      root_ = insertible;
      insertible->right_ = end_nil_;
      insertible->left_ = begin_nil_;
      end_nil_->parent_ = insertible;
      begin_nil_->parent_ = insertible;
      end_nil_->right_ = end_nil_;
      begin_nil_->left_ = begin_nil_;
    } else {
      Node *tmp = root_;
      Node *parent = Search(key, tmp);
      if (tmp == end_nil_) {
        parent->right_ = insertible;
        insertible->parent_ = parent;
        insertible->left_ = nullptr;
        insertible->right_ = end_nil_;
        end_nil_->parent_ = insertible;
      } else if (tmp == begin_nil_) {
        parent->left_ = insertible;
        insertible->parent_ = parent;
        insertible->left_ = nullptr;
        insertible->left_ = begin_nil_;
        begin_nil_->parent_ = insertible;
      } else if (!tmp) {
        comparator.LessThan(key, parent->data_) ? parent->left_ = insertible
                                                : parent->right_ = insertible;
        insertible->parent_ = parent;
        insertible->left_ = insertible->right_ = nullptr;
      } else {
        pair.first = iterator(tmp);
        pair.second = false;
        if (!node) delete insertible;
      }
    }
    if (pair.second) ++size_;
    return pair;
  };

  void DeleteLeaf(Node *leaf) {
    ChangeParentsChild(leaf->parent_, leaf, nullptr);
  };

  void DeleteWithChild(Node *node, Node *child) {
    ChangeParentsChild(node->parent_, node, child);
    child->parent_ = node->parent_;
  };

  void DeleteRoot() {
    root_ = nullptr;
    begin_nil_->parent_ = end_nil_;
    end_nil_->parent_ = begin_nil_;
  };

  void DeleteWithWwo(Node *node, Node *parent) {
    Node *max_in_left = GetMax(node->left_);
    Node *parent_moved = max_in_left->parent_;
    if (parent_moved == node) {
      max_in_left->right_ = node->right_;
      node->right_->parent_ = max_in_left;
      max_in_left->parent_ = parent;
      if (parent) {
        ChangeParentsChild(parent, node, max_in_left);
      } else {
        root_ = max_in_left;
      }
    } else {
      parent_moved->right_ = max_in_left->left_;
      if (max_in_left->left_) parent_moved->right_->parent_ = parent_moved;
      max_in_left->left_ = node->left_;
      node->left_->parent_ = max_in_left;
      max_in_left->parent_ = parent;
      if (parent) {
        ChangeParentsChild(parent, node, max_in_left);
      } else {
        root_ = max_in_left;
      }
      max_in_left->right_ = node->right_;
      node->right_->parent_ = max_in_left;
    }
  };

  void DeleteWithNilInLeft(Node *node, Node *parent) {
    if (!node->right_->left_) {
      node->right_->parent_ = parent;
      if (parent) {
        ChangeParentsChild(parent, node, node->right_);
      } else {
        root_ = node->right_;
      }
      node->right_->left_ = begin_nil_;
      begin_nil_->parent_ = node->right_;
    } else {
      Node *min_in_right = GetMin(node->right_);
      Node *tmp = min_in_right->right_;
      Node *parent_moved = min_in_right->parent_;
      parent_moved->left_ = tmp;
      if (tmp) tmp->parent_ = parent_moved;
      min_in_right->parent_ = parent;
      if (parent) {
        ChangeParentsChild(parent, node, min_in_right);
      } else {
        root_ = min_in_right;
      }
      min_in_right->right_ = node->right_;
      node->right_->parent_ = min_in_right;
      begin_nil_->parent_ = min_in_right;
      min_in_right->left_ = begin_nil_;
    }
  };

  void DeleteWithNilInRight(Node *node, Node *parent) {
    if (!node->left_->right_) {
      node->left_->parent_ = parent;
      if (parent) {
        ChangeParentsChild(parent, node, node->left_);
      } else {
        root_ = node->left_;
      }
      node->left_->right_ = end_nil_;
      end_nil_->parent_ = node->left_;
    } else {
      Node *max_in_left = GetMax(node->left_);
      Node *tmp = max_in_left->left_;
      Node *parent_moved = max_in_left->parent_;
      parent_moved->right_ = tmp;
      if (tmp) tmp->parent_ = parent_moved;
      max_in_left->parent_ = parent;
      if (parent) {
        ChangeParentsChild(parent, node, max_in_left);
      } else {
        root_ = max_in_left;
      }
      max_in_left->left_ = node->left_;
      node->left_->parent_ = max_in_left;
      end_nil_->parent_ = max_in_left;
      max_in_left->right_ = end_nil_;
    }
  };

  Node *Search(const key_type &key, Node *&tmp_node) {
    Node *parent = nullptr;
    while (tmp_node != nullptr && tmp_node != end_nil_ &&
           comparator.NotEquals(key, tmp_node->data_) &&
           tmp_node != begin_nil_) {
      parent = tmp_node;
      if (comparator.LessThan(key, tmp_node->data_))
        tmp_node = tmp_node->left_;
      else if (comparator.GreaterThan(key, tmp_node->data_))
        tmp_node = tmp_node->right_;
    }
    return parent;
  };

  bool IsLeaf(Node *checked) {
    bool tmp = false;
    if (checked->left_ == nullptr && checked->right_ == nullptr) tmp = true;
    return tmp;
  };

  Node *HasOneChild(Node *checked) {
    Node *tmp = nullptr;
    if (checked->left_ && !checked->right_) tmp = checked->left_;
    if (!checked->left_ && checked->right_) tmp = checked->right_;
    return tmp;
  };

  Node *GetMax(Node *starting) {
    return starting->right_ == nullptr ? starting : GetMax(starting->right_);
  };

  Node *GetMin(Node *starting) {
    return starting->left_ == nullptr ? starting : GetMax(starting->left_);
  };
};

#endif  //  S21_CONTAINERS_HEADERS_S21_BINARY_TREE_H_
