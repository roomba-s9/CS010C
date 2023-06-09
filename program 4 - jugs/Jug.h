#ifndef JUG_H
#define JUG_H

#include <queue> // queue ADT from C++ STL
#include <vector> // vector ADT from C++ STL
#include <stack> // stack ADT from C++ STL

#include <string>
#include <climits>
#include <sstream>
#include <iostream>

using namespace std;

struct Vertex {
    /* constructor for a vertex */
    Vertex() : distance(INT_MAX), prev(nullptr) {}

    /* destructor for a vertex */
    ~Vertex() {}

    /* distance the vertex is from the start vertex */
    int distance;

    /* the previous pointer in the graph (BFS Traversal) */
    Vertex *prev;

    /* array of neighboring vertex's position in the graph's
    vector verticies and the cost of the edge to that neighbor */
    pair<int,int> neighbors[6];

    /* the amount of water each jug holds in the vertex */
    pair<int,int> currentWater;
};

class Jug {
 public:
    Jug(int,int,int,int,int,int,int,int,int);
    ~Jug();

    // solve is used to check input and find the solution if one exists
    // returns -1 if invalid inputs. solution set to empty string.
    // returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    // returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);

 private:
    /* functions to deal with the water in the jugs */
    void fillA(Vertex &);
    void fillB(Vertex &);
    void pourAB(Vertex &);
    void pourBA(Vertex &);
    void emptyA(Vertex &);
    void emptyB(Vertex &);
    
    /* misc functions */
    void constructGraph(vector<Vertex> &);
    bool solnExists(Vertex &);
    int find(Vertex &);
    void optimizePaths();
    
    /* variables */
    bool invalid = false;
    int capacityA;
    int capacityB;
    int goal;
    int costFillA;
    int costFillB;
    int costEmptyA;
    int costEmptyB;
    int costPourAB;
    int costPourBA;

    /* adjacency list for the graph */
    vector<Vertex> adjList;
};

#endif