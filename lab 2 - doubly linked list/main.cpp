#include "IntList.h"

#include <iostream>

using namespace std;

int main () {
    IntList *list = new IntList;

    // // Testing push_front() function
    
    // list->push_front(1);
    // list->push_front(2);
    // list->push_front(3);

    // cout << *list << endl;

    

    // // Testing printReverse() function

    // list->push_front(1);
    // list->push_front(2);
    // list->push_front(3);

    // cout << *list << endl;
    // list->printReverse();
    // cout << endl << endl;

    

    // // Testing pop_front() function.

    // list->push_front(1);
    // list->push_front(2);
    // list->push_front(3);

    // cout << *list << endl;
    // list->printReverse();
    // cout << endl << endl;

    // list->pop_front();

    // cout << *list << endl;
    // list->printReverse();
    // cout << endl << endl;

    // list->pop_front();

    // cout << *list << endl;
    // list->printReverse();
    // cout << endl << endl;

    // list->pop_front();

    // cout << *list << endl;
    // list->printReverse();
    // cout << endl << endl;
    

    // // Testing pop_back() function
    
    // list->push_front(1);
    // list->push_front(2);
    // list->push_front(3);

    // cout << "List in normal order:  " << *list << endl;
    // cout << "List in reverse order: ";
    // list->printReverse();
    // cout << endl << endl;

    // cout << "Calling list->pop_back()" << endl;
    // list->pop_back();
    
    // cout << "List in normal order:  " << *list << endl;
    // cout << "List in reverse order: ";
    // list->printReverse();
    // cout << endl << endl;

    // cout << "Calling list->pop_back()" << endl;
    // list->pop_back();

    // cout << "List in normal order:  " << *list << endl;
    // cout << "List in reverse order: ";
    // list->printReverse();
    // cout << endl << endl;

    // cout << "Calling list->pop_back()" << endl;
    // list->pop_back();

    // cout << "List in normal order:  " << *list << endl;
    // cout << "List in reverse order: ";
    // list->printReverse();
    // cout << endl << endl;
    

    // // Testing push_back() function

    // list->push_back(1);
    // list->push_back(2);
    // list->push_back(3);

    // cout << "List in normal order:  " << *list << endl;
    // cout << "List in reverse order: ";
    // list->printReverse();
    // cout << endl << endl;


    // // Testing operator<< for trailing whitespace
    
    // list->push_front(25);
    // list->push_front(54);
    // cout << "List in forward order: " << *list;

    // Testing try throw catch 

    cout << "Testing pop_back() on an empty list." << endl;
    list->pop_back();
    cout << endl;

    cout << "Testing push_back() for 1, 2, 3, 4, 5" << endl;
    list->push_back(1);
    list->push_back(2);
    list->push_back(3);
    list->push_back(4);
    list->push_back(5);
    cout << "List: " << *list << endl;

    cout << "Testing pop_back()" << endl;
    list->pop_back();
    cout << "List: " << *list << endl << endl;

    cout << "Testing pop_front()" << endl;
    list->pop_front();
    cout << "List: " << *list << endl << endl;

    cout << "Testing pop_back()" << endl;
    list->pop_back();
    cout << "List: " << *list << endl << endl;

    cout << "Testing pop_back()" << endl;
    list->pop_back();
    cout << "List: " << *list << endl << endl;

    cout << "Testing pop_front()" << endl;
    list->pop_front();
    cout << "List: " << *list << endl << endl;

    cout << "Testing pop_front()" << endl;
    list->pop_front();
    cout << "List: " << *list << endl << endl;

    return 1;
}