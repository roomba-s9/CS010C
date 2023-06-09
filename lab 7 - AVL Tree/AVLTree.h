#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include "Node.h"

class AVLTree {
    private:
        Node *root;
        void copyHelper(Node *, const Node *);
        void insertHelper(Node *, Node *); // helper function for insert
        Node* searchHelper(Node *, const string &) const; // returns the pointer of the node that is being searched
        void removeSubtree(Node *); // function to delete all nodes in a tree.
        bool const isEmpty() const; // returns whether or not if the BST is empty
        int heightHelper(Node *) const; // helper function for height

    public:
        AVLTree(); // default constructor
        ~AVLTree(); // deconstructor
        AVLTree(const AVLTree &); // copy constructor
        AVLTree& operator=(const AVLTree &); // copy assignment operator
        void insert(const string &); // inserts a new Node with the key of newString
        bool search(const string &) const; // returns true if there is a node in the tree that has a value of key
        int height(const string &) const; // returns the height of a specified node

        /* ADDED AVLTREE FUNCTIONS/VARIABLES */
        void printBalanceFactors() const;
        void printBalanceFactors(Node *) const;
        void updateHeights(Node *);
        void updateBalanceFactors(Node *);
        int balanceFactor(Node *);
        void rotate(Node *, Node *);
        void rotateRight(Node *);
        void rotateLeft(Node *);
        bool balanced;

        /* VISUALIZE FUNCTIONS */
        void visualizeTree(const string &);
        void visualizeTree(ofstream &out, Node *);

};

#endif
