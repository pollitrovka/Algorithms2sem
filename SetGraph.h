#ifndef UNTITLED_SETGRAPH_H
#define UNTITLED_SETGRAPH_H

#include <unordered_set>
#include "IGraph.h"

class SetGraph : public IGraph {
public:
    SetGraph(int);
    SetGraph(const IGraph*);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const;
private:
    vector<std::unordered_set<int> > table;
};

#endif
