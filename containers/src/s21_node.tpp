#include "s21_map.h"

using namespace s21;

template <class K, class T>
Map<K, T>::Node::Node() : value_(std::make_pair(K(), T())), parent_(nullptr), left_(nullptr), right_(nullptr) { ; }
//Копирует значения создавая новую ноду
template <class K, class T>
Map<K, T>::Node::Node(const Node &other) : Node() {
  value_.first = other.value_.first;
  value_.second = other.value_.second;
  parent_ = other.parent_;
  left_ = other.left_;
  right_ = other.right_;
}
// Создает новую ноду перенеся данные из другой(other)
template <class K, class T>
Map<K, T>::Node::Node(Node &&other) {
  value_.first = other.value_.first;
  value_.second = other.value_.second;
  parent_ = other.parent_;
  left_ = other.left_;
  right_ = other.right_;
}
// Создает новую ноду по переданным значениям
template <class K, class T>
Map<K, T>::Node::Node(const std::pair<K, T> &value, const Node *parent, const Node *left, const Node *right) {
  value_ = value;
  parent_ = parent;
  left_ = left;
  right_ = right;
}
