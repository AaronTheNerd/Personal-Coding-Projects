// Written by Aaron Barge
// Copyright 2019

#include "binarySearchTree.h"
#include <stdio>
int main(int argc, char** argv) {
  Tree* t;
  t->Add(5);
  t->Add(4);
  t->Add(19);
  t->Add(2);
  t->Add(7);
  t->Add(12);
  t->Add(1);
  t->Add(3);
  t->Add(10);
  t->Add(6);

  if (!t->Contains(5))
    return 1;
  std::cout << "Contain Test 1 PASSED" << std::endl;
  if (t->Contains(100))
    return 1;
  std::cout << "Contain Test 2 PASSED" << std::endl;
  t->Pop();
  if (t->Contains(5))
    return 1;
  std::cout << "Pop Test PASSED" << std::endl;
  t->Remove(10);
  if (t->Contains(10))
    return 1;
  std::cout << "Remove Test PASSED" << std::endl;
  return 0;
}