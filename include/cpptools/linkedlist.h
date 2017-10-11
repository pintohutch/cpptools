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
    LinkedList();
    // Explicit guards against implicit type conversions.
    explicit LinkedList(T value);
    ~LinkedList();

    T Pop();
    void Push(T value);
    int Size() const;

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
 * Constructor with no arguments.
 */
template <typename T>
LinkedList<T>::LinkedList()
  : head_(NULL), size_(0) {}

/**
 * Single-argument constructor.
 */
template <typename T>
LinkedList<T>::LinkedList(T val)
  : head_(NULL), size_(0) {
    Push(val);
}

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

    size_--;
    return val;
  } else {
    throw "Cannot pop an empty list!";
  }
}

/**
 * Method to push a new value on top of the current head of the linked
 * list.
 */
template <typename T>
void LinkedList<T>::Push(T value) {
  head_ = new Node(value, head_);
  size_++;
}

/**
 * Method to return the number of nodes in the list.
 * const keyword specifies accessor method - non-mutating.
 */
template <typename T>
int LinkedList<T>::Size() const {
  return size_;
}
}

#endif //CPPTOOLS_LINKEDLIST_H
