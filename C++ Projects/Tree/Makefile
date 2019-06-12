# Makefile for compiling my forest
CXX = g++
CXXFLAGS = -Wall -g

tree: BST_Testing.o DL_Testing.o
	$(CXX) $(CXXFLAGS) -o tree BST_Testing.o DL_Testing.o

BST_Testing.o: BST_Testing.cc BinaryTree.cc BinaryTree.h
	$(CXX) $(CXXFLAGS) -c BST_Testing.cc BinaryTree.h

DL_Testing.o: DL_Testing.cc DoublyLinkedTree.cc DoublyLinkedTree.h
	$(CXX) $(CXXFLAGS) -c DL_Testing.cc DoublyLinkedTree.h

clean:
	rm *.o & rm *.gch