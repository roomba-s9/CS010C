#include <iostream>
#include "Node.h"

Node::Node() : 
             leftChild(nullptr),
             rightChild(nullptr),
             key(""),
             count(1) {}

Node::Node(string key) :
             leftChild(nullptr),
             rightChild(nullptr),
             key(key),
             count(1) {}

Node* Node::getLeftChild() const {
    return this->leftChild;
}

Node* Node::getRightChild() const {
    return this->rightChild;
}

void Node::setLeftChild(Node *insert) {
    this->leftChild = insert;
}

void Node::setRightChild(Node *insert) {
    this->rightChild = insert;
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