// linkedlist.h
//
// Author: Daniel Clark

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

// Includes
#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node {
  T value;
  Node<T>* next;
};

template <class T>
class LinkedList {
  private:
    Node<T>* head; // Pop() would return.
    int list_length;

  public:
    // Default constructor - creates head node
    LinkedList();

    T Pop();
    void Push(T value);
};

#endif //CPPTOOLS_LINKEDLIST_H
