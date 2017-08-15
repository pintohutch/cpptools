// linkedlist.cpp
//
// Author: Daniel Clark

// Headers
#include <iostream>

#include "cpp-tools/linkedlist.h"

using namespace std;

template <class T>
LinkedList<T>::LinkedList() {
  head = NULL;
  list_length = 0;
}

template <class T>
T LinkedList<T>::Pop() {
  if (head != NULL) {
    Node<T>* new_head = head->next;
    list_length--;
    return head->value;
  } else {
    throw "Cannot pop an empty list!";
  }
}

template <class T>
void LinkedList<T>::Push(T value) {
  Node<T>* new_head;
  new_head->value = value;

  if (head != NULL) {
    head->next = new_head;
  } else {
    head = new_head;
  }
}
