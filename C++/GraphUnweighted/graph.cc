// Written by Aaron Barge
// Copyright 2019

#ifndef _C_PLUS_PLUS_PROJECTS_GRAPH_CC_
#define _C_PLUS_PLUS_PROJECTS_GRAPH_CC_
#include "graph.h"
#include <vector>
#endif
Graph::Graph() {
  this->origin = NULL;
  this->nodes = std::vector<Node*>();
}
void Graph::AddNode(int node_value) {
  Node* n = new Node(node_value);
  if (!this->origin)
    this->origin = n;
  this->nodes.push_back(n);
}
void Graph::AddLink(int from, int to) {
  Node* n_from = FindNode(from);
  if (!n_from) {
    this->AddNode(from);
    n_from = this->nodes[this->nodes.size() - 1];
  }
  Node* n_to = FindNode(to);
  if (!n_to) {
    this->AddNode(to);
    n_to = this->nodes[this->nodes.size() - 1];
  }
  n_from->AddLink(n_to);
}
void Graph::RemoveNode(int node_value) {
  Node* to_be_removed = FindNode(node_value);
  if (!to_be_removed)
    return;
  for (Node* n : to_be_removed->in)
    n->RemoveLink(to_be_removed);
  for (Node* n : to_be_removed->out)
    n->RemoveLink(to_be_removed);
  delete to_be_removed->in;
  delete to_be_removed->out;
  delete to_be_removed->val;
  delete to_be_removed;
}
void Graph::RemoveLink(int from, int to) {
  Node n_from = FindNode(from);
  Node n_to = FindNode(to);
  if (!(n_from && n_to))
  
}
Graph::Node::Node() {

}
Graph::Node::Node(int val_) {

}
void Graph::Node::AddLink(Node* to) {

}
void Graph::Node::RemoveLink(Node* to) {

}
Graph::Node* Graph::FindNode(int node_val) {
  for (size_t index = 0; index < this->nodes.size(); ++i)
    if (this->nodes[index].val == node_val)
      return this->nodes[index];
  return NULL;
}