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

struct node
{
    string song;
    string artist;
    int play_count;
    node * next;
};

#endif //CPPTOOLS_LINKEDLIST_H
