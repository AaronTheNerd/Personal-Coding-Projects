// Written by Aaron Barge
// Copyright 2019


#ifndef _FOREST_HUFFMAN_TREE_H_
#define _FOREST_HUFFMAN_TREE_H_
#include <string>
#include <map>
#include "Tree.h"


class Huffman {
 public:
  Huffman();                                            // Default tree constructor
  ~Huffman();                                           // Tree destructor
  void Add(std::string);                                // Adds text to the tree
  bool Contains(std::string) const;                     // Returns true if a character is contained in the character set
  std::string GetCodeOf(std::string) const;             // Returns the code of a character if that character is in the Huffman tree
  std::string Top() const;                              // Returns the entire character set
  unsigned int Size() const;                            // Returns the amount of characters in the character set
  unsigned int MaxDepth() const;                        // Returns the maximum size of an encoded character
  unsigned int Depth(std::string) const;                // Returns the size of the specified encoded character
  void Print() const;                                   // Print's each character's frequency and code
  std::string Encode() const;                           // Returns all the text encoded using Huffman Encoding
  std::string Decode(std::string) const;                // Attempts to Decode a binary string into it's original text based off of current Huffman Codes
  void PrintTop() const;                                // Print's the entire character set and character count
 protected:
  class Node {
   public:
    class Edge {
     public:
      Node* to;
      Edge() { to = NULL; }
      Edge(Node* to_) { to = to_; }
      ~Edge() { delete(to); }
      Node* operator->() { return to; }
      Node& operator*() { return *to; }
    };
    std::string character;
    int frequency;
    std::string code;
    Edge left;
    Edge right;
    Node();                                             // Default node constructor
    Node(std::string, int);                             // Node constructor with only value
    Node(const std::pair<std::string, int>&);           // Node constructor for type conversion
    Node(const Node&);
    Node operator=(const std::pair<std::string, int>&);
    ~Node();                                            // Node destructor
  };                                                    // Helper methods and root
  class comp {
   public:
    bool operator() (const Node& n1, const Node& n2) const;
  };
  Node* root;
  std::map<std::string, int> char_freqs;
  std::string text;
  void DestroyTree(Node*);
  void GetCharFreqs(std::string);
  void Add();
  void GetCodes();
  void GetCodes(Node*, std::string);
  std::string GetCodeOf(Node*, std::string) const;
  bool Contains(Node*, std::string) const;
  unsigned int Size(Node*) const;
  unsigned int MaxDepth(Node*, unsigned int depth) const;
  unsigned int Depth(Node*, std::string, unsigned int depth) const;
  void PrintInOrder(Node*) const;
};
#endif