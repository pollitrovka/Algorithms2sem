#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertex_count) : pairs(), count(vertex_count) {}

ArcGraph::ArcGraph(const IGraph* graph) : ArcGraph(graph->VerticesCount()) {
    for (int i = 0; i < graph->VerticesCount(); ++i) {
        vector<int> next;
        graph->GetNextVertices(i, next);
        for (int vertex: next) {
            AddEdge(i, vertex);
        }
    }

}

void ArcGraph::AddEdge(int from, int to) {
    pairs.push_back(make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
    return count;
}

void ArcGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first == vertex) {
            vertices.push_back(pairs[i].second);
        }
    }
}
void ArcGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i].second == vertex) {
            vertices.push_back(pairs[i].first);
        }
    }
}