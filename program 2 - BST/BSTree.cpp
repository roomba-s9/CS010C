#include "BSTree.h"

#include <iostream>

BSTree::BSTree() : root(nullptr) { }

BSTree::~BSTree() {
    removeSubtree(root);
}

// copy constructor
BSTree::BSTree(const BSTree &other) : root(nullptr) {
    if (other.root != nullptr) {
        root = new Node(*other.root);
        copyHelper(root, other.root);
    }
}

// copy assignment operator
BSTree& BSTree::operator=(const BSTree &other) {
    if (this != &other) {
        // clear the current tree
        removeSubtree(root);
        root = nullptr;

        // copy the other tree
        if (other.root != nullptr) {
            root = new Node(*other.root);
            copyHelper(root, other.root);
        }
    }
    return *this;
}

void BSTree::copyHelper(Node *curr, const Node *other) {
    // if the other tree is empty, don't do anything
    if (other == nullptr) {
        return;
    }
    
    // if the other tree has a left child, make a new node for the current tree
    // and insert it into the same place as other's tree
    if (other->getLeftChild() != nullptr) {
        Node *insert = new Node(*other->getLeftChild());
        curr->setLeftChild(insert);
        // recursively call for all the left children
        copyHelper(curr->getLeftChild(), other->getLeftChild());
    }

    // if the other tree has a right child, make a new node for the current tree
    // and insert it into the same place as other's tree
    if (other->getRightChild() != nullptr) {
        Node *insert = new Node(*other->getRightChild());
        curr->setRightChild(insert);
        // recursively call for all the right children
        copyHelper(curr->getRightChild(), other->getRightChild());
    }
}

void BSTree::removeSubtree(Node *node) {
    if (node != nullptr) {
        // recursively visits every singular node that exists in the tree
        if (node->getLeftChild() != nullptr) {
            removeSubtree(node->getLeftChild());
        }
        if (node->getRightChild() != nullptr) {
            removeSubtree(node->getRightChild());
        }
        // deletes the node and then goes back up to the parent node and its right
        // child if it exists and repeats
        delete node;
    }
}

void BSTree::insert(const string &newString) {
    // if the node already exists, increment count
    if (search(newString)) {
        Node *inc = searchHelper(root, newString);
        inc->addCount();
        return; // ends the function
    }

    // create a new node with the value of newString
    Node *newNode = new Node(newString);

    // if the tree is empty, the node to be inserted is the root.
    if (root == nullptr) {
        root = newNode;
    } 

    // otherwise, call the helper function
    else { 
        insertHelper(root, newNode);
    }
}

void BSTree::insertHelper(Node *parent, Node *toInsert) {
    // if the value is smaller than the parent, go to the left subtree
    if (toInsert->getKey() < parent->getKey()) {
        // if there isn't a left child, then toInsert is now the left child.
        if (parent->getLeftChild() == nullptr) {
            parent->setLeftChild(toInsert);
        } 
        
        // if there already is a left child, recursively go down to the subtree 
        // of the left child.
        else {
            insertHelper(parent->getLeftChild(), toInsert);
        }
    }

    // if the value is larger than the parent, go to the right subtree
    else {
        // if there isn't a right child, then toInsert is now the right child.
        if (parent->getRightChild() == nullptr) {
            parent->setRightChild(toInsert);
        } 
        
        // if there already is a right child, recursively go down to the subtree
        // of the right child
        else {
            insertHelper(parent->getRightChild(), toInsert);
        }
    }
}

bool BSTree::search(const string &key) const {
    // creates a bool variable to keep track if the key is found
    bool found = false;

    // calls the recursive helper function
    Node *search = searchHelper(root, key);

    // if search exists, then we found the key
    if (search != nullptr) {
        found = true;
    }

    return found;
}

Node* BSTree::searchHelper(Node *newRoot, const string &key) const {
    // case 1: the node cannot be found
    if (newRoot == nullptr) {
        return nullptr;
    }

    // case 2: the node is found
    if (newRoot->getKey() == key) {
        return newRoot;
    }
    
    // recursive call to traverse the tree
    if (key < newRoot->getKey()) {
        return searchHelper(newRoot->getLeftChild(), key);
    } else {
        return searchHelper(newRoot->getRightChild(), key);
    }

}

void BSTree::remove(const string &key) {
    // if a node containing the key already exists and the count is greater than 1
    Node *temp = searchHelper(root, key);
    if (temp != nullptr && temp->getCount() > 1) {
        temp->subCount();
        return;
    }

    // if there is only a count of 1 in the node
    // that we want to remove
    removeHelper(nullptr, root, key);

}

void BSTree::removeHelper(Node *par, Node *cur, const string &key) {
    // if the node doesn't exist, don't do anything.
    if (cur == nullptr) {
        return;
    }

    // search the tree for the key value
    if (key < cur->getKey()) {
        removeHelper(cur, cur->getLeftChild(), key);
    } else if (key > cur->getKey()) {
        removeHelper(cur, cur->getRightChild(), key);
    }

    // node is found
    else if (key == cur->getKey()) {
        // case 1: removing a leaf
        if (cur->getLeftChild() == nullptr && cur->getRightChild() == nullptr) {
            // if the node is the root, make the root null
            if (cur == root) {
                root = nullptr;
            } else if (cur == par->getLeftChild()) { // if the node is the left child of the parent, remove that child.
                par->setLeftChild(nullptr);
            } else if (cur == par->getRightChild()) { // if the node is the right child of the parent, remove that child.
                par->setRightChild(nullptr);
            }
            delete cur;
        }
    
        // case 2: removing a node with only a right child
        else if (cur->getLeftChild() == nullptr) {
            Node *suc = cur->getRightChild();
            // find the successor (leftmost of right subtree)
            while (suc->getLeftChild() != nullptr) {
                suc = suc->getLeftChild();
            }
            // copy the data from suc to cur
            cur->copyData(suc);
            // recursively delete the suc
            removeHelper(cur, cur->getRightChild(), suc->getKey());
        }

        // case 3 : removing a node with two children or only a left child.
        else {
            Node *suc = cur->getLeftChild();
            // find the successor (rightmost of left subtree)
            while (suc->getRightChild() != nullptr) {
                suc = suc->getRightChild();
            }
            // copy the data from suc to cur
            cur->copyData(suc);
            // recursively delete the suc
            removeHelper(cur, cur->getLeftChild(), suc->getKey());
        }
    }
}

int BSTree::height(const string &key) const {
    Node *node = searchHelper(root, key);
    // if the node is not found, return -1
    if (node == nullptr) {
        return -1;
    }
    // otherwise, call the helper function
    return heightHelper(node);
}

int BSTree::heightHelper(Node *node) const {
    // if the node doesn't exist,
    if (node == nullptr) {
        // return -1 to indicate that the height of a non-existent node is -1
        return -1;
    }

    // recursively calculate the heights of the left and right subtrees
    int leftHeight = heightHelper(node->getLeftChild());
    int rightHeight = heightHelper(node->getRightChild());
    
    // the height of the current node is 1 + the max height of its left and right subtrees
    return 1 + max(leftHeight, rightHeight);
}

string BSTree::largest() const {
    // return an empty string if the tree is empty
    if (isEmpty()) {
        return "";
    } else {
        // traverse the rightmost child to find the max value
        Node *largest = root;
        while (largest->getRightChild() != nullptr) {
            largest = largest->getRightChild();
        }
        return largest->getKey();
    }
}

string BSTree::smallest() const {
    // return an empty string if the tree is empty
    if (isEmpty()) {
        return "";
    } else {
        // traverse the leftest of the children to find the min value
        Node *smallest = root;
        while (smallest->getLeftChild() != nullptr) {
            smallest = smallest->getLeftChild();
        }
        return smallest->getKey();
    }
}

bool const BSTree::isEmpty() const {
    // if the root is null, then the tree is empty.
    if (root == nullptr) {
        return true;
    } 

    return false;
}

void BSTree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void BSTree::preOrder(Node *node) const {
    if (node == nullptr) return;
    cout << node->getKey() << '(' << node->getCount() << ')' << ", ";
    preOrder(node->getLeftChild());
    preOrder(node->getRightChild());
}

void BSTree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void BSTree::postOrder(Node *node) const {
    if (node == nullptr) return;
    postOrder(node->getLeftChild());
    postOrder(node->getRightChild());
    cout << node->getKey() << '(' << node->getCount() << ')' << ", ";
}

void BSTree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void BSTree::inOrder(Node *node) const {
    if (node == nullptr) return;
    inOrder(node->getLeftChild());
    cout << node->getKey() << '(' << node->getCount() << ')' << ", ";
    inOrder(node->getRightChild());
}