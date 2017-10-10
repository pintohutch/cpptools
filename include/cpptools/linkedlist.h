/** \file linkedlist.h
 * Basic linked list class template and methods.
 *
 * Author: Daniel Clark
 */

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

#include <stddef.h>
#include <iostream>

namespace cpptools {

/**
 * An implementation of a doubly linked list using templates to handle
 * generic data types.
 */
template <typename T>
class LinkedList {
  public:
    // Default constructor - creates head node
    LinkedList();
    // Destructor
    ~LinkedList();

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

/**
 * Default constructor with no arguments.
 */
template <typename T>
LinkedList<T>::LinkedList()
    : head_(NULL), size_(0) {}

/**
 * Default destructor - uses Pop() method to clear up heap space.
 */
template <typename T>
LinkedList<T>::~LinkedList() {
  while (head_) {
    Pop();
  }
}

/**
 * Method to to return the current head of the list while also removing
 * its reference from the structure.
 * @return the value of type T at list's current head.
 */
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
