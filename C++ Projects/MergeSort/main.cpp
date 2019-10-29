// Written by Aaron Barge
// Copyright 2019

#include "stat.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char** argv) {
    const int DEFAULT_SIZE = 131072;
    int size;
    switch (argc) { // Figure out how many arguments were provided
        case 1: { // If no size was provided, use default
        size = DEFAULT_SIZE;
        break;
        } case 2: { // If a size was provided, use given size
        std::stringstream list_size_string(argv[1]);
        list_size_string >> size;
        break;
        } default: { // If something else was provided, error
        std::cout << "Please run file by ./sort <list size>" << std::endl;
        return -1;
        }
    }
    std::vector<int> resolutions = stat::generate_resolutions(size); // Generate range of min thread sizes
    std::ofstream output("results" + std::to_string(size) + ".csv", std::fstream::app); // Open up result file to be appended to
    for (size_t i = 0; i < resolutions.size(); ++i) { // Go through each min thread size
        std::cout << "List Size: " << size << ", Min Thread Size: " << resolutions[i] << std::endl; // Print parameters
        std::vector<int> list = stat::generate_list(size); // Generate a random list
        int micro_s = stat::sort(list, resolutions[i]); // Sort and size the runtime in micro seconds
        bool sorted = stat::sorted(list); // Test if list was sorted
        if (sorted) // Write to file only if the file was properly sorted
            output << micro_s << ((i + 1 == resolutions.size()) ? ("\n") : (",")); // Write to output file
        std::cout << "List Sorted: " << (sorted ? "SUCCESS" : "FAIL") << std::endl; // Show if list was sorted
        std::cout << "Sorting took: " << micro_s << " microseconds\n" << std::endl; // Print data
    }
    return 0;
}