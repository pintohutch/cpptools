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
    explicit LinkedNode(const T& value = T())
     : value_(value), next_(nullptr) {
      std::cout << "constructor called\n";
     }
    // Big Five
    // Overwriting defaults is necessary when data types are pointers.
    // Destructor
    ~LinkedNode() {
      std::cout << "destructor called\n";
      while (next_ != nullptr) {
        LinkedNode* new_next = next_;
        next_ = next_->next_;
        delete new_next;
      }
    }
    // Copy constructor (lvalue const reference)
    LinkedNode(const LinkedNode& rhs) : value_(rhs.value_) {
      std::cout << "node copy constructor invoked\n";
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
    // Move constructor (rvalue reference)
    LinkedNode(LinkedNode&& rhs) : value_(rhs.value_), next_(rhs.next_) {
      std::cout << "node move constructor invoked\n";
      rhs.next_ = nullptr;
    }
    // Copy assignment (lvalue const reference)
    LinkedNode& operator= (const LinkedNode& rhs) {
      std::cout << "node copy assign invoked\n";
      LinkedNode copy = rhs;
      value_ = copy.value_;
      next_ = copy.next_;
      return *this;
    }
    // Move assignment (rvalue reference)
    LinkedNode& operator= (LinkedNode&& rhs) {
      std::cout << "node move assign invoked\n";
      std::swap(value_, rhs.value_);
      std::swap(next_, rhs.next_);
      return *this;
    }

    T value_;
    LinkedNode* next_;
};

}

#endif //CPPTOOLS_LINKEDNODE_H_
