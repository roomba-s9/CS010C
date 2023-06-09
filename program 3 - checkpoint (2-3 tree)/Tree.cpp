#include "Tree.h"

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    // not complete
}

Tree::Tree(const Tree &other) : root(nullptr) {
    // not complete
}

Tree& Tree::operator=(const Tree &other) {
    // not complete
    return *this;
}


void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void Tree::preOrder(Node *node) const {
    if (node == nullptr) return;

    cout << node->small << ", ";

    preOrder(node->left);

    if (node->large != "") {
        cout << node->large << ", ";
    }

    preOrder(node->middle);
    preOrder(node->right);
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void Tree::inOrder(Node *node) const {
    if (node == nullptr) return;
    
    if (isLeaf(root)) {
        cout << node->small << ", ";
        if (node->large != "") {
        cout << node->large << ", ";
        }
    } else if (!isFull(root)) {
        inOrder(node->left);
        cout << node->small << ", ";
        if (node->large != "") {
        cout << node->large << ", ";
        }
        inOrder(node->middle);
    } else {
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->middle);
        if (node->large != "") {
        cout << node->large << ", ";
        }
        inOrder(node->right);
    }
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void Tree::postOrder(Node *node) const {
    if (node == nullptr) return;

    postOrder(node->left);
    postOrder(node->middle);

    cout << node->small << ", ";

    postOrder(node->right);

    if (node->large != "") {
        cout << node->large << ", ";
    }
    
}

void Tree::remove(const string &toRemove) {
    // if the value we want to remove doesn't exist, don't do anything
    if (!search(toRemove)) {
        return;
    }

    // call the recursive removeHelper function
    removeHelper(root, toRemove);
}

void Tree::removeHelper(Node *node, const string &toRemove) {
    // if the key we need to remove is in the current node
    if (node->small == toRemove || node->large == toRemove) {
        // if the node is a root and leaf
        if (isLeaf(node) && node->parent == nullptr) {
            // if there is only one key in the node
            if (!isFull(node)) {
                delete node;
                root = nullptr;
                return;
            } 

            // if there are two keys in the node
            else {
                // if we need to remove the larger key
                if (node->large == toRemove) {
                    node->large = "";
                }

                // if we need to remove the smaller key
                else {
                    node->small = node->large;
                    node->large = "";
                }
            }
        }

        // if the node is a root (but not a leaf)
        else if (!isLeaf(node) && node->parent == nullptr) {
            // if there is only one value in the node
            if (!isFull(node)) {
                node->small = node->left->small;
                node->large = node->middle->small;
                node->left = nullptr;
                node->middle = nullptr;
                root = node;
            }
        }

        // if the node is a leaf (and not a root)
        else if (isLeaf(node)) {
            if (!isFull(node)) {
                // if the parent's left pointer is the node
                if (node->parent->left == node) {
                    delete node;
                    // makes the left pointer of the parent null (we are removing that node)
                    node->parent->left = nullptr;

                    // to keep the balance of the 2-3 tree, we have to move the middle pointer of the parent
                    // into the parent node.
                    node->parent->large = node->parent->middle->small;
                    node->parent = root;
                    node->parent->middle = nullptr;
                } else if (node->parent->middle == node) {
                    delete node;
                    // makes the middle pointer of the parent null (we are removing that node)
                    node->parent->middle = nullptr;

                    // to keep the balance of the 2-3 tree, we have to move the left pointer of the parent
                    // into the parent node.
                    node->parent->large = node->parent->small;
                    node->parent->small = node->parent->left->small;
                    node->parent = root;
                    node->parent->left = nullptr;
                }
            } else if (isFull(node)) {
                // we just need to remove a key in the node if there are two values, no need to rewire potiners
                if (node->small == toRemove) {
                    node->small = node->large;
                    node->large = "";
                } else {
                    node->large = "";
                }
            }
            
        }

        return;

    } 
    
    // if the key we need to remove is not in the current node, traverse through the respective subtree
    else if (toRemove < node->small) {
        return removeHelper(node->left, toRemove);
    } else if (node->large == "" || toRemove < node->large) {
        return removeHelper(node->middle, toRemove);
    } else {
        return removeHelper(node->right, toRemove);
    }
}

bool Tree::search(const string &toSearch) const {
    return searchHelper(root, toSearch);
}

bool Tree::searchHelper(Node *subtree, const string &toSearch) const {
    bool found = false;

    // start traversing through the tree
    if (subtree != nullptr) {
        // if the current node has the value, make found = true
        if (subtree->small == toSearch || subtree->large == toSearch) {
            found = true;
        }
        // all other cases:

        // case 1 : if toSearch is smaller than the small value,
        // recursively call searchHelper on the left subtree
        else if (toSearch < subtree->small) {
            return searchHelper(subtree->left, toSearch);
        }
        
        // case 2 : if toSearch is smaller than the large value
        // or the large value doesn't exist
        // recursively call searchHelper on the middle subtree
        else if (subtree->large == "" || toSearch < subtree->large) {
            return searchHelper(subtree->middle, toSearch);
        }

        // case 3 : if toSearch is larger than both values
        // recursively call searchHelper on the right subtree
        else {
            return searchHelper(subtree->right, toSearch);
        }
    }
    return found;
}

void Tree::insert(const string &toInsert) {
    insertHelper(root, toInsert);
}

void Tree::insertHelper(Node *node, const string &toInsert) {
    // if the node already exists, don't do anything
    if (search(toInsert)) {
        return;
    }

    // if the tree is empty
    if (root == nullptr) {
        // allocate memory for a new node
        Node *newNode = new Node(toInsert);
        root = newNode;
        return;
    }

    // traverse the tree to the leaf
    if (!isLeaf(node)) {
        // if toInsert is smaller than small, go to the left child
        if (toInsert < node->small) {
            return insertHelper(node->left, toInsert);
        }

        // if toInsert is smaller than large value or large value doesn't exist
        else if (node->large == "" || toInsert < node->large) {
            return insertHelper(node->middle, toInsert);
        }

        // if toInsert is larger than both values
        else {
            return insertHelper(node->right, toInsert);
        }
    }

    // if the node is a leaf and it is not full
    if (isLeaf(node) && !isFull(node)) {
        // if toInsert is larger than the current key
        if (toInsert > node->small) {
            node->large = toInsert;
        }
        
        // otherwise, move small to large and insert the new key
        // into small.
        else {
            node->large = node->small;
            node->small = toInsert;
        }
        return;
    }
    
    // if the node is a leaf and it is full
    if (isLeaf(node) && isFull(node)) {
        // we need to find the middle value of the three values
        // and move that value to the parent.
        splitAndInsert(node, node->parent, toInsert);
        return;
    }

}

void Tree::splitAndInsert(Node *currNode, Node *nodeParent, const string &toInsert) {
    // put the middle node into the parent
    
    /* THREE CASES */

    // first case: parent does not exist
    if (nodeParent == nullptr) {
        // find the values to split into 2 new and different nodes

        if (toInsert < currNode->small) {
            // create a new parent and middle node
            Node *newParent = new Node(currNode->small);
            Node *newMiddle = new Node(currNode->large);

            // update parent and middle pointers
            currNode->parent = newParent;
            newMiddle->parent = newParent;

            // update current node's values
            currNode->small = toInsert;
            currNode->large = "";

            // update parent's left and middle pointers
            newParent->left = currNode;
            newParent->middle = newMiddle;

            // set the new parent as the root
            root = newParent;
        } 
        
        else if (toInsert > currNode->large) {
            // create a new parent node and a new middle node
            Node *newParent = new Node(currNode->large);
            Node *newMiddle = new Node(toInsert);

            // update parent and middle pointers
            currNode->parent = newParent;
            newMiddle->parent = newParent;

            // update current node's values
            currNode->large = "";

            // update parent's left and middle pointers
            newParent->left = currNode;
            newParent->middle = newMiddle;

            // set the new parent as the root
            root = newParent;
        }
        
        else {
            // create a new parent node and a new middle node
            Node *newParent = new Node(toInsert);
            Node *newMiddle = new Node(currNode->large);

            // update parent and middle pointers
            currNode->parent = newParent;
            newMiddle->parent = newParent;

            // update current node's values
            currNode->large = "";

            // update parent's left and middle pointers
            newParent->left = currNode;
            newParent->middle = newMiddle;

            // set the new parent as rhe root
            root = newParent;
        }
    }

    // second case: parent is not full
    else if (!isFull(nodeParent)) {
        // find the middle key that needs to move up to the parent
        if (toInsert < currNode->small) { 
            // moving the middle key up to the parent
            nodeParent->large = currNode->small;

            // creating a new right node and rewiring pointers
            Node *newRight = new Node(currNode->large);
            newRight->parent = nodeParent;
            nodeParent->right = newRight;

            // updating the current node's values
            currNode->large = "";

        } 
        
        else if (toInsert > currNode->large) {
            // moving the middle key up to the parent
            nodeParent->large = currNode->large;

            // creating a new right node and rewiring pointers
            Node *newRight = new Node(toInsert);
            newRight->parent = nodeParent;
            nodeParent->right = newRight;

            // updating the current node's values
            currNode->large = "";

        }
        
        else {
            // moving the middle key up to the parent
            nodeParent->large = toInsert;

            // creating a new right node and rewiring pointers
            Node *newRight = new Node(currNode->large);
            newRight->parent = nodeParent;
            nodeParent->right = newRight;

            // updating the current node's values
            currNode->large = "";

        }

        return;
    }

    // third case: parent is full
    else if (isFull(nodeParent)) {
        // FIXME: not complete
    }

}

bool Tree::isLeaf(Node *node) const {
    if (node->left == nullptr && node->middle == nullptr && node->right == nullptr) {
        return true;
    }
    return false;
}

bool Tree::isFull(Node *node) const {
    if (node->small != "" && node->large != "") {
        return true;
    }
    return false;
}
