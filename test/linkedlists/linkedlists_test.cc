// Tests the LinkedList implementation.

#include "cpptools/linkedlist.h"

#include "gtest/gtest.h"

class LinkedListTest : public ::testing::Test {
  protected:
    // Reference on setup/teardown vs constructors/destructors:
    // https://stackoverflow.com/a/13587712
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(LinkedListTest, DefaultConstructor) {
  cpptools::LinkedList<int> ll;
  EXPECT_EQ(ll.size(), 0);
}

TEST_F(LinkedListTest, LValueConstructor) {
  int i = 0;
  cpptools::LinkedList<int> ll(i);
  EXPECT_EQ(ll.size(), 1);
}

TEST_F(LinkedListTest, RValueConstructor) {
  cpptools::LinkedList<int> ll(0);
  EXPECT_EQ(ll.size(), 1);
}

