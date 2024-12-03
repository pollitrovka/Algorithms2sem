#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexCount) : adjacencyMatrix(vertexCount, vector<bool>(vertexCount, false)) {}

MatrixGraph::MatrixGraph(const IGraph* graph) : MatrixGraph(graph->VerticesCount()) {
    for (int i = 0; i < graph->VerticesCount(); ++i) {
        vector <int> next;
        graph->GetNextVertices(i, next);
        for (int j = 0; j < next.size(); ++j) {
            AddEdge(i, next[j]);
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    adjacencyMatrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return adjacencyMatrix.size();
}

void MatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    for (int j = 0; j < adjacencyMatrix[vertex].size(); ++j) {
        if (adjacencyMatrix[vertex][j] == true) {
            vertices.push_back(j);
        }
    }
}
void MatrixGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    for (int j = 0; j < adjacencyMatrix[vertex].size(); ++j) {
        if (adjacencyMatrix[j][vertex] == true) {
            vertices.push_back(j);
        }
    }
}