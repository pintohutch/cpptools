// Tests the LinkedList implementation.

#include "cpptools/linkedlist.h"

#include "gtest/gtest.h"

class LinkedListTest : public ::testing::Test {
  protected:
    // Reference on setup/teardown vs constructors/desctructors:
    // https://stackoverflow.com/a/13587712
    virtual void SetUp() {
      ll_ = cpptools::LinkedList<int>(1);
    }

    virtual void TearDown() {
    }

  cpptools::LinkedList<int> ll_;
};

TEST_F(LinkedListTest, DefaultConstructor) {
  EXPECT_EQ(ll_.size(), 1);
}

TEST_F(LinkedListTest, PushPopSize) {
  ll_.Push(1);
  ll_.Push(3);
  EXPECT_EQ(ll_.size(), 3);
  EXPECT_EQ(ll_.Pop(), 3);
  EXPECT_EQ(ll_.Pop(), 1);
  EXPECT_EQ(ll_.Size(), 1);
}

TEST_F(LinkedListTest, CopyConstructor) {
  cpptools::LinkedList<int> ll2 = ll_;
  EXPECT_EQ(ll_.Size(), 1);
  EXPECT_EQ(ll_.Pop(), 1);
}
