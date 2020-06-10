// Written by Aaron Barge
// Copyright 2019

#include "binarySearchTree.h"
#include <iostream>
int main(int argc, char** argv) {
  Tree* t = new Tree;
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
  t->PrintInOrder();
  if (!t->Contains(5)) {
    return 1;
  }
  if (t->Contains(100))
    return 1;
  t->Remove(10);
  t->PrintInOrder();
  if (t->Contains(10))
    return 1;
  t->Remove(2);
  t->PrintInOrder();
  if (t->Contains(2))
    return 1;
  t->Remove(100);
  t->PrintInOrder();
  int old_root = t->Pop();
  t->PrintTop();
  t->PrintInOrder();
  if (t->Contains(old_root))
    return 1;
  return 0;
}