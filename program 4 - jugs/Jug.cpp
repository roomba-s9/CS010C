#include "Jug.h"

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) : 
    capacityA(Ca),
    capacityB(Cb),
    goal(N),
    costFillA(cfA),
    costFillB(cfB),
    costEmptyA(ceA),
    costEmptyB(ceB),
    costPourAB(cpAB),
    costPourBA(cpBA) 
    {
        // verifying that all the costs are positive
        if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
            invalid = true;
            return; 
        }

        // verifying that 0 < Ca <= Cb
        if (Ca <= 0 || Ca > Cb) {
            invalid = true;
            return;
        }

        // verifying that N <= Cb <= 1000
        if (!(Ca > 0 && Ca <= Cb) ||
            !(Cb >= N && Cb <= 1000)) {
            invalid = true;
            return;
        }

        // construct the graph only if there are valid parameters
        constructGraph(adjList);
    }

Jug::~Jug() {
    // FIXME: complete the destructor
}

/* determines wheter or not there is a solution */
int Jug::solve(string &solution) {
    stringstream ss;

    // if the input values are invalid, set the
    // solution to an empty string and return -1
    if (invalid) {
        solution = "";
        return -1;
    }

    // algorithm to find if the solution exists
    int index = 0;
    bool found = false;
    for (unsigned i = 0; i < adjList.size(); ++i) {
        if (adjList.at(i).currentWater.first == 0 &&
            adjList.at(i).currentWater.second == goal) {
            index = i;
            found = true;
        }
    }

    // if the solution does not exist, end the solve() function
    if (!found) {
        return 0;
    } 
    
    // if the solution exists, find the cheapest way to get there
    else {
        optimizePaths();

        stack<Vertex*> vtxStack;
        Vertex *cur = &adjList.at(index);

        while (cur != 0) {
            vtxStack.push(cur);
            cur = cur->prev;
        }

        while (vtxStack.size() - 1 != 0) {
            cur = vtxStack.top();
            vtxStack.pop();

            Vertex *before = vtxStack.top();

            if (&adjList.at(cur->neighbors[0].first) == before) {
                ss << "fill A" << endl; 
            }

            if (&adjList.at(cur->neighbors[1].first) == before) {
                ss << "fill B" << endl;
            }

            if (&adjList.at(cur->neighbors[2].first) == before) {
                ss << "empty A" << endl;
            }

            if (&adjList.at(cur->neighbors[3].first) == before) {
                ss << "empty B" << endl;
            }

            if (&adjList.at(cur->neighbors[4].first) == before) {
                ss << "pour A B" << endl;
            }

            if (&adjList.at(cur->neighbors[5].first) == before) {
                ss << "pour B A" << endl;
            }
        }
    }
    ss << "success " << adjList.at(index).distance;
    solution = ss.str();

    return 1;
}

/* fills up the first jug */
void Jug::fillA(Vertex &vtx) {
    vtx.currentWater.first = capacityA;
}

/* fills up the second jug */
void Jug::fillB(Vertex &vtx) {
    vtx.currentWater.second = capacityB;
}

/* pours water from jug A to jug B */
/* stops when jug A is empty OR jug B is full (whichever comes first) */
void Jug::pourAB(Vertex &vtx) {
    // ends the function if jug A is empty
    while (vtx.currentWater.first != 0) {
        // ends the function if jug B is full
        if (vtx.currentWater.second == capacityB) {
            return;
        }
        vtx.currentWater.first--;
        vtx.currentWater.second++;
    }
}

/* pours water from jug B to jug A */
/* stops when jug B is empty OR jug A is full (whichever comes first) */
void Jug::pourBA(Vertex &vtx) {
    // ends the function if jug B is empty
    while (vtx.currentWater.second != 0) {
        // ends the function if jug A is full
        if (vtx.currentWater.first == capacityA) {
            return;
        }
        vtx.currentWater.second--;
        vtx.currentWater.first++;
    }
}

/* empties jug A */
void Jug::emptyA(Vertex &vtx) {
    vtx.currentWater.first = 0;
}

/* empties jug B */
void Jug::emptyB(Vertex &vtx) {
    vtx.currentWater.second = 0;
}

/* creates a graph using a vector and an adjacency list */
void Jug::constructGraph(vector<Vertex> &vtx) {
    // foundation = (0, 0) jug
    Vertex foundation;
    Vertex others;
    vtx.push_back(foundation);

    for (unsigned i = 0; i < vtx.size(); ++i) {
        others = vtx.at(i);
        Vertex vtx1 = others;
        Vertex vtx2 = others;
        Vertex vtx3 = others;
        Vertex vtx4 = others;
        Vertex vtx5 = others;
        Vertex vtx6 = others;

        fillA(vtx1);
        fillB(vtx2);
        emptyA(vtx3);
        emptyB(vtx4);
        pourAB(vtx5);
        pourBA(vtx6);

        if (!solnExists(vtx1)) {
            vtx.push_back(vtx1);
        }

        if (!solnExists(vtx2)) {
            vtx.push_back(vtx2);
        }

        if (!solnExists(vtx3)) {
            vtx.push_back(vtx3);
        }

        if (!solnExists(vtx4)) {
            vtx.push_back(vtx4);
        }

        if (!solnExists(vtx5)) {
            vtx.push_back(vtx5);
        }

        if (!solnExists(vtx6)) {
            vtx.push_back(vtx6);
        }

        others.neighbors[0] = pair<int,int>(find(vtx1), costFillA);
        others.neighbors[1] = pair<int,int>(find(vtx2), costFillB);
        others.neighbors[2] = pair<int,int>(find(vtx3), costEmptyA);
        others.neighbors[3] = pair<int,int>(find(vtx4), costEmptyB);
        others.neighbors[4] = pair<int,int>(find(vtx5), costPourAB);
        others.neighbors[5] = pair<int,int>(find(vtx6), costPourBA);

        vtx.at(i) = others;

    }

}

/* finds whether or not a solution exists */
bool Jug::solnExists(Vertex &vtx) {
    for (unsigned i = 0; i < adjList.size(); ++i) {
        if (adjList.at(i).currentWater.first == vtx.currentWater.first &&
            adjList.at(i).currentWater.second == vtx.currentWater.second) {
            return true;
        }
    }
    return false;
}

/* finds the index of the vertex that has the respective capacities in each jug */
int Jug::find(Vertex &vtx) {
    for (unsigned i = 0; i < adjList.size(); ++i) {
        if (adjList.at(i).currentWater.first == vtx.currentWater.first &&
            adjList.at(i).currentWater.second == vtx.currentWater.second) {
            return i;
        }
    }
    return -1;
}

/* dijkstra's shortest path algorithm */
void Jug::optimizePaths() {
    queue<Vertex *> unvisitedQueue;
    
    // initializes all verticies distances to infinity and predecessors to null
    for (unsigned i = 0; i < adjList.size(); ++i) {
        adjList.at(i).distance = INT_MAX;
        adjList.at(i).prev = nullptr;
        unvisitedQueue.push(&adjList.at(i));
    }

    // makes the root vertex distance 0
    adjList.at(0).distance = 0;

    while (!unvisitedQueue.empty()) {
        Vertex *cur = unvisitedQueue.front();
        unvisitedQueue.pop();

        for (unsigned i = 0; i < 6; ++i) {
            int initialPos = cur->neighbors[i].first;
            int initialLength = cur->neighbors[i].second;
            int otherLength = cur->distance + initialLength;
            
            if (otherLength < adjList.at(initialPos).distance) {
                adjList.at(initialPos).distance = otherLength;
                adjList.at(initialPos).prev = cur;
            }
        }
    }
}