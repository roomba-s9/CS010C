#include <iostream>
#include "Node.h"

Node::Node() : 
             leftChild(nullptr),
             rightChild(nullptr),
             key(""),
             count(1),
             height(-999),
             balFactor(-999) {}

Node::Node(string key) :
             leftChild(nullptr),
             rightChild(nullptr),
             key(key),
             count(1),
             height(-999),
             balFactor(-999) {}

Node* Node::getLeftChild() const {
    return this->leftChild;
}

Node* Node::getRightChild() const {
    return this->rightChild;
}

Node *Node::getParent() const {
    return this->parent;
}

void Node::setLeftChild(Node *insert) {
    this->leftChild = insert;
}

void Node::setRightChild(Node *insert) {
    this->rightChild = insert;
}

void Node::setParent(Node *par) {
    this->parent = par;
}

string Node::getKey() const {
    return key;
}

void Node::setKey(string key) {
    this->key = key;
}

void Node::addCount() {
    count++;
}

void Node::subCount() {
    count--;
}

int Node::getCount() const {
    return count;
}

void Node::copyData(Node *node) {
    // copies the data (count and key) from one node to another,
    // keeping the left and right child pointers
    count = node->getCount();
    key = node->getKey();
}