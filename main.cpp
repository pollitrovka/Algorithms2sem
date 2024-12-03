#include <iostream>
#include <queue>
#include <vector>
using std::queue;
using std::vector;
using std::cin;
using std::cout;

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
    void GetPrevVertices(int, vector<int>&) const;
private:
    vector<vector<int>> adjacencyList;
};

ListGraph::ListGraph(int vertexCount) : adjacencyList(vertexCount) {}

void ListGraph::AddEdge(int from, int to) {
    adjacencyList[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    vertices = adjacencyList[vertex];
}

int BFS(IGraph* graph, int start) {
    queue<int> tops;
    vector<int> cycle(graph->VerticesCount());
    vector<int> color(graph->VerticesCount());
    int length_cycle = 1000;
    cycle[start] = 0;
    color[start] = 1;
    tops.push(start);
    // Если нашли какой-нибудь цикл, он и есть искомый, т.к. используем обход в ширину 
    // (первый цикл = минимальный)
    while ((!tops.empty()) && (length_cycle == 1000)) {
        int vertex = tops.front();
        tops.pop();
        vector<int> next_vertices;
        graph->GetNextVertices(vertex, next_vertices);
        for (int i = 0; i < next_vertices.size(); ++i) {
            if (color[next_vertices[i]] == 0) {
                tops.push(next_vertices[i]);
                cycle[next_vertices[i]] = cycle[vertex] + 1;
                color[next_vertices[i]] = 1;
            }
            else if (color[next_vertices[i]] == 1) {
                length_cycle = cycle[vertex] + cycle[next_vertices[i]] + 1;
            }
            // Если петля
            else if (color[next_vertices[i]] == 2 && next_vertices[i] == vertex) {
                length_cycle = 1;
            }
        }
        color[vertex] = 2;
    }
    return length_cycle;
}

int main() {
    int N, M;
    cin >> N >> M;
    ListGraph graph(N);
    int from, to;
    for (int i = 0; i < M; ++i) {
        cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }
    int length_cycle = 1000;
    for (int i = 0; i < N; ++i) {
        int length = BFS(&graph, i);
        if (length < length_cycle) {
            length_cycle = length;
        }
    }
    if (length_cycle == 1000) {
        length_cycle = -1;
    }
    cout << length_cycle;
    return 0;
}
