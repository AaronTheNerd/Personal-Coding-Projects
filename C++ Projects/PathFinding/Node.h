// Written by Aaron Barge
// Copyright 2019

#ifndef _PATHFINDING_NODE_H_
#define _PATHFINDING_NODE_H_
#include <vector>


class Node {
 public:
  class Edge {
   public:
    Node* to;
    int weight;
    Edge(Node* n_ = NULL, int weight_ = -1): to(n_), weight(weight_) {}
    ~Edge() { delete(to); }
    Node* operator->() {return to; }
    Node& operator*() { return *to; }
    inline int getWeight() const { return weight; } 
  };
  Node();
  Node(int x, int y);
  inline std::vector<Edge> getNeighbors() const { return neighbors_; }
  inline int getX() const { return x_; }
  inline int getY() const { return y_; }
  bool operator!=(const Node* n) const;
  bool operator==(const Node* n) const;
  void setPos(int, int);
  void checkConnections();
  void addEdge(Node* to);
  Node* prev;
  std::vector<Node::Edge> neighbors_;
 protected:
  int x_;
  int y_;
};
#endif