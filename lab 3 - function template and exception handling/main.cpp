#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

vector<char> createVector();

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

template<typename T>
void selection_sort(vector<T> &vals);

template<typename T>
T getElement(vector<T> &vals, const int &index);

int main() {

    // Part A Testing
    vector<int> list = {1, 0, 2, 9, 3, 8, 4, 7, 5, 6};
    cout << "List:        ";
    for (auto x : list) {
        cout << x << " ";
    }

    cout << endl;

    cout << "Sorted list: ";
    selection_sort(list);

    for (auto x : list) {
        cout << x << " ";
    }

    cout << endl;

    // Part B Testing
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;
        curChar = getElement(vals, index);
        cout << "Element located at " << index << ": is " << curChar << endl;
    }

    return 0;
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    for (unsigned i = index; i < vals.size(); ++i) {
        if (vals.at(i) < vals.at(index)) {
            index = i;
        }
    }
    return index;
}

template<typename T>
void selection_sort(vector<T> &vals) {  
    for (unsigned i = 0; i < vals.size(); ++i) { // goes through the list and swaps the current value with the lowest value
        unsigned minIndex = min_index(vals, i);
        if (minIndex != i) {
            swap(vals.at(i), vals.at(minIndex));
        }
    }
}

template<typename T>
T getElement(vector<T> &vals, const int &index) {
    try {
        if (index < 0 || index >= static_cast<int>(vals.size())) {
            throw out_of_range("out of range exception occurred");
        }
        return vals.at(index);
    }
    catch (out_of_range &excpt) {
        cout << excpt.what() << endl;
    }
    return 1;
}