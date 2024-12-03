#ifndef UNTITLED_ARCGRAPH_H
#define UNTITLED_ARCGRAPH_H

#include "IGraph.h"
#include <utility>

class ArcGraph : public IGraph {
public:
    ArcGraph (int);
    void AddEdge(int, int);
    ArcGraph (const IGraph*);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
    void GetPrevVertices(int, vector<int>&) const;
private:
    vector<pair<int, int>> pairs;
    const int count;
};

#endif
