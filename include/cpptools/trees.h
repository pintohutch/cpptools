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
    // Passing by reference vs pointer:
    // Reference: http://cplusplus.com/articles/z6vU7k9E
    // 1) Pass by value when the function does not want to modify the parameter
    //    and the value is easy to copy (ints, doubles, char, bool, etc).
    // 2) Pass by const pointer when the value is expensive to copy AND
    //    the function does not want to modify the value pointed to AND
    //    NULL is a valid, expected value that the function handles.
    // 3) Pass by non-const pointer when the value is expensive to copy AND
    //    the function wants to modify the value pointed to AND
    //    NULL is a valid, expected value that the function handles.
    // 4) Pass by const reference when the value is expensive to copy AND
    //    the function does not want to modify the value referred to AND
    //    NULL would not be a valid value if a pointer was used instead.
    // 5) Pass by non-const reference when the value is expensive to copy AND
    //    the function wants to modify the value referred to AND
    //    NULL would not be a valid value if a pointer was used instead.
    // 6) When writing template functions, there isn't a clear-cut answer
    //    because there are a few trade-offs to consider that are beyond the
    //    scope of this discussion, but suffice to say that most template
    //    functions take their parameters by value or (const) reference.
    //
    void dup(const BinarySearchTree& bst, BinarySearchTree& itr) {
      if (bst.left_ != nullptr) {
        itr.left_ = new BinarySearchTree{bst.left_->data_};
        dup(*bst.left_, *itr.left_);
      }
      if (bst.right_ != nullptr) {
        itr.right_ = new BinarySearchTree{bst.right_->data_};
        dup(*bst.right_, *itr.right_);
      }
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
      BinarySearchTree itr = BinarySearchTree{bst.data_};
      dup(bst, itr);
      data_ = itr.data_;
      left_ = itr.left_;
      right_ = itr.right_;
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
    const BinarySearchTree* left() {
      return left_;
    }
    const BinarySearchTree* right() {
      return right_;
    }

    void insert(const T& d) {

    }

    void insert(const T&& d) {
    }

  private:
    BinarySearchTree* left_;
    BinarySearchTree* right_;
    T data_;
};

}

#endif //CPPTOOLS_TREES_H
