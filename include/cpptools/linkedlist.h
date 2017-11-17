/** \file linkedlist.h
 * Basic linked list class template and methods.
 *
 * Copyright 2017 Daniel Clark
 */

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

#include <stddef.h>
#include "linkednode.h"

namespace cpptools {

/**
 * An implementation of a doubly linked list using templates to handle
 * generic data types.
 */
template <typename T>
class LinkedList {
  public:
    // Parameter-less constructor
    LinkedList();
    // Explicit guards against implicit type conversions.
    explicit LinkedList(T value);
    // Big Five
    // Overwriting defaults is necessary when data types are pointers.
    // Destructor
    ~LinkedList();
    // Copy constructor (lvalue const reference)
    LinkedList(const LinkedList& rhs);
    // Move constructor (rvalue reference)
    //LinkedList(LinkedList&& rhs);
    // Copy assignment (lvalue const reference)
    //LinkedList& operator= (const LinkedList& rhs);
    // Move assignment (rvalue reference)
    //LinkedList& operator= (LinkedList&& rhs);

    T Pop();
    void Push(T value);
    int Size() const;

  private:
    LinkedNode<T>* head_;
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
LinkedList<T>::LinkedList(T value)
  : head_(NULL), size_(0) {
    Push(value);
}

/**
 * Default destructor - uses Pop() method to clear up heap space.
 */
template <typename T>
LinkedList<T>::~LinkedList() {
  while (head_) {
    Pop();
  }
  delete head_;
}

/**
 * Copy constructor
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) : size_(rhs.size_) {
  std::cout << "got invoked";
  // Invoke LinkedNode's copy constructor.
  LinkedNode<T> copy = *rhs.head_;
  head_ = &copy;
}

/**
 * Method to to return the current head of the list while also removing
 * its reference from the structure.
 * @return the value of type T at list's current head.
 */
template <typename T>
T LinkedList<T>::Pop() {
  if (head_ != NULL) {
    LinkedNode<T>* new_head = head_;
    head_ = head_->next_;
    T value = new_head->value_;

    size_--;
    return value;
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
  LinkedNode<T>* tmp = new LinkedNode<T>(value);
  tmp->next_ = head_;
  head_ = tmp;
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

#endif //CPPTOOLS_LINKEDLIST_H_
