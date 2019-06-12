# Makefile for compiling my forest
CXX = g++
CXXFLAGS = -Wall -g

FOREST = $(wildcard ../Forest/*.h) $(wildcard ../Forest/*.cc)
TESTING_FILES = $(wildcard ../src/*.h)
OBJ_FILES = AVL_Testing.o BST_Testing.o DL_Testing.o Forest_Testing.o Huffman_Testing.o TTTree_Testing.o

tree: Forest_Testing.o $(TESTING_FILES) $(FOREST)
	$(CXX) $(CXXFLAGS) -o *.o

Forest_Testing.o: ../src/Forest_Testing.cc $(OBJ_FILES) $(FOREST)
	$(CXX) $(CXXFLAGS) -c ../src/Forest_Testing.cc

BST_Testing.o: ../src/BST_Testing.h ../Forest/BinaryTree.cc ../Forest/BinaryTree.h
	$(CXX) $(CXXFLAGS) -c ../src/BST_Testing.cc

DL_Testing.o: ../src/DL_Testing.h ../Forest/DoublyLinkedTree.cc ../Forest/DoublyLinkedTree.h
	$(CXX) $(CXXFLAGS) -c ../src/DL_Testing.cc

Huffman_Testing.o: ../src/Huffman_Testing.cc ../Forest/Huffman.cc ../Forest/Huffman.h
	$(CXX) $(CXXFLAGS) -c ../src/Huffman_Testing.cc

AVL_Testing.o: ../src/AVL_Testing.h ../Forest/AVLTree.cc ../Forest/AVLTree.h
	$(CXX) $(CXXFLAGS) -c ../src/AVL_Testing.cc

TTTree_Testing.o: ../src/TTTree_Testing.h ../Forest/TwoThreeTree.cc ../Forest/TwoThreeTree.h
	$(CXX) $(CXXFLAGS) -c ../src/TTTree_Testing.cc

clean:
	rm *.o