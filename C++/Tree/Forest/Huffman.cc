// Written by Aaron Barge
// Copyright 2019


#ifndef _FOREST_HUFFMAN_TREE_CC_
#define _FOREST_HUFFMAN_TREE_CC_
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "Huffman.h"
#endif


/*
 * Constructors
 */
Huffman::Huffman():
    root(NULL), char_freqs(std::map<std::string, int>()), text(std::string("")) {}
Huffman::Node::Node():
    character(std::string("_")), frequency(0), code(std::string("")), left(Edge()), right(Edge()) {}
Huffman::Node::Node(const std::pair<std::string, int>& pair):
    character(pair.first), frequency(pair.second), code(std::string("")), left(Edge()), right(Edge()) {}
Huffman::Node::Node(std::string char_, int val_):
    character(char_), frequency(val_), code(std::string("")), left(Edge()), right(Edge()) {}
Huffman::Node::Node(const Huffman::Node& n):
    character(n.character), frequency(n.frequency), code(n.code), left(n.left), right(n.right) {}


/*
 * Destructor
 */
Huffman::~Huffman() {
  DestroyTree(this->root);
}
void Huffman::DestroyTree(Huffman::Node* current) {
  if (current != NULL) {
    DestroyTree(current->left.to);
    DestroyTree(current->right.to);
    delete current;
  }
}
Huffman::Node::~Node() {
  this->left.to = NULL;
  this->right.to = NULL;
}


/*
 * Node addition
 */
void Huffman::Add(std::string text) {
  this->text += text;
  this->GetCharFreqs(text);
  this->Add();
  this->GetCodes();
}
void Huffman::GetCharFreqs(std::string text) {
  for (unsigned int i = 0; i < text.size(); ++i) {
    auto result = this->char_freqs.emplace(text[i] + std::string(""), 1);
    bool new_pair = result.second;
    if (!new_pair) {
      auto iterator = result.first;
      iterator->second = iterator->second + 1;
    }
  }
}
bool Huffman::comp::operator() (const Node& n1, const Node& n2) const {
  return n1.frequency > n2.frequency;
}
Huffman::Node Huffman::Node::operator=(const std::pair<std::string, int>& pair) {
  Node* n = new Node(pair.first, pair.second);
  return *n;
}
void Huffman::Add() {
  std::priority_queue<Huffman::Node, std::vector<Huffman::Node>, Huffman::comp> PQ(this->char_freqs.begin(), this->char_freqs.end());
  while (PQ.size() > 1) {
    Huffman::Node n1 = Huffman::Node(PQ.top());
    PQ.pop();
    Huffman::Node n2 = Huffman::Node(PQ.top());
    PQ.pop();
    Huffman::Node* n = new Huffman::Node(n1.character + n2.character, n1.frequency + n2.frequency);
    n->left.to = new Node(n1);
    n->right.to = new Node(n2);
    PQ.push(*n);
  }
  Huffman::Node node = PQ.top();
  this->root = new Node(node);
}
void Huffman::GetCodes() {
  return this->GetCodes(this->root, std::string(""));
}
void Huffman::GetCodes(Huffman::Node* curr, std::string curr_code) {
  if (curr == NULL) {
    return;
  } else if (curr->left.to == NULL && curr->right.to == NULL) {
    curr->code = curr_code;
    return;
  } else {
    this->GetCodes(curr->left.to, curr_code + std::string("1"));
    this->GetCodes(curr->right.to, curr_code + std::string("0"));
  }
}


/*
 * Searching
 */
bool Huffman::Contains(std::string character) const {
  return Contains(this->root, character);
}
bool Huffman::Contains(Huffman::Node* current, std::string character) const {
  if (current == NULL) {
    return false;
  } else if (current->left.to == NULL && current->right.to == NULL && current->character == character) {
    return true;
  } else {
    bool left_true = this->Contains(current->left.to, character);
    bool right_true = this->Contains(current->right.to, character);
    return left_true || right_true;
  }
}


/*
 * Top method
 */
std::string Huffman::Top() const {
  if (this->root)
    return this->root->character;
  else
    return NULL;
}


/*
 * Size and Depth methods
 */
unsigned int Huffman::Size() const {
  return this->root->character.size();
}
unsigned int Huffman::MaxDepth() const {
  return MaxDepth(this->root, 0);
}
unsigned int Huffman::MaxDepth(Huffman::Node* current, unsigned int curr_depth) const {
  if (current == NULL)
    return curr_depth;
  else {
    unsigned int left_depth = MaxDepth(current->left.to, curr_depth + 1);
    unsigned int right_depth = MaxDepth(current->right.to, curr_depth + 1);
    return (left_depth > right_depth) ? left_depth : right_depth;
  }
}
unsigned int Huffman::Depth(std::string character) const {
  if (this->root == NULL)
    return -1;
  return Depth(this->root, character, 0);
}
unsigned int Huffman::Depth(Huffman::Node* current, std::string character, unsigned int curr_depth) const {
  if (current == NULL)
    return -1;
  if (current->character == character)
    return curr_depth;
  if (current->character > character)
    return Depth(current->left.to, character, curr_depth + 1);
  else
    return Depth(current->right.to, character, curr_depth + 1);
}


/*
 * Encoding
 */
std::string Huffman::Encode() const {
  std::string encoded_text = std::string("");
  for (unsigned int i = 0; i < this->text.size(); ++i) {
    std::string character = this->text[i] + std::string("");
    std::string code = this->GetCodeOf(character);
    encoded_text += (code == std::string("")) ? ("Failed") : (code);
  }
  return encoded_text;
}
std::string Huffman::GetCodeOf(std::string character) const {
  return this->GetCodeOf(this->root, character);
}
std::string Huffman::GetCodeOf(Huffman::Node* curr, std::string character) const {
  if (curr == NULL) {
    return std::string("");
  } else if (curr->left.to == NULL && curr->right.to == NULL && curr->character == character) {
    return curr->code;
  } else {
    std::string left_code = GetCodeOf(curr->left.to, character);
    std::string right_code = GetCodeOf(curr->right.to, character);
    return (left_code == std::string("") && right_code == std::string("")) ? (std::string("")) : ((left_code == std::string("")) ? (right_code) : (left_code));
  }
}


/*
 * Decoding
 */
std::string Huffman::Decode(std::string encoded_text) const {
  Huffman::Node* curr = this->root;
  std::string decoded_text = std::string("");
  for (unsigned int i = 0; i < encoded_text.size(); ++i) {
    if (curr == NULL) {
      curr = this->root;
    } else {
      curr = (encoded_text[i] + std::string("") == "1") ? (curr->left.to) : (curr->right.to); 
      if (curr->left.to == NULL && curr->right.to == NULL) {
        decoded_text += curr->character;
        curr = this->root;
      }
    }
  }
  return decoded_text;
}


/*
 * Print method 
 */
void Huffman::Print() const {
  if (this->root == NULL)
    return;
  PrintInOrder(this->root);
  std::cout << std::endl;
}
void Huffman::PrintInOrder(Huffman::Node* curr) const {
  if (curr == NULL) {
    return;
  } else if (curr->left.to == NULL && curr->right.to == NULL) {
    std::cout << "'" << curr->character << "': " << curr->frequency << "| " << curr->code << std::endl;
    return;
  } else {
    PrintInOrder(curr->left.to);
    PrintInOrder(curr->right.to);
  }
}


/*
 * Print memory locations for top (debugging)
 */
void Huffman::PrintTop() const {
  std::cout << "The address of the root is: " << this->root << std::endl;
  if (this->root != NULL) {
    std::cout << "  And its character is: '" << this->root->character << "'" << std::endl;
  } else {
    std::cout << "  The Root is NULL" << std::endl;
  }
  std::cout << "The address of the root's left child is: " << this->root->left.to <<  std::endl;
  if (this->root->left.to) {
    std::cout << "  And its character is: '" << this->root->left->character << "'" << std::endl;
  } else {
    std::cout << "  The left child is NULL" << std::endl;
  }
  std::cout << "The address of the root's right child is: " << this->root->right.to << std::endl;
  if (this->root->right.to) {
    std::cout << "  And its character is: '" << this->root->right->character << "'" << std::endl;
  } else {
    std::cout << "  The right child is NULL" << std::endl;
  }
  std::cout << std::endl;
}