#include "Node.h"

Node::Node() : small(""), 
               large(""),
               left(nullptr),
               middle(nullptr),
               right(nullptr),
               parent(nullptr) { }

// parameterized constructor that makes the small key the key
Node::Node(string key) : small(key),
                         large(""),
                         left(nullptr),
                         middle(nullptr),
                         right(nullptr),
                         parent(nullptr) { }

