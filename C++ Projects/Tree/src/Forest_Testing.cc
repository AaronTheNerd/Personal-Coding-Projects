// Written by Aaron Barge
// Copyright 2019

#ifndef _TREE_FOREST_TESTING_CC_
#define _TREE_FOREST_TESTING_CC_
#include "BST_Testing.h"
#include "DL_Testing.h"
#include "Huffman_Testing.h"
#include "AVL_Testing.h"
#include "TTTree_Testing.h"
#include <iostream>
#endif

int main(int argc, char** argv) {
  Tree<int>* t = new BinaryTree<int>();
  BST_TESTER bst;
  bst.testBinaryTree(t);
  std::cout << std::endl << std::endl << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << std::endl << std::endl;
  t = new DLTree<int>();
  DL_TESTER dl;
  dl.testDLTree(t);
  std::cout << std::endl << std::endl << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << std::endl << std::endl;
  Huffman* huffman = new Huffman();
  HUFFMAN_TESTER huff;
  huff.testHuffmanTree(huffman);
  delete huffman;
  std::cout << std::endl << std::endl << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << std::endl << std::endl;
  t = new AVLTree<int>();
  AVL_TESTER avl;
  avl.testAVLTree(t);
}