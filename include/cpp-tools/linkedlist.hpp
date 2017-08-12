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
struct Node
{
    T val;
    Node<T>* next;
};

template <class T>
class LinkedList
{
  private:
    Node* head;
    int list_length;

  public:
    // Default constructor - creates head node
    LinkedList();

    // Insert node function
    bool insert_node(int val, int index);
};

#endif //CPPTOOLS_LINKEDLIST_H
