// Tests the linkedlist.cpp implementation.

#include "cpptools/linkedlist.h"

#include "gtest/gtest.h"

class LinkedListTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    cpptools::LinkedList<int> ll_;
};

TEST_F(LinkedListTest, DefaultConstructor) {
  EXPECT_EQ(ll_.Size(), 0);
}

TEST_F(LinkedListTest, PushPopSize) {
  ll_.Push(1);
  ll_.Push(3);
  EXPECT_EQ(ll_.Size(), 2);
  EXPECT_EQ(ll_.Pop(), 3);
  EXPECT_EQ(ll_.Pop(), 1);
  EXPECT_EQ(ll_.Size(), 0);
}
