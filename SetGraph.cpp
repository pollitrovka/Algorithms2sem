#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) : table(vertexCount) {}

void SetGraph::AddEdge(int from, int to) {
    table[from].insert(to);
}

SetGraph::SetGraph(const IGraph* graph) : SetGraph(graph->VerticesCount())
{
    for (int i = 0; i < graph->VerticesCount(); ++i) {
        vector <int> next;
        graph->GetNextVertices(i, next);
        for (int j = 0; j < next.size(); ++j) {
            AddEdge(i, next[j]);
        }
    }
}

int SetGraph::VerticesCount() const {
    return table.size();
}

void SetGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    for (auto i = table[vertex].begin(); i != table[vertex].end(); ++i) {
        vertices.push_back(*i);
    }
}
void SetGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < table.size(); ++i) {
        auto itFind = table[i].find(vertex);
        if (itFind != table[i].end()) {
            vertices.push_back(i);
        }
    }
}