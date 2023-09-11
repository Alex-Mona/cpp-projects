#include "s21_map.h"

using namespace s21;

template <class K, class T>
Map<K, T>::Map() {
  root_ = &end_;
}

template <class K, class T>
Map<K, T>::~Map() {
}
// Поиск ноды по ключу - find
template <class K, class T>
std::pair<typename Map<K, T>::Node*, bool> Map<K, T>::find(key_type Key) {
  Node *root = root_;
  bool check = true;
  while (root->value_.first != Key && check) {
    if (root->value_.first < Key) {
      if (root->right_ != nullptr) {
        root = root->right_;
      } else {
        check = false;
      }
    } else {
      if (root->left_ != nullptr) {
        root = root->left_;
      } else {
        check = false;
      }
    }
  }
  return std::make_pair(root, check);
}
// Вставка - insert
template <class K, class T>
std::pair<typename Map<K, T>::Node*, bool> Map<K, T>::insert(const value_type& value) {
  auto tp = find(value.first);
  if (!tp.second) {
    if (tp.first->value_.first > value.first) {
      tp.first->left_ = new Node(value, tp.first);
      tp.first = tp.first->left_;
    } else {
      tp.first->right_ = new Node(value, tp.first);
      tp.first = tp.first->right_;
    }
  }
  tp.second = !tp.second;
  return tp;
}

template <class K, class T>
std::pair<typename Map<K, T>::Node*, bool> Map<K, T>::insert(const K& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}