#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;

struct Edge {
    size_t from, to, weight;
    Edge () {}
};

class DSU {
public:
    DSU(size_t);
    size_t findRoot(size_t);
    void unite(size_t, size_t);
private:
    vector<size_t> parent;
};

DSU::DSU(size_t verticesCount){
    parent.resize(verticesCount);
    for (size_t i = 0; i < verticesCount; ++i) {
        // Изначально каждая вершина является "деревом"
        parent[i] = i;
    }
}

size_t DSU::findRoot(size_t vertex) {
    if (vertex == parent[vertex]) {
        return vertex;
    }
    size_t root = findRoot(parent[vertex]);
    // Сжатие пути
    parent[vertex] = root;
    return root;
}
void DSU::unite(size_t firstVertex, size_t secondVertex) {
    const size_t firstRoot = findRoot(firstVertex);
    const size_t secondRoot = findRoot(secondVertex);
    // Если вершины из разных "деревьев"
    if (firstRoot != secondRoot) {
        parent[secondRoot] = firstRoot;
    }
}

struct Compare {
    bool operator() (const Edge& firstEdge, const Edge& secondEdge) const {
        return firstEdge.weight < secondEdge.weight;
    }
};

vector<Edge> buildSpanningTree(size_t verticesCount, const vector<Edge>& edges) {
    vector<Edge> sortedEdges = edges;
    // Рассматриваем вершины в порядке возрастания
    sort(sortedEdges.begin(), sortedEdges.end(), Compare());
    DSU dsu(verticesCount);
    vector<Edge> spanningTree;
    // Пока не останется единственного дерева
    for (const Edge &edge: sortedEdges) {
        if (dsu.findRoot(edge.from) != dsu.findRoot(edge.to)) {
            dsu.unite(edge.from, edge.to);
            spanningTree.push_back(edge);
        }
    }
    return spanningTree;
}

size_t countSpanningTreeWeight(const vector<Edge>& edges) {
    size_t spanningTreeWeight = 0;
    for (const Edge &edge: edges) {
        spanningTreeWeight += edge.weight;
    }
    return spanningTreeWeight;
}

int main () {
    size_t verticesCount, edgesCount;
    std::cin >> verticesCount >> edgesCount;
    vector<Edge> edges(edgesCount);
    for (Edge &edge: edges) {
        std::cin >> edge.from >> edge.to >> edge.weight;
        --edge.from;
        --edge.to;
    }
    vector<Edge> spanningTree = buildSpanningTree(verticesCount, edges);
    size_t spanningTreeWeight = countSpanningTreeWeight(spanningTree);
    std::cout << spanningTreeWeight << std::endl;
    return 0;
}
