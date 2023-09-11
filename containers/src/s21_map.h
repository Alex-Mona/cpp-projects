#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <iostream>

// Дописать Insert - смещение begin налево, end направо
// Фейковый метод begin - возвращает родителя фейковой ноды begin
// class MapIterator & ConstMapIterator

namespace s21 {
class Node;
class Iterator;

template <typename K, typename T>
class Map {
  public:
    class Node;
    class Iterator;
    using key_type = K;
    using mapped_type = T;
    using value_type = std::pair<key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const reference;
    using node = Node;
    // using iterator = 
    // using const_iterator
    using size_type = size_t;
  Map();
  ~Map();
  std::pair<Node*, bool> insert(const value_type& value);
  std::pair<Node*, bool> insert(const K& key, const T& obj);
  
  private:
    node begin_;
    node end_;
    node *root_;
    std::pair<Node*, bool> find(key_type Key);
};

template <typename K, typename T> class Map<K, T>::Node {
  friend class Map;
  private:
  Node();
  Node(const Node &other);
  Node(Node &&other);
  Node(const std::pair<K, T> &value, const Node *parent = nullptr, const Node *left = nullptr, const Node *right = nullptr);

  std::pair<K, T> value_;
  Node* parent_;
  Node* left_;
  Node* right_;
};

template <typename Key, typename T> class Map<Key, T>::Iterator {
protected:
  Node *iterator_;

public:
  Iterator(Node *node) : iterator_(node) {}
  bool operator==(const Iterator &it);
  bool operator!=(const Iterator &it);
  Node *operator++();
  Node *operator++(int);
  Node *operator--();
  Node *operator--(int);
  Node *operator+=(int n);
  Node *operator-=(int n);

private:
  Node *NextNode_(Node *node);
  Node *PreviousNode_(Node *node);
  Node *MinNode_(Node *node);
  Node *MaxNode_(Node *node);
};

};

#include "s21_map.tpp"
#include "s21_node.tpp"
#include "s21_iterator.tpp"
#endif // SRC_S21_MAP_H_