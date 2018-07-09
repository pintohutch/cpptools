/** \file trees_test.cc
 * Unit tests for the cpptools trees data structures.
 *
 * Copyright 2018 Daniel Clark
 */
#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

#include "cpptools/trees.h"


class BinarySearchTreeTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(BinarySearchTreeTest, SimpleConstructors) {
  int i = 1;
  cpptools::BinarySearchTree<int> bst_l{i};
  EXPECT_EQ(bst_l.data(), i);
  cpptools::BinarySearchTree<int> bst_r{std::move(i)};
  EXPECT_EQ(bst_r.data(), i);
}

TEST_F(BinarySearchTreeTest, CopyConstructor) {
  cpptools::BinarySearchTree<int> bst{1};
  bst.insert(0);
  bst.insert(2);
  cpptools::BinarySearchTree<int> copy{bst};
  EXPECT_EQ(bst.data(), copy.data());
  EXPECT_EQ(bst.left()->data(), copy.left()->data());
  EXPECT_EQ(bst.right()->data(), copy.right()->data());

  EXPECT_NE(bst.left(), copy.left());
  EXPECT_NE(bst.right(), copy.right());
}

TEST_F(BinarySearchTreeTest, MoveConstructor) {
  cpptools::BinarySearchTree<int> bst{1};
  bst.insert(2);
  bst.insert(0);
  cpptools::BinarySearchTree<int> bst2 = std::move(bst);
  EXPECT_EQ(bst2.data(), 1);
  EXPECT_EQ(bst2.left()->data(), 0);
  EXPECT_EQ(bst2.right()->data(), 2);

  EXPECT_EQ(bst.left(), nullptr);
  EXPECT_EQ(bst.right(), nullptr);
}

TEST_F(BinarySearchTreeTest, CopyAssignment) {
  cpptools::BinarySearchTree<int> bst{1};
  bst.insert(2);
  bst.insert(0);
  cpptools::BinarySearchTree<int> copy{0};
  copy = bst;
  EXPECT_EQ(bst.data(), copy.data());
  EXPECT_EQ(bst.left()->data(), copy.left()->data());
  EXPECT_EQ(bst.right()->data(), copy.right()->data());

  EXPECT_NE(bst.left(), copy.left());
  EXPECT_NE(bst.right(), copy.right());
}

TEST_F(BinarySearchTreeTest, MoveAssignment) {
  cpptools::BinarySearchTree<int> bst{1};
  bst.insert(2);
  bst.insert(0);
  cpptools::BinarySearchTree<int> bst2{0};
  bst2 = std::move(bst);
  EXPECT_EQ(bst2.data(), 1);
  EXPECT_EQ(bst2.left()->data(), 0);
  EXPECT_EQ(bst2.right()->data(), 2);

  EXPECT_EQ(bst.left(), nullptr);
  EXPECT_EQ(bst.right(), nullptr);
}

TEST_F(BinarySearchTreeTest, Insert) {
  cpptools::BinarySearchTree<int> bst{1};
  bst.insert(0);
  bst.insert(2);
  bst.insert(1);
  int i = -1;
  bst.insert(i);
  EXPECT_EQ(bst.data(), 1);
  EXPECT_EQ(bst.left()->data(), 0);
  EXPECT_EQ(bst.right()->data(), 2);
}
