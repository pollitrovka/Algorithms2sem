#ifndef UNTITLED_IGRAPH_H
#define UNTITLED_IGRAPH_H

#include <iostream>
#include <vector>
using namespace std;

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0;
};

#endif
