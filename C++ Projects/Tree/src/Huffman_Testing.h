// Written by Aaron Barge
// Copyright 2019
#ifndef _TREE_HUFFMAN_TESTING_CC_
#define _TREE_HUFFMAN_TESTING_CC_
#include <iostream>
#include <string>
#include "../Forest/Tree.h"
#include "../Forest/Huffman.h"
#endif 

struct HUFFMAN_TESTER {
  static bool testHuffmanTree(Huffman* t) {
    std::cout << "Testing Huffman Tree" << std::endl;
    bool result = true;
    std::cout << "Adding values..." << std::endl;
    t->Add(std::string("some stuff to add like apples bananas and other fruit"));
    std::cout << "Values added successfully" << std::endl;
    t->PrintTop();
    std::cout << "The size of the tree is currently: " << t->Size() << std::endl;
    std::cout << "The maximum depth of the tree is currentlty: " << t->MaxDepth() << std::endl;
    t->Print();
    std::cout << "Adding additional values" << std::endl;
    t->Add(std::string(" heres some more stuff to make sure more text can be added"));
    std::cout << "Values added successfully" << std::endl;
    std::cout << "The size of the tree is currently: " << t->Size() << std::endl;
    std::cout << "The maximum depth of the tree is currentlty: " << t->MaxDepth() << std::endl;
    t->Print();
    std::string encoded_text = t->Encode();
    std::cout << "Encoded text:" << encoded_text << std::endl;
    std::cout << "Decoded text:" << t->Decode(encoded_text) << std::endl;
    std::cout << "Entire character set:" << t->Top() << std::endl;
    std::cout << "Testing contains a contained character" << (t->Contains("f") ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Huffman Tree testing has " << (result ? "PASSED" : "FAILED") << std::endl;
    return result;
  }
};