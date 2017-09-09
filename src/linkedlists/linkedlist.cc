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
    Node<T>* new_head = head_->next;
    size_--;
    return head_->value;
  } else {
    throw "Cannot pop an empty list!";
  }
}

template <class T>
void LinkedList<T>::Push(T value) {
  Node<T>* new_head;
  new_head->value = value;

  if (head_ != NULL) {
    head_->next = new_head;
  } else {
    head_ = new_head;
  }
  size_++;
}

template <class T>
int LinkedList<T>::Size() {
  return size_;
}
}
