#ifndef S21_CONTAINERS_HEADERS_S21_SET_H_
#define S21_CONTAINERS_HEADERS_S21_SET_H_

#include <iostream>

#include "s21_binary_tree.h"

namespace s21 {
template <typename Key, class Compare = s21::SingleComp<Key>>
class Set : public BinaryTree<Key, Compare> {
 public:
  using key_type = Key;
  using value_type = typename BinaryTree<Key>::value_type;
  using reference = typename BinaryTree<Key>::value_type &;
  using const_reference = const typename BinaryTree<Key>::value_type &;
  using size_type = size_t;
  using iterator = typename BinaryTree<Key>::Iterator;
  using const_iterator = typename BinaryTree<Key>::ConstIterator;
  using tree_node = typename BinaryTree<Key, Compare>::Node;

  Set() {
    this->end_nil_ = new tree_node(0);
    this->begin_nil_ = new tree_node(0, nullptr, nullptr, this->end_nil_);
    this->end_nil_->parent_ = this->begin_nil_;
  };

  Set(std::initializer_list<value_type> const &items) : Set() {
    for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
  };

  Set(const Set &other) : Set() {
    for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
  };

  Set(Set &&other) : Set() { this->swap(other); };

  ~Set() {
    this->clear();
    delete this->end_nil_;
    delete this->begin_nil_;
  };

  Set &operator=(Set &&other) {
    this->clear();
    this->swap(other);
    return *this;
  };

  Set &operator=(const Set &other) {
    this->clear();
    for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
    return *this;
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->InsertOrPaste(value);
  };

  void merge(Set &other) {
    auto it = other.begin();
    while (it != other.end()) {
      auto tmp = it + 1;
      if (!this->contains(*it)) {
        other.DeleteOrExtract(it, false);
        this->InsertOrPaste(*it, it.node());
      }
      it = tmp;
    }
  };

  iterator find(const Key &key) {
    auto it = this->end();
    if (this->contains(key)) {
      it = this->begin();
      while (*it != key) ++it;
    }
    return it;
  };

  bool contains(const Key &key) {
    tree_node *tmp = this->root_;
    bool answer = false;
    this->Search(key, tmp);
    if (tmp && tmp != this->end_nil_ && tmp != this->begin_nil_ &&
        tmp->data_ == key)
      answer = true;
    return answer;
  }
};
}  // namespace s21
#endif  // S21_CONTAINERS_HEADERS_S21_SET_H_
