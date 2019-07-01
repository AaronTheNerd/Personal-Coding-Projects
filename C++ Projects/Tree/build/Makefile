# Makefile for compiling my forest
CXX = g++
CXXFLAGS = -Wall -g

FOREST = $(wildcard ../Forest/*.h) $(wildcard ../Forest/*.cc)
TESTING_FILES = $(wildcard ../src/*.h) $(wildcard ../src/*.cc)
OBJ_FILES = AVL_Testing.o BST_Testing.o DL_Testing.o Forest_Testing.o Huffman.o TTTree_Testing.o

tree: $(TESTING_FILES) $(FOREST) $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o tree *.o

Forest_Testing.o: ../src/Forest_Testing.cc $(OBJ_FILES) $(FOREST) $(TESTING_FILES)
	$(CXX) $(CXXFLAGS) -c ../src/Forest_Testing.cc

BST_Testing.o: ../src/BST_Testing.* ../Forest/BinaryTree.*
	$(CXX) $(CXXFLAGS) -c ../src/BST_Testing.cc

DL_Testing.o: ../src/DL_Testing.* ../Forest/DoublyLinkedTree.*
	$(CXX) $(CXXFLAGS) -c ../src/DL_Testing.cc

Huffman.o: ../src/Huffman_Testing.* ../Forest/Huffman.*
	$(CXX) $(CXXFLAGS) -c ../src/Huffman_Testing.cc ../Forest/Huffman.cc

AVL_Testing.o: ../src/AVL_Testing.* ../Forest/AVLTree.*
	$(CXX) $(CXXFLAGS) -c ../src/AVL_Testing.cc

TTTree_Testing.o: ../src/TTTree_Testing.* ../Forest/TwoThreeTree.*
	$(CXX) $(CXXFLAGS) -c ../src/TTTree_Testing.cc

clean:
	rm *.o tree