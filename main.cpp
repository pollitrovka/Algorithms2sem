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
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
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

int BFS(IGraph* graph, int start, int end) {
    queue<int> tops;
    vector<int> way(graph->VerticesCount());
    vector<int> color(graph->VerticesCount());
    vector<int> count(graph->VerticesCount());
    // way[i] - кол-во ребер (путь) между стартовой вершиной и i
    way[start] = 0;
    color[start] = 1;
    // count[i] - количество различных кратчайших путей между start и i
    count[start] = 1;
    tops.push(start);
    while (!tops.empty()) {
        int vertex = tops.front();
        tops.pop();
        vector<int> next_vertices;
        graph->GetNextVertices(vertex, next_vertices);
        for (int i = 0; i < next_vertices.size(); ++i) {
            // В очередь добавляем непосещенные вершины (белые), изменяет цвет
            if (color[next_vertices[i]] == 0) {
                tops.push(next_vertices[i]);
                way[next_vertices[i]] = way[vertex] + 1;
                color[next_vertices[i]] = 1;
                count[next_vertices[i]] = count[vertex];
            }
            // Если соседняя вершина серая (т.е. мин. расстояние до нее от стартовой уже известно) и
            // если расстояние от стартовой до нее равно расстоянию через текущую вершину vertex,
            // то существует еще один кратчайший путь     
            else if (color[next_vertices[i]] == 1) { 
                if (way[next_vertices[i]] == way[vertex] + 1) { 
                    count[next_vertices[i]] += count[vertex]; 
                }
            }
        }
        color[vertex] = 2;
    }
    return count[end];
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
    int start, end;
    cin >> start >> end;
    cout << BFS(&graph, start, end);
    return 0;
}
