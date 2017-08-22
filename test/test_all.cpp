// test_all.cpp runs all unit tests in project.

#include "gtest/gtest.h"

// argc - argument count
// argv - argument vector
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
