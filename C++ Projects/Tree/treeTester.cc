// Written by Aaron Barge
// Copyright 2019

#include "binarySearchTree.h"
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
  if (t->Contains(100))
    return 1;
  t->Pop();
  if (t->Contains(5))
    return 1;
  t->Remove(10);
  if (t->Contains(10))
    return 1;
  return 0;
}