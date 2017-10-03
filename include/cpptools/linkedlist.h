// linkedlist.h
//
// Author: Daniel Clark

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

#include <stddef.h>
#include <iostream>

namespace cpptools {

template <typename T>
class LinkedList {
  public:
    // Default constructor - creates head node
    LinkedList();

    T Pop();
    void Push(T value);
    int Size();

  private:
    struct Node {
      T value;
      Node* next;
      Node(const T& val, Node* nextNode) : value(val), next(nextNode) {}
    };
    Node* head_;
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
    Node* new_head = head_;
    head_ = head_->next;
    T val = new_head->value;
    delete new_head;
    size_--;
    return val;
  } else {
    throw "Cannot pop an empty list!";
  }
}

template <typename T>
void LinkedList<T>::Push(T value) {
  head_ = new Node(value, head_);
  size_++;
}

template <typename T>
int LinkedList<T>::Size() {
  return size_;
}
}

#endif //CPPTOOLS_LINKEDLIST_H
