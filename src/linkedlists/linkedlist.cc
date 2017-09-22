// linkedlist.cpp provides the linkedlist implementation.

// Headers
#include <stddef.h>
#include "cpptools/linkedlist.h"

namespace cpptools {
template <class T>
LinkedList<T>::LinkedList() {
  head_ = NULL;
  size_ = 0;
}

template <class T>
T LinkedList<T>::Pop() {
  if (head_ != NULL) {
    T val = head_->value;
    head_ = head_->next;
    size_--;
    return val;
  } else {
    throw "Cannot pop an empty list!";
  }
}

template <class T>
void LinkedList<T>::Push(T value) {
  Node<T>* new_head = new Node<T>;//{T, head_};
  new_head->value = value;
  new_head->next = head_;
  head_ = new_head;
  size_++;
}

template <class T>
int LinkedList<T>::Size() {
  return size_;
}
template class LinkedList<int>;
}
