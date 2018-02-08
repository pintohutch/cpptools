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
  int size = end-beg;
  int mid = beg + (end-beg)/2;
  // Lists of size 0 or 1 are already sorted.
  if (size < 2) {
    return;
  }
  else {
    _merge_sort(unsorted, beg, mid);
    _merge_sort(unsorted, mid, end);
  }

  // Sort each sorted-half into one vector.
  std::vector<T> tmp;
  tmp.resize(size);
  int l = beg, r = mid, t = 0;
  while (l < mid && r < end) {
    if (unsorted[l] < unsorted[r]) {
      tmp[t++] = std::move(unsorted[l++]);
    } else {
      tmp[t++] = std::move(unsorted[r++]);
    }
  }

  // Capture any leftovers.
  while (l < mid) {
    tmp[t++] = std::move(unsorted[l++]);
  }
  while (r < end) {
    tmp[t++] = std::move(unsorted[r++]);
  }

  // Move sorted tmp array elements back into input.
  for (int i=0; i < tmp.size(); i++) {
    unsorted[i] = std::move(tmp[i]);
  }

}
}

#endif //CPPTOOLS_SORT_H
