// linkedlist.h
//
// Author: Daniel Clark

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

#include <stddef.h>

namespace cpptools {
template <typename T>
struct Node {
  T value;
  Node<T>* next;
};

template <typename T>
class LinkedList {
  public:
    // Default constructor - creates head node
    LinkedList();

    T Pop();
    void Push(T value);
    int Size();

  private:
    Node<T>* head_;
    int size_;
};

template <typename T>
LinkedList<T>::LinkedList() {
  head_ = NULL;
  size_ = 0;
}

template <typename T>
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

template <typename T>
void LinkedList<T>::Push(T value) {
  Node<T>* new_head = new Node<T>;//{T, head_};
  new_head->value = value;
  new_head->next = head_;
  head_ = new_head;
  delete new_head;
  size_++;
}

template <typename T>
int LinkedList<T>::Size() {
  return size_;
}
}

#endif //CPPTOOLS_LINKEDLIST_H
