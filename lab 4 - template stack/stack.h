#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

const int MAX_SIZE = 20;

template<typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T>(T data) : data(data), next(nullptr) {}
};

template<typename T>
class stack {
 public:
    stack() : dHead(new Node<T>(T())) {}

    ~stack() {
        while (dHead->next != nullptr) {
            pop();
        }
    }

    void push(T val) { // essentially push_front
        if (size == MAX_SIZE) {
            throw overflow_error("Called push on full stack.");
        }

        Node<T> *temp = new Node<T>(val);
        temp->next = dHead->next;
        dHead->next = temp;
        size++;

        // try {
        //     if (size == MAX_SIZE) {
        //         throw overflow_error("Called push on full stack.");
        //     }
        //     Node<T> *temp = new Node<T>(val);
        //     temp->next = dHead->next;
        //     dHead->next = temp;
        //     size++;
        // }
        // catch (overflow_error &excpt) {
        //     cout << excpt.what();
        // }
    }

    T pop() { // essentially pop_front
        T value;
        if (size == 0) {
            throw out_of_range("Called pop on empty stack.");
        }
        Node<T> *remove = dHead->next;
        value = remove->data;
        dHead->next = dHead->next->next;
        delete remove;
        size--;

        return value;
        // T value;
        // try {
        //     if (size == 0) {
        //         throw out_of_range("Called pop on empty stack.");
        //     }
        //     Node<T> *remove = dHead->next;
        //     value = remove->data;
        //     dHead->next = dHead->next->next;
        //     delete remove;
        //     size--;
        // }
        // catch (out_of_range &excpt) {
        //     cout << excpt.what();
        // }
        // return value;
    }

    T pop_two() {
        string to_return;
        T value1;
        T value2;
        if (size == 0) {
            throw out_of_range("Called pop_two on empty stack.");
        }
        if (size == 1) {
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
        value1 = pop();
        value2 = pop();

        to_return = value1 + ' ' + value2;
        return to_return;
    }

    T top() const {
        if (empty()) {
            throw underflow_error("Called top on empty stack.");
        }
        return dHead->next->data;
    }

    bool empty() const {
        if (dHead->next == nullptr) {
            return true;
        }
        return false;
    }

 private:
    T data;
    int size = 0;
    Node<T> *dHead; // using the head to keep things simple
};

#endif