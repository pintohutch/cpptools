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
    BinarySearchTree* left_;
    BinarySearchTree* right_;
    T data_;
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
    static BinarySearchTree* duplicate(const BinarySearchTree* root) {
      if (root == nullptr) {
        return nullptr;
      }
      auto dup = new BinarySearchTree{root->data_};
      if (root->left_ != nullptr) {
        dup->left_ = duplicate(root->left_);
      }
      if (root->right_ != nullptr) {
        dup->right_ = duplicate(root->right_);
      }
      return dup;
    }
    void _insert(const T& d) {
      if (d < data_) {
        if (left_ != nullptr) {
          left_->_insert(d);
        } else {
          left_ = new BinarySearchTree{d};
        }
      } else {
        if (right_ != nullptr) {
          right_ ->_insert(d);
        } else {
          right_ = new BinarySearchTree{d};
        }
      }
    }

  public:
    explicit BinarySearchTree(const T& d, BinarySearchTree* l = nullptr,
      BinarySearchTree* r = nullptr) : data_{d}, left_{l}, right_{r} {}

    explicit BinarySearchTree(const T&& d, BinarySearchTree* l = nullptr,
      BinarySearchTree* r = nullptr) : data_{std::move(d)}, left_{l}, right_{r} {}

    // Destructor
    //~BinarySearchTree();

    // Copy Constructor.
    BinarySearchTree(const BinarySearchTree& bst) {
      BinarySearchTree* dup = duplicate(&bst);
      data_ = dup->data_;
      left_ = dup->left_;
      right_ = dup->right_;
    }

    // Move constructor.
    BinarySearchTree(BinarySearchTree&& bst) noexcept :
      data_{bst.data_}, left_{bst.left_}, right_{bst.right_} {
      bst.data_ = T{};
      bst.left_ = nullptr;
      bst.right_ = nullptr;
    }

    // Copy assignment.
    BinarySearchTree& operator= (const BinarySearchTree& bst) {
      BinarySearchTree tmp = bst;
      std::swap(*this, tmp);
      return *this;
    }

    // Move assignment.
    BinarySearchTree& operator= (BinarySearchTree&& bst) noexcept {
      std::swap(data_, bst.data_);
      std::swap(left_, bst.left_);
      std::swap(right_, bst.right_);

      return *this;
    }

    const T& data() const {
      return data_;
    }

    BinarySearchTree* left() const {
      return left_;
    }

    BinarySearchTree* right() const {
      return right_;
    }

    void insert(const T& d) {
      _insert(d);
    }

    void insert(const T&& d) {
      _insert(std::move(d));
    }
};

}

#endif //CPPTOOLS_TREES_H
