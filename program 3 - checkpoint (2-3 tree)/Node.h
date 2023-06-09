#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {
  friend class Tree;
public:
  Node();
  Node(string);

private:
  string small; // left key
  string large; // right key

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif
