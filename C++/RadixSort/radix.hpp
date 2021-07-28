// Written by Aaron Barge
// Radix sort with counting sort


#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>
#pragma once


namespace atn {
typedef unsigned long long ULL;
#define DEFAULT_RADIX 256


template <typename T>
void print_arr(std::vector<T> arr) {
  std::cout << "[";
  for (ULL index = 0; index < arr.size(); ++index) {
    std::cout << arr[index];
    if (index + 1 != arr.size())
      std::cout << ", ";
  }
  std::cout << "]" << std::endl << std::endl;
}


template <typename T>
bool is_sorted(std::vector<T> arr) {
  for (ULL index = 1; index < arr.size(); ++index)
    if (arr[index] < arr[index - 1])
      return false;
  return true;
}


size_t MSB(size_t num) {
  if (num == 0)
    return 0;
  int msb = 0;
  num >>= 1;
  while (num != 0) {
    num >>= 1;
    msb++;
  }
  return msb;
}


template <typename T>
void radix_sort(std::vector<T>* input, size_t radix) {
  std::vector<size_t> counts(radix, 0);
  std::vector<T>* output = new std::vector<T>(input->size(), 0);
  std::vector<T>* original = input;
  size_t msb = MSB(radix);
  assert((1 << msb) == radix); // Ensure that the radix is 1 << n where n > 0
  std::cout << "MSB: " << msb << ", sizeof(T): " << sizeof(T) << std::endl;
  for (ULL iter = 0; iter < (sizeof(T) << 2) / msb; ++iter) {

    for (ULL index = 0; index < counts.size(); ++index) {
      counts[index] = 0;
    }

    ULL mask = (radix - 1) << (iter * msb);

    for (ULL index = 0; index < input->size(); ++index) {
      counts[(input->at(index) & mask) >> (iter * msb)]++;
    }

    for (ULL index = 1; index < counts.size(); ++index) { // Prefix sum
      counts[index] += counts[index - 1];
    }

    for (ULL index = input->size() - 1; index != ULL(-1); --index) {
      output->at(--counts[(input->at(index) & mask) >> (iter * msb)]) = input->at(index);
    }

    std::swap(input, output);
  }
  if (output == original) {
    std::swap(input, output);
    for (ULL index = 0; index < input->size(); ++index) {
      input->at(index) = output->at(index);
    }
  }
  delete output;
}


template<typename T>
void radix_sort(std::vector<T>& arr, size_t radix) {
  radix_sort(&arr, radix);
  return arr;
}


template<typename T>
void radix_sort(std::vector<T>& arr) {
  radix_sort(&arr, DEFAULT_RADIX);
}


} // end namespace atn