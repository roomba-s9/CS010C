#include "Heap.h"

#include <iostream>

using namespace std;

Heap::Heap() : numItems(0) {}

Heap::~Heap() {
    // go through the heap and delete the items
    // and set them to a nullptr
    for (unsigned i = 0; i < numItems; ++i) {
        delete arr[i];
        arr[i] = nullptr;
    }
}

Heap::Heap(const Heap &other) : numItems(other.numItems) {
    // assign numItems (above) with the amount of items in other
    // then, go through the current Heap and copy from other
    // to the current heap
    for (unsigned i = 0; i < numItems; ++i) {
        arr[i] = new PrintJob(*other.arr[i]);
    }
}

Heap& Heap::operator=(const Heap &other) {
    // if the current heap doesn't equal the other Heap
    if (this != &other) {
        // delete the current contents of the heap
        for (unsigned i = 0; i < numItems; ++i) {
            delete arr[i];
            arr[i] = nullptr;
        }
        numItems = 0;

        // copy contents of other heap to current heap
        for (int i = 0; i < other.numItems; ++i) {
            arr[i] = new PrintJob(*other.arr[i]);
        }
        numItems = other.numItems;
    }
    return *this;
}

void Heap::enqueue(PrintJob *job) {
    // if the heap is full
    if (numItems == MAX_HEAP_SIZE) {
        cout << "Heap full, cannot enqueue" << endl;
        return;
    }
    
    // insert PrintJob at the end of the heap
    arr[numItems] = job;
    numItems++;

    // perlocate up the new PrintJob to satisfy the
    // max-heap requirement
    perlocateUp(numItems - 1, job);
}

void Heap::dequeue() {
    // if the heap is empty
    if (numItems == 0) {
        cout << "Heap empty, cannot dequeue" << endl;
    }

    // swap the root with the last item in the heap
    swap(arr[0], arr[numItems - 1]);
    delete arr[numItems - 1];
    arr[numItems - 1] = nullptr;
    numItems--;

    // fix the max-heap properties by trickling
    // down the new root
    trickleDown(0);
}

PrintJob* Heap::highest() const {
    // if the heap is empty, return a nullptr
    if (numItems == 0) {
        return nullptr;
    }

    // return the first item in the array (highest priority)
    return arr[0];
}

void Heap::print() const {
    // if the heap is empty, don't print anything
    if (numItems == 0) {
        return;
    }

    // print the highest priority item in the heap
    cout << "Priority: "
            << arr[0]->getPriority()
            << ", Job Number: "
            << arr[0]->getJobNumber()
            << ", Number of Pages: "
            << arr[0]->getPages()
            << endl;

}

void Heap::trickleDown(int num) {
    // find the childIndex of the current PrintJob
    int childIndex = 2 * num + 1;
    PrintJob *value = arr[num];

    while (childIndex < numItems) {
        // find the max among the nodes and all the node's children
        PrintJob *maxValue = value;
        int maxIndex = num;
        // for loop to find the largest value of the parent and their respective children's nodes
        for (int i = 0; i < 2 && i + childIndex < numItems; ++i) {
            if (arr[i + childIndex]->getPriority() > maxValue->getPriority()) {
                maxValue = arr[i + childIndex];
                maxIndex = i + childIndex;
            }
        }

        // if the values of the max and the current are the same,
        // we are done trickling down, so we return to end the function
        if (maxValue == value) {
            return;
        }

        // if the maxValue is now different, then swap the values.
        else {
            swap(arr[num], arr[maxIndex]);
            num = maxIndex;
            childIndex = 2 * num + 1;
        }
    }
}

void Heap::perlocateUp(int nodeIndex, PrintJob *job) {
    while (nodeIndex > 0) {
        // find the parent index of the job
        int parentIndex = (nodeIndex - 1) / 2;

        // if it already satisifes the max-heap requirement, then don't do anything
        if (arr[nodeIndex]->getPriority() <= arr[parentIndex]->getPriority()) {
            return;
        }

        // otherwise swap the job and the parent and continue
        // until it satisfies the max-heap requirement
        else {
            swap(arr[nodeIndex], arr[parentIndex]);
            nodeIndex = parentIndex;
        }
    }
}