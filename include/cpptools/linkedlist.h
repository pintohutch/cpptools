/** \file linkedlist.h
 * Basic linked list class template and methods.
 *
 * Copyright 2017 Daniel Clark
 */

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

#include <stddef.h>
#include <algorithm>

namespace cpptools {

/**
 * An implementation of a doubly linked list using templates to handle
 * generic data types. This class also uses sentinel nodes as empty head
 * and tail markers to remove special case handling in the methods.
 *
 * ||--|------|-->|---|-->|---|-->|------|
 *     | head |   | a |   | b |   | tail |
 *     |------|<--|---|<--|---|<--|------|--||
 */
template <typename T>
class LinkedList {
  public:
    LinkedList() {
      init();
    }
    // Explicit guards against implicit type conversions.
    // Also can take zero parameters due to default parameter.
    //explicit LinkedList(const T& d = T()) {
    //  init();
    //}
    // Big Five
    // Overwriting defaults is necessary when data types are pointers.
    // Destructor
    ~LinkedList();
    // Copy constructor (lvalue const reference)
    LinkedList(const LinkedList& rhs) : size_(rhs.size_) {
      // Invoke LinkedNode's copy constructor.
    }
    // Move constructor (rvalue reference)
    //LinkedList(LinkedList&& rhs);
    // Copy assignment (lvalue const reference)
    //LinkedList& operator= (const LinkedList& rhs);
    // Move assignment (rvalue reference)
    //LinkedList& operator= (LinkedList&& rhs);

    // const keyword specifies accessor method - non-mutating.
    int size() const {
      return size_;
    }

    // const keyword specifies accessor method - non-mutating.
    bool empty() const {
      return size() == 0;
    }

  private:
    void init() {
      size_ = 0;
      head_ = new Node;
      tail_ = new Node;
      head_->next = tail_;
      tail_->prev = head_;
    }

    struct Node {
        T data;
        Node* prev;
        Node* next;

        // lvalue constructor.
        Node(const T& d = T{}, Node* p = nullptr, Node* n = nullptr) :
                data{d}, prev{p}, next{n} {}
        // rvalue constructor.
        Node(T&& d, Node* p = nullptr, Node* n = nullptr) :
                data{ std::move(d) }, prev{p}, next{n} {}
    };

    Node* head_;
    Node* tail_;
    int size_;
};

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

}

#endif //CPPTOOLS_LINKEDLIST_H_
