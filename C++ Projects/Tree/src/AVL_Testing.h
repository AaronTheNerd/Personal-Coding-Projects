#ifndef _TREE_AVL_TESTING_CC_
#define _TREE_AVL_TESTING_CC_
#include <iostream>
#include "../Forest/Tree.h"
#include "../Forest/AVLTree.h"
#endif 

struct AVL_TESTER {
  static bool testAVLTree(Tree<int>* t) {
    std::cout << "Testing AVL Tree" << std::endl;
    bool result = true;
    result &= test_add(t);
    result &= test_size_depth(t);
    result &= test_contains_contained(t);
    result &= test_contains_not_contained(t);
    result &= test_remove_10(t);
    result &= test_remove_2(t);
    result &= test_remove_not_contained(t);
    result &= test_size_depth(t);
    result &= test_pop(t);
    result &= test_size_depth(t);
    std::cout << "The depth of 12 is " << t->Depth(12) << std::endl;
    std::cout << "AVL Tree testing has " << (result ? "PASSED" : "FAILED") << std::endl;
    return result;
  }
 private:
  static bool test_add(Tree<int>* t) {
    std::cout << "Adding values..." << std::endl;
    try {
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
      std::cout << "Values added successfully" << std::endl;
      t->Print();
      return true;
    } catch (...) {
      std::cout << "Values add unsuccessfully" << std::endl;
      return false;
    }
  }
  static bool test_size_depth(Tree<int>* t) {
    try {
      std::cout << "The size of the tree is currently: " << t->Size() << std::endl;
      std::cout << "The maximum depth of the tree is currentlty: " << t->MaxDepth() << std::endl;
      return true;
    } catch (...) {
      std::cout << "An unknown error occured with either Size() or MaxDepth()" << std::endl;
      return false;
    }
  }
  static bool test_contains_contained(Tree<int>* t) {
    bool contains_result = false;
    try {
      contains_result = t->Contains(5);
    } catch (...) {
      std::cout << "An unknown error occured with Contains() and a contained value" << std::endl;
      return false;
    }
    if (!contains_result) {
      std::cout << "Contains contained value test failed" << std::endl
          << "  Expected: " << true << std::endl
          << "  Actual: " << contains_result << std::endl;
      return false;
    } else {
      std::cout << "Contains contained value test passed" << std::endl;
      return true;
    }
  }
  static bool test_contains_not_contained(Tree<int>* t) {
    bool contains_result = true;
    try {
      contains_result = t->Contains(100);
    } catch (...) {
      std::cout << "An unknown error occured with Contains() and a not contained value" << std::endl;
      return false;
    }
    if (contains_result) {
      std::cout << "Contains not contained value test failed" << std::endl
          << "  Expected: " << false << std::endl
          << "  Actual: " << contains_result << std::endl;
      return false;
    } else {
      std::cout << "Contains not contained value test passed" << std::endl;
      return true;
    }
  }
  static bool test_remove_10(Tree<int>* t) {
    std::cout << "Removing 10" << std::endl;
    try {
      t->Remove(10);
      t->Print();
    } catch (...) {
      std::cout << "An unknown error occured while removing 10" << std::endl;
      return false;
    }
    if (t->Contains(10)) {
      std::cout << "Value removal was unsuccessful" << std::endl
          << "  Expected: " << false << std::endl
          << "  Actual: " << t->Contains(10) << std::endl;
      return false;
    } else {
      std::cout << "Value removal was successful" <<std::endl;
      return true;
    }
  }
  static bool test_remove_2(Tree<int>* t) {
    std::cout << "Removing 2" << std::endl;
    try {
      t->Remove(2);
      t->Print();
    } catch (...) {
      std::cout << "An unknown error occured while removing 2" << std::endl;
      return false;
    }
    if (t->Contains(2)) {
      std::cout << "Value removal was unsuccessful" << std::endl
          << "  Expected: " << false << std::endl
          << "  Actual: " << t->Contains(2) << std::endl;
      return false;
    } else {
      std::cout << "Value removal was successful" <<std::endl;
      return true;
    }
  }
  static bool test_remove_not_contained(Tree<int>* t) {
    std::cout << "Removing value not contained in tree" << std::endl;
    try {
      t->Remove(100);
      t->Print();
      return true;
    } catch (...) {
      std::cout << "An unknown error occured with Remove() and a not contained value" << std::endl;
      return false;
    }
  }
  static bool test_pop(Tree<int>* t) {
    std::cout << "Popping off root" << std::endl;
    int old_root;
    try {
      old_root = t->Pop();
      t->Print();
    } catch (...) {
      std::cout << "An unknown error occured with Pop()" << std::endl;
      return false;
    }
    std::cout << "Making sure " << old_root << " was removed successfully" << std::endl;
    if (t->Contains(old_root)) {
      std::cout << "Value removal was unsuccessful" << std::endl
                << "  Expected: " << false << std::endl
                << "  Actual: " << t->Contains(old_root) << std::endl;
      return false;
    } else {
      std::cout << "Pop test was successful" << std::endl;
      return true;
    }
    
  }
};