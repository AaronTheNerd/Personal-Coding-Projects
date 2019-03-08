// Written by Aaron Barge
// Copyright 2019
#ifndef _TREE_TESTING_CC_
#define _TREE_TESTING_CC_
#include "Tree.h"
#include "BinaryTree.h"
#include "DoublyLinkedTree.h"
#include "Hoffman.h"
#endif

bool testBinaryTree(BinaryTree<int> t);
bool testDoublyLinkedTree(Tree<int> t);
bool testHoffmanTree(Tree<int>);

int main(int argc, char** argv) {
  BinaryTree<int> BST;
  testBinaryTree(BST);
}
bool testBinaryTree(BinaryTree<int> t) {
  
}