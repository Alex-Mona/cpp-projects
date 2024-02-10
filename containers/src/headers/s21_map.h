#ifndef S21_CONTAINERS_HEADERS_S21_MAP_H_
#define S21_CONTAINERS_HEADERS_S21_MAP_H_

#include <iostream>

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class T, class Compare = s21::PairComp<Key, T>>
class Map : public BinaryTree<std::pair<Key, T>, Compare> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using key_compare = Compare;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<value_type, key_compare>::Iterator;
  using const_iterator =
      typename BinaryTree<value_type, key_compare>::ConstIterator;
  using size_type = size_t;
  using tree_node = typename BinaryTree<value_type, Compare>::Node;

  Map() {
    this->end_nil_ = new tree_node(value_type(0, 0));
    this->begin_nil_ =
        new tree_node(value_type(0, 0), nullptr, nullptr, this->end_nil_);
    this->end_nil_->parent_ = this->begin_nil_;
  };

  Map(std::initializer_list<value_type> const &items) : Map() {
    for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
  };

  Map(const Map &other) : Map() {
    for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
  };

  Map(Map &&other) : Map() { this->swap(other); };

  ~Map() {
    this->clear();
    delete this->end_nil_;
    delete this->begin_nil_;
  };

  Map &operator=(Map &&other) {
    this->clear();
    this->swap(other);
    return *this;
  };

  Map &operator=(const Map &other) {
    for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
    return *this;
  };

  T &operator[](const Key &key) {
    auto it = this->begin();
    while ((*it).first != key && it != this->end()) ++it;
    if (it == this->end()) {
      auto pair = this->insert(key, 0);
      it = pair.first;
    }
    return (*it).second;
  };

  T &at(const Key &key) {
    auto it = this->begin();
    if (this->contains(key)) {
      while ((*it).first != key) ++it;
    } else {
      throw std::out_of_range("s21::map::at");
    }
    return (*it).second;
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->InsertOrPaste(value);
  };

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    value_type tmp(key, obj);
    std::pair<iterator, bool> answer = this->InsertOrPaste(tmp);
    return answer;
  };

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    value_type tmp(key, obj);
    std::pair<iterator, bool> answer = this->InsertOrPaste(tmp);
    if (!answer.second) (*answer.first).second = obj;
    return answer;
  };

  void merge(Map &other) {
    auto it = other.begin();
    while (it != other.end()) {
      auto tmp = it + 1;
      if (!this->contains((*it).first)) {
        other.DeleteOrExtract(it, false);
        this->InsertOrPaste(*it, it.node());
      }
      it = tmp;
    }
  };

  bool contains(const Key &key) {
    bool answer = true;
    auto it = this->begin();
    while ((*it).first != key && it != this->end()) ++it;
    if (it == this->end()) answer = false;
    return answer;
  };
};
}  // namespace s21

#endif  // S21_CONTAINERS_HEADERS_S21_MAP_H_
