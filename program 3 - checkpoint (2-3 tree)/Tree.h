#ifndef __TREE_H
#define __TREE_H

#include <iostream>
#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  Tree(const Tree &); // copy constructor
  Tree& operator=(const Tree &); // copy assignment operator
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search(const string &) const;

private:
  // Add additional functions/variables here
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;

  bool searchHelper(Node *, const string &) const;
  void insertHelper(Node *, const string &);
  void removeHelper(Node *, const string &);
  void insertToLeaf(Node *, string &);
  void splitAndInsert(Node *, Node*, const string &);
  bool isLeaf(Node *) const;
  bool isFull(Node *) const;


};

#endif
