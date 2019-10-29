// Written by Aaron Barge
// Copyright 2019

#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <math.h>

namespace stat {

// Forward Declaration
void merge_sort(std::vector<int>&, int, int, int);
void merge(std::vector<int>&, int, int, int);

// Implementation
std::vector<int> generate_resolutions(int list_size) { // Creates a list of min thread sizes so that the sort will create 1-32 threads
    std::vector<int> resolutions;
    for (int i = 1; i >= -4; --i) {
        resolutions.push_back(list_size * std::pow(2, i));
    }
    return resolutions;
}

std::vector<int> generate_list(int list_size) { // Creates a list of random numbers between 0-list_size
    std::vector<int> list(list_size);
    std::srand((unsigned)time(0));
    for (size_t i = 0; i < list.size(); ++i)
        list[i] = std::rand() % list_size;
    return list;
}

void print_list(std::vector<int> list) { // Prints the list
    std::cout << "[";
    for (size_t i = 0; i < list.size(); ++i)
        std::cout << list[i] << ((i + 1 == list.size()) ? "]" : ", ");
    std::cout << std::endl;
}

bool sorted(std::vector<int> list) { // Checks if a given list is sorted
    for (size_t i = 0, j = 1; j < list.size(); i++, j++) {
        if (list[i] > list[j])
            return false;
    }
    return true;
}

int sort(std::vector<int>& list, int resolution) { // Times and sorts a list
    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(list, 0, list.size() - 1, resolution);
    auto end = std::chrono::high_resolution_clock::now();
    auto micro_s = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return micro_s.count();
}

void merge_sort(std::vector<int>& list, int lower, int upper, int resolution) { // Merge sort implementation and creates a thread if the lsit is longer than resolution
    int middle = (upper + lower) / 2;
    if (lower < upper && upper - lower + 1 >= resolution) {
        std::thread t(merge_sort, std::ref(list), lower, middle, resolution);
        auto t_id = t.get_id();
        if (std::this_thread::get_id() != t_id)
            merge_sort(list, middle + 1, upper, resolution);
        t.join();
        merge(list, lower, middle, upper);
    } else if (lower < upper) {
        merge_sort(list, lower, middle, resolution);
        merge_sort(list, middle + 1, upper, resolution);
        merge(list, lower, middle, upper);
    }
}

void merge(std::vector<int>& list, int lower, int middle, int upper) { // Merges 2 sorted lists into one sorted list
    std::vector<int> temp(upper - lower + 1);
    int i = lower, j = middle + 1, k = 0;
    while (i <= middle && j <= upper) {
        if (list[i] <= list[j]) {
            temp[k] = list[i];
            k++;
            i++;
        } else {
            temp[k] = list[j];
            k++;
            j++;
        }
    }
    while (i <= middle) {
        temp[k] = list[i];
        k++;
        i++;
    }
    while (j <= upper) {
        temp[k] = list[j];
        k++;
        j++;
    }
    for (i = lower; i <= upper; i++) {
        list[i] = temp[i - lower];
    }
}
} // stat