/**
 * \file main.cc
 * Main file for project (for now).
 *
 * Copyright 2018 Daniel Clark
 */
#include "cpptools/linkedlist.h"

int main() {
  cpptools::LinkedList<int> l = cpptools::LinkedList<int>();
  return l.size();
}
