/** \file sort.h
 * Various array sorting algorithms.
 *
 * Copyright 2018 Daniel Clark
 */

// Define guard
#ifndef CPPTOOLS_SORT_H_
#define CPPTOOLS_SORT_H_

#include <cstddef>
#include <iostream>
#include <vector>

namespace {
  template <typename T>
  void _merge_sort(std::vector<T>& unsorted, int beg, int end);
}

namespace cpptools {

/**
 * This function sorts the provided vector using the
 * <a href="https://en.wikipedia.org/wiki/Merge_sort>merge sort</a> algorithm.
 *
 * Runtime: O(nlogn)
 * Memory: O(n)
 *
 * @tparam T objects must provide operator< and operator=.
 * @param unsorted unsorted vector.
 * @return the sorted version of the passed-in vector.
 */
template <typename T>
void merge_sort(std::vector<T>& unsorted) {
    return _merge_sort(unsorted, 0, unsorted.size());
}

}

// Intentionally anonymous namespace so can't be referred to externally.
namespace {
template <typename T>
void _merge_sort(std::vector<T>& unsorted, int beg, int end) {
  std::vector<T> lhs, rhs;
  int size = end-beg;
  // Lists of size 0 or 1 are already sorted.
  if (size < 2) {
    return;
  }
  else {
    _merge_sort(unsorted, beg, end / 2);
    _merge_sort(unsorted, end / 2, end);
  }

  // Sort each sorted-half into one vector.
  std::vector<T> sorted;
  sorted.resize(size);
  int l = 0, r = 0, s = 0;
  while (l < lhs.size() && r < rhs.size()) {
    if (lhs[l] < rhs[r]) {
      sorted[s++] = lhs[l++];
    } else {
      sorted[s++] = rhs[r++];
    }
  }

  // Capture any leftovers.
  while (l < lhs.size()) {
    sorted[s++] = lhs[l++];
  }
  while (r < rhs.size()) {
    sorted[s++] = rhs[r++];
  }

  return;

}
}

#endif //CPPTOOLS_SORT_H
