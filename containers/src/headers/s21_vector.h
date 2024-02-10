#ifndef S21_CONTAINERS_HEADERS_S21_VECTOR_H_
#define S21_CONTAINERS_HEADERS_S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  class VectorIterator {
   public:
    VectorIterator(value_type *ref) { array_ptr_ = ref; };
    reference &operator*() { return *array_ptr_; };

    VectorIterator &operator++() { return ++array_ptr_; };
    VectorIterator operator++(int) {
      VectorIterator tmp = array_ptr_;
      ++array_ptr_;
      return tmp;
    };

    VectorIterator &operator--() { return --array_ptr_; };
    VectorIterator operator--(int) {
      VectorIterator tmp = array_ptr_;
      --array_ptr_;
      return tmp;
    };

    VectorIterator operator+(int n) { return array_ptr_ + n; };
    VectorIterator operator-(int n) { return array_ptr_ - n; };

    VectorIterator operator+=(int n) { return array_ptr_ += n; };
    VectorIterator operator-=(int n) { return array_ptr_ -= n; };

    bool operator==(const VectorIterator it) {
      return array_ptr_ == it.array_ptr_;
    };
    bool operator!=(const VectorIterator it) {
      return array_ptr_ != it.array_ptr_;
    };

   private:
    value_type *array_ptr_;
  };

  class VectorConstIterator {
   public:
    VectorConstIterator(value_type *ref) { array_ptr_ = ref; };
    const value_type &operator*() const { return *array_ptr_; };

    VectorConstIterator operator++() { return ++array_ptr_; };
    VectorConstIterator operator++(int) {
      VectorConstIterator tmp = array_ptr_;
      ++array_ptr_;
      return tmp;
    };

    VectorConstIterator operator--() { return --array_ptr_; };
    VectorConstIterator operator--(int) {
      VectorConstIterator tmp = array_ptr_;
      --array_ptr_;
      return tmp;
    };

    VectorConstIterator operator+(int n) { return array_ptr_ + n; };
    VectorConstIterator operator-(int n) { return array_ptr_ - n; };

    VectorConstIterator operator+=(int n) { return array_ptr_ += n; };
    VectorConstIterator operator-=(int n) { return array_ptr_ -= n; };

    bool operator==(const VectorConstIterator &it) {
      return array_ptr_ == it.array_ptr_;
    };
    bool operator!=(const VectorConstIterator &it) {
      return array_ptr_ != it.array_ptr_;
    };

   private:
    value_type *array_ptr_;
  };

  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;
  using size_type = size_t;
  Vector() : size_(0), capacity_(0), arr_(nullptr){};

  Vector(size_type n) : size_(n), capacity_(n) {
    if (n == 0) {
      arr_ = nullptr;
    } else {
      arr_ = new value_type[n];
      for (size_type i = 0; i < size_; i++) {
        arr_[i] = 0;
      }
    }
  };

  Vector(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    arr_ = new value_type[size_];
    std::copy(items.begin(), items.end(), arr_);
  };

  Vector(const Vector &v)
      : size_(v.size_), capacity_(v.capacity_), arr_(new value_type[size_]) {
    const_iterator it = v.cbegin();
    int counter = 0;
    while (it != v.cend()) {
      arr_[counter] = *it;
      ++counter;
      ++it;
    }
  };

  Vector(Vector &&v) : size_(v.size()), capacity_(v.capacity()), arr_(v.arr_) {
    v.size_ = v.capacity_ = 0;
    v.arr_ = nullptr;
  };

  ~Vector() {
    size_ = capacity_ = 0;
    if (arr_ != nullptr) {
      delete[] arr_;
      arr_ = nullptr;
    }
  };

  Vector &operator=(const Vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    delete[] this->arr_;
    arr_ = new value_type[capacity_];
    const_iterator source_it = v.cbegin();
    iterator dest_it = this->begin();
    while (source_it != v.cend()) {
      *dest_it = *source_it;
      source_it++;
      dest_it++;
    }
    return *this;
  };

  reference at(size_type pos) {
    if (pos >= this->size())
      throw std::out_of_range("at(): invalid input, index out of bounds");
    return arr_[pos];
  };

  reference operator[](size_type pos) { return arr_[pos]; };

  const_reference operator[](size_type pos) const { return arr_[pos]; };

  const_reference front() {
    const value_type &const_ref = arr_[0];
    return const_ref;
  };

  const_reference back() {
    const value_type &const_ref = arr_[size_ - 1];
    return const_ref;
  };

  T *data() { return arr_; };

  const_iterator cbegin() const { return const_iterator(arr_); };

  const_iterator cend() const { return const_iterator(arr_ + size_); };

  iterator begin() { return iterator(arr_); };

  iterator end() { return iterator(arr_ + size_); };

  bool empty() { return !(bool)size_; };

  size_type size() { return size_; };

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(value_type));
  };

  void reserve(size_type size) {
    if (size > capacity_) {
      int counter = 0;
      capacity_ = size;
      value_type *tmp = new value_type[capacity_];
      Vector<value_type>::iterator it = this->begin();
      while (it != this->end()) {
        tmp[counter] = *it;
        counter++;
        it++;
      }
      delete[] arr_;
      arr_ = tmp;
    }
  };

  size_type capacity() { return capacity_; };

  void shrink_to_fit() {
    int counter = 0;
    capacity_ = this->size();
    value_type *tmp = new value_type[capacity_];
    iterator it = this->begin();
    while (it != this->end()) {
      tmp[counter] = *it;
      counter++;
      it++;
    }
    delete[] arr_;
    arr_ = tmp;
  };

  void clear() {
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = '\0';
    }
    size_ = 0;
  };

  iterator insert(iterator pos, const_reference value) {
    int counter = 0;
    for (iterator it = this->end(); it != pos; it--) {
      counter++;
    }
    if (size_ == capacity_) {
      this->reserve(this->size_ * 2);
    }
    iterator it = this->end();
    iterator it_2 = it - 1;
    for (int i = 0; i != counter; i++) {
      *it = *it_2;
      it--;
      it_2--;
    }
    *it = value;
    iterator returnable = it;
    size_++;
    return returnable;
  };

  void erase(iterator pos) {
    iterator it = pos;
    iterator it_2 = pos + 1;
    while (it_2 != this->end()) {
      *it = *it_2;
      it++;
      it_2++;
    }
    *it = '\0';
    size_--;
  };

  void push_back(const_reference value) { this->insert(this->end(), value); };

  void pop_back() { this->erase(this->end() - 1); };

  void swap(Vector &other) {
    value_type *tmp = other.data();

    int size = other.size();
    int capacity = other.capacity();

    other.arr_ = this->data();
    other.size_ = this->size();
    other.capacity_ = this->capacity();

    this->arr_ = tmp;
    this->size_ = size;
    this->capacity_ = capacity;
  };

 private:
  size_type size_, capacity_;
  value_type *arr_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_HEADERS_S21_VECTOR_H_
