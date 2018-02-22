/**
 * \file test_all.cpp
 * Runs all unit tests in project.
 *
 * Copyright 2018 Daniel Clark
 */

#include "gtest/gtest.h"

// argc - argument count
// argv - argument vector
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
