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

struct Node
{
    string song;
    string artist;
    int play_count;
    Node * next;
};


class LinkedList
{
private:
    Node * head;
    int list_length;

public:
    // Default constructor - creates head node
    LinkedList();

    // Insert node function
    bool insert_node(Node * new_node, int index);
};

#endif //CPPTOOLS_LINKEDLIST_H
