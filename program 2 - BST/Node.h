#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {
 public:
    Node(); // default constructor
    Node(string); // overridden constructor
    Node* getLeftChild() const; // returns the node of the left child
    Node* getRightChild() const; // returns the node of the right child
    void setLeftChild(Node *); // sets the current node's left child
    void setRightChild(Node *); // set the current node's right child
    string getKey() const; // returns the string of the node's key
    void setKey(string); // sets the string of the node's key
    void addCount(); // increments the node's count by 1
    void subCount(); // decrements the node's count by 1
    int getCount() const; // returns the node's value of count
    void copyData(Node *); // copies the data values (key and count) from one node to another
 private:
    Node *leftChild;
    Node *rightChild;
    Node *parent;
    string key;
    int count;
};

#endif