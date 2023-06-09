#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"

class BSTree {
    private:
        Node *root;
    public:
        BSTree(); // default constructor
        ~BSTree(); // deconstructor
        BSTree(const BSTree &); // copy constructor
        BSTree& operator=(const BSTree &); // copy assignment operator
        void copyHelper(Node *, const Node *);
        void insert(const string &); // inserts a new Node with the key of newString
        void insertHelper(Node *, Node *); // helper function for insert
        void remove(const string &); // removes a node in the tree with a value of key
        void removeHelper(Node *, Node *, const string &); // helper function for remove
        bool search(const string &) const; // returns true if there is a node in the tree that has a value of key
        Node* searchHelper(Node *, const string &) const; // returns the pointer of the node that is being searched
        string largest() const; // returns the node with the largest key in the tree
        string smallest() const; // returns the node with the smallest key in the tree
        int height(const string&) const; // returns the height of a specified node
        int heightHelper(Node *) const; // helper function for height
        void preOrder() const; // prints the tree in preOrder
        void postOrder() const; // prints the tree in postOrder
        void inOrder() const; // prints the tree inOrder
        void inOrder(Node *) const; // helper function for inOrder
        void preOrder(Node *) const; // helper function for preOrder
        void postOrder(Node *) const; // helper function for postOrder
        void removeSubtree(Node *); // function to delete all nodes in a tree.
        bool const isEmpty() const; // returns whether or not if the BST is empty
};

#endif
