// Written by Aaron Barge
// Copyright 2019
#ifndef _TREE_TESTING_CC_
#define _TREE_TESTING_CC_
#include <iostream>
#include "Tree.h"
#include "BinaryTree.h"
#include "DoublyLinkedTree.h"
#include "Huffman.h"
#endif

bool testBinaryTree(Tree<int>* t);
//bool testDoublyLinkedTree(Tree<int>* t);
//bool testHuffmanTree(Tree<int>* t);

int main(int argc, char** argv) {
  Tree<int>* Tree = new BinaryTree<int>();
  std::cout << "Testing Binary Search Tree" << std::endl;
  if (!testBinaryTree(Tree))
    std::cout << "Binary Search Tree FAILED" << std::endl;
  return 0;
}
bool testBinaryTree(Tree<int>* t) {
  t->Add(5);
  t->PrintTop();
  t->Add(4);
  t->PrintTop();
  t->Add(19);
  t->PrintTop();
  t->Add(2);
  t->Add(7);
  t->Add(12);
  t->Add(1);
  t->Add(3);
  t->Add(10);
  t->Add(6);
  t->Print();
  if (!t->Contains(5))
    return false;
  if (t->Contains(100))
    return false;
  t->Remove(10);
  t->Print();
  if (t->Contains(10))
    return false;
  t->Remove(2);
  t->Print();
  if (t->Contains(2))
    return false;
  t->Remove(100);
  t->Print();
  int old_root = t->Pop();
  t->PrintTop();
  t->Print();
  if (t->Contains(old_root))
    return false;
  return true;
}