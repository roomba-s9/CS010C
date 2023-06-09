#include "IntList.h"

IntList::IntList() {
    dHead = new IntNode(0);
    dTail = new IntNode(0);
    dHead->next = dTail;
    dTail->prev = dHead;

    // these are already declared to nullptr or 0 in the constructor for IntNode
    // dHead->prev = nullptr;
    // dTail->next = nullptr;
}

IntList::~IntList() {
    while (!empty()) {
        pop_front();
    }
    // pop_front() doesn't deal with the dummy nodes in the list
    delete dHead;
    delete dTail;
}

void IntList::push_front(const int &x) {
    IntNode *newNode = new IntNode(x);
    IntNode *firstNode = dHead->next;
    newNode->next = dHead->next;
    newNode->prev = dHead;
    dHead->next = newNode;
    firstNode->prev = newNode;
}

void IntList::pop_front() {
    try {
        if (empty()) throw runtime_error("List is empty.");

        IntNode *remove = dHead->next;
        dHead->next = remove->next;
        remove->next->prev = dHead;
        delete remove;
    }
    catch (runtime_error& excpt) {
        cout << "Error: " << excpt.what() << endl;
    }
}

void IntList::push_back(const int &x) {
    IntNode *temp = new IntNode(x);
    temp->next = dTail;
    temp->prev = dTail->prev;
    dTail->prev->next = temp;
    dTail->prev = temp;
}

void IntList::pop_back() {
    try {
        if (empty()) throw runtime_error("List is empty");

        IntNode *remove = dTail->prev;
        IntNode *before = remove->prev;
        IntNode *after = remove->next;
        before->next = after;
        after->prev = before;
        delete remove;
    }
    catch (runtime_error& excpt) {
        cout << "Error: " << excpt.what() << endl;
    }
}

bool IntList::empty() const {
    return (dHead->next == dTail);
}

ostream & operator<<(ostream &out, const IntList &list) {
    for (IntNode *temp = list.dHead->next; temp != list.dTail; temp = temp->next) {
        out << temp->data;
        if (temp->next != list.dTail) {
            out << " ";
        }
    }

    return out;
}

void IntList::printReverse() const {
    for (IntNode *temp = dTail->prev; temp != dHead; temp = temp->prev) {
        cout << temp->data;
        if (temp->prev != dHead) {
            cout << " ";
        }
    }
}