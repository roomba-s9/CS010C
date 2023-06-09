#include "AVLTree.h"

#include <iostream>
#include <fstream>

AVLTree::AVLTree() : root(nullptr),
                     balanced(true) { }

AVLTree::~AVLTree() {
    // call the removeSubtree helper function to
    // deconstruct the AVLTree
    removeSubtree(root);
}

// copy constructor
AVLTree::AVLTree(const AVLTree &other) : root(nullptr) {
    // if the tree you want to copy over is empty, don't do anything
    if (other.root != nullptr) {
        // otherwise, you make a new node equal to the other node's root.
        root = new Node(*other.root);
        // recursively call the copyHelper function to copy the other tree
        // over to the current tree
        copyHelper(root, other.root);
    }
}

// copy assignment operator
AVLTree& AVLTree::operator=(const AVLTree &other) {
    // if the tree you want to assign have different values --
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

void AVLTree::copyHelper(Node *curr, const Node *other) {
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

void AVLTree::removeSubtree(Node *node) {
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

bool AVLTree::search(const string &key) const {
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

Node* AVLTree::searchHelper(Node *newRoot, const string &key) const {
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

int AVLTree::height(const string &key) const {
    Node *node = searchHelper(root, key);
    // if the node is not found, return -1
    if (node == nullptr) {
        return -1;
    }
    // otherwise, call the helper function
    return heightHelper(node);
}

int AVLTree::heightHelper(Node *node) const {
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

bool const AVLTree::isEmpty() const {
    // if the root is null, then the tree is empty.
    if (root == nullptr) {
        return true;
    } 

    return false;
}

void AVLTree::insertHelper(Node *parent, Node *toInsert) {
    // if the value is smaller than the parent, go to the left subtree
    if (toInsert->getKey() < parent->getKey()) {
        // if there isn't a left child, then toInsert is now the left child.
        if (parent->getLeftChild() == nullptr) {
            parent->setLeftChild(toInsert);
            toInsert->setParent(parent);
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
            toInsert->setParent(parent);
        } 
        
        // if there already is a right child, recursively go down to the subtree
        // of the right child
        else {
            insertHelper(parent->getRightChild(), toInsert);
        }
    }

}

/* ADDED OR MODIFIED AVL FUNCTIONS */

void AVLTree::insert(const string &newString) {
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

    // update the heights of the nodes in the tree
    updateHeights(root);
    
    // update the balance factors of the nodes in the tree
    updateBalanceFactors(root);

    visualizeTree("before.txt");

    // check if the tree is unbalanced (need to rotate)
    if (!balanced) {

        Node *inbalanced = newNode;

        while (!(inbalanced->balFactor == 2 || inbalanced->balFactor == -2)) {
            inbalanced = inbalanced->getParent();
        }

        rotate(inbalanced, newNode);

        // reupdate the heights of the nodes and the balance factors in the tree
        updateHeights(root);
        updateBalanceFactors(root);

        visualizeTree("after.txt");
        
    }

}

void AVLTree::rotate(Node *pivot, Node *inserted) {
    // 4 cases:
    // ... 1 - left left case
    if (inserted->getKey() < pivot->getKey() && inserted->getKey() < pivot->getLeftChild()->getKey()) {
        rotateRight(pivot);
    }
    // ... 2 - left right case (needs two rotations)
    else if (inserted->getKey() < pivot->getKey() && inserted->getKey() > pivot->getLeftChild()->getKey()) {
        rotateLeft(pivot->getLeftChild());
        rotateRight(pivot);
    }
    // ... 3 - right right case
    else if (inserted->getKey() > pivot->getKey() && inserted->getKey() > pivot->getRightChild()->getKey()) {
        rotateLeft(pivot);
    }
    // ... 4 - right left case (needs two rotations)
    else if (inserted->getKey() > pivot->getKey() && inserted->getKey() < pivot->getRightChild()->getKey()) {
        rotateRight(pivot->getRightChild());
        rotateLeft(pivot);
    }
    
    balanced = true;
}

void AVLTree::rotateRight(Node *node) {
    Node *leftChild = node->getLeftChild();
    Node *leftRightChild = leftChild->getRightChild();
    Node *parent = node->getParent();

    // update the parent's child reference
    if (parent != nullptr) {
        if (parent->getLeftChild() == node) {
            parent->setLeftChild(leftChild);
        } else {
            parent->setRightChild(leftChild);
        }
    } else { // if the node is the root
        root = leftChild;
        root->setParent(nullptr);
    }

    // update the node and its left child
    leftChild->setRightChild(node);
    node->setParent(leftChild);
    node->setLeftChild(leftRightChild);

    if (leftRightChild != nullptr) {
        leftRightChild->setParent(node);
    }

    leftChild->setParent(parent);
}

void AVLTree::rotateLeft(Node *node) {
    Node *rightChild = node->getRightChild();
    Node *rightLeftChild = rightChild->getLeftChild();
    Node *parent = node->getParent();

    // update the parent's child reference
    if (parent != nullptr) {
        if (parent->getLeftChild() == node) {
            parent->setLeftChild(rightChild);
        } else { // if the node is the root
            parent->setRightChild(rightChild);
        }
    } else {
        root = rightChild;
        root->setParent(nullptr);
    }

    // update the node and its right child
    rightChild->setLeftChild(node);
    node->setParent(rightChild);
    node->setRightChild(rightLeftChild);

    if (rightLeftChild != nullptr) {
        rightLeftChild->setParent(node);
    }

    rightChild->setParent(parent);
}

void AVLTree::updateBalanceFactors(Node *node) {
    if (node == nullptr) {
        return;
    }

    // traverses through the AVLTree inOrder to update the balance factors
    // using the balanceFactor(Node *) function
    updateBalanceFactors(node->getLeftChild());
    node->balFactor = balanceFactor(node);
    updateBalanceFactors(node->getRightChild());

}

int AVLTree::balanceFactor(Node *node) {
    int lSubtreeHeight;
    int rSubtreeHeight;
    int bal;
    
    // if either of the children are null
    if (node->getLeftChild() == nullptr || node->getRightChild() == nullptr) {
        // if both children are null, the balance factor is 0
        if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
            bal = 0;
        }
        
        // if the right child is null, the balance factor is going to be
        // the left subtree height + 1
        else if (node->getRightChild() == nullptr) {
            bal = height(node->getLeftChild()->getKey()) + 1;
        }

        // if the left child is null, the balance factor is going to be
        // -1 subtracted by the right subtree's height
        else if (node->getLeftChild() == nullptr) {
            bal = -1 - height(node->getRightChild()->getKey());
        }
        
    } 
    
    // if both children exist
    else {
        lSubtreeHeight = height(node->getLeftChild()->getKey());
        rSubtreeHeight = height(node->getRightChild()->getKey());
        bal = lSubtreeHeight - rSubtreeHeight;
    }

    // if any updated bal is not -1, 0, or 1, the tree is not balanced
    if (!(bal >= -1 && bal <= 1)) {
        // update the public balanced variable to rebalance the tree in the 
        // insert() function
        balanced = false;
    }

    return bal;

}

void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *node) const {
    if (node == nullptr) return;

    // prints the key and the balance factor of each node in order
    printBalanceFactors(node->getLeftChild());
    cout << node->getKey() << '(' << node->balFactor << ')' << ", ";
    printBalanceFactors(node->getRightChild());
}

void AVLTree::updateHeights(Node *node) {
    if (node == nullptr) return;

    // traverses through the whole tree (in this case, we traverse in order)
    // and updates the height of each node
    updateHeights(node->getLeftChild());
    node->height = height(node->key);
    updateHeights(node->getRightChild());

}

/* VISUALIZE FUNCTIONS */

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getLeftChild()){
            visualizeTree(outFS,n->getLeftChild());
            outFS<<n->getKey() <<" -> " <<n->getLeftChild()->getKey()<<";"<<endl;    
        }

        if(n->getRightChild()){
            visualizeTree(outFS,n->getRightChild());
            outFS<<n->getKey() <<" -> " <<n->getRightChild()->getKey()<<";"<<endl;    
        }
    }
}