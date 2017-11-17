/** \file linkednode.h
 * Basic linked list class template and methods.
 *
 * Copyright 2017 Daniel Clark
 */

// Define guard
#ifndef CPPTOOLS_LINKEDNODE_H_
#define CPPTOOLS_LINKEDNODE_H_

#include <stddef.h>
#include <iostream>

namespace cpptools {

/**
 * An implementation of a singly linked node using templates to handle
 * generic data types.
 */
template <typename T>
class LinkedNode {
  public:
    // Explicit guards against implicit type conversions.
    explicit LinkedNode(T value);
    // Big Five
    // Overwriting defaults is necessary when data types are pointers.
    // Destructor
    ~LinkedNode();
    // Copy constructor (lvalue const reference)
    LinkedNode(const LinkedNode& rhs);
    // Move constructor (rvalue reference)
    LinkedNode(LinkedNode&& rhs);
    // Copy assignment (lvalue const reference)
    LinkedNode& operator= (const LinkedNode& rhs);
    // Move assignment (rvalue reference)
    LinkedNode& operator= (LinkedNode&& rhs);

    T value_;
    LinkedNode* next_;
};

/**
 * Single-argument constructor.
 */
template <typename T>
LinkedNode<T>::LinkedNode(T val)
  : value_(val), next_(nullptr) {}

/**
 * Destructor - removes any references to it or any of its references.
 */
template <typename T>
LinkedNode<T>::~LinkedNode() {
  while (next_ != nullptr) {
    LinkedNode* new_next = next_;
    next_ = next_->next_;
    delete new_next;
  }
}

/**
 * Copy constructor
 */
template <typename T>
LinkedNode<T>::LinkedNode(const LinkedNode& rhs) : value_(rhs.value_) {
  if (rhs.next_ != nullptr) {
    next_ = new LinkedNode(rhs.next_->value_);
    LinkedNode* walk = next_;
    LinkedNode* shadow = rhs.next_;
    // Walk forward through nexts and copy.
    while (shadow != nullptr) {
      LinkedNode* tmp = new LinkedNode(shadow->value_);
      walk->next_ = tmp;
      walk = walk->next_;
      shadow = shadow->next_;
    }
  }
}

/**
 * Move constructor
 */
template <typename T>
LinkedNode<T>::LinkedNode(LinkedNode&& rhs) : value_(rhs.value_),
    next_(rhs.next_) {
  rhs.next_ = nullptr;
}

/**
 * Copy assignment operator
 */
template <typename T>
LinkedNode<T>& LinkedNode<T>::operator= (const LinkedNode& rhs) {
  LinkedNode copy = rhs;
  value_ = copy.value_;
  next_ = copy.next_;
  return *this;
}

/**
 * Move assignment operator
 */
template <typename T>
LinkedNode<T>& LinkedNode<T>::operator= (LinkedNode&& rhs) {
  std::swap(value_, rhs.value_);
  std::swap(next_, rhs.next_);
  return *this;
}

}

#endif //CPPTOOLS_LINKEDNODE_H_
