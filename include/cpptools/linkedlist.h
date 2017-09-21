// linkedlist.h
//
// Author: Daniel Clark

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

namespace cpptools {
template <class T>
struct Node {
  T value;
  Node<T>* next;
};

template <class T>
class LinkedList {
  private:
    Node<T>* head_; // Pop() would return.
    int size_;

  public:
    // Default constructor - creates head node
    LinkedList();

    T Pop();
    void Push(T value);
    int Size();
};
}

#endif //CPPTOOLS_LINKEDLIST_H
