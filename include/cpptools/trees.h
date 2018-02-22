/** \file trees.h
 * Various tree implementations.
 *
 *
 * Copyright 2018 Daniel Clark
 */

#ifndef CPPTOOLS_TREES_H
#define CPPTOOLS_TREES_H

#include <algorithm>

namespace cpptools {

template <typename T>
class BinarySearchTree {

  private:
    void dup(const BinarySearchTree& bst) const {
      if (bst.left_ != nullptr) {
        bst.dup(*bst.left_);
      }
      if (bst.right_ != nullptr) {
        bst.dup(*bst.right_);
      }
      // Copy constructor
      data_ = T{bst.data_};
    }

  public:
    explicit BinarySearchTree(const T& d = T{}, BinarySearchTree* l = nullptr,
      BinarySearchTree* r = nullptr) : data_{d}, left_{l}, right_{r} {}

    explicit BinarySearchTree(const T&& d = T{}, BinarySearchTree* l = nullptr,
      BinarySearchTree* r = nullptr) : data_{std::move(d)}, left_{l}, right_{r} {}

    // Destructor
    //~BinarySearchTree();
    // Copy Constructor.
    BinarySearchTree(const BinarySearchTree& bst) {
      dup(bst);
    }
    // Copy assignment.
    //BinarySearchTree(BinarySearchTree&& bst);
    // Move constructor.
    //BinarySearchTree& operator= (const BinarySearchTree& bst);
    // Move assignment.
    //BinarySearchTree& operator= (BinarySearchTree&& bst);

    const T& data() {
      return data_;
    }

  private:
    BinarySearchTree* left_;
    BinarySearchTree* right_;
    T data_;
};

}

#endif //CPPTOOLS_TREES_H
