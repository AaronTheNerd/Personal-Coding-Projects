#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include "radix.hpp"


int main (int argc, char** argv) {
  std::vector<unsigned long> arr(100000000);
  srand(time(NULL));
  for (unsigned long long index = 0; index < arr.size(); ++index) {
    arr[index] = rand();
  }
  //atn::print_arr(arr);
  atn::radix_sort(arr);
  //atn::print_arr(arr);
  if (atn::is_sorted(arr))
    std::cout << "Sorting Successful!" << std::endl;
}