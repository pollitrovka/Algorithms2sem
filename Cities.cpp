#include <iostream>
#include <vector>
#include <set>
using std::vector;
using std::pair;
using std::make_pair;
using std::cin;

const int MAX = 1000000000;

struct Graph {
    // Изначально кратчайшие пути будут максимальными
    Graph(int n): countVertex(n), dist(n), short_path_to(n, MAX) {}
    int countVertex;
    vector<vector<pair<int, int>>> dist;
    vector<int> short_path_to;
};

void Dijkstra(int s, Graph& graph) {
    graph.short_path_to[s] = 0;
    // В set храним пару (вершина, текущее кратчайшее расстояние до нее), чтобы на каждой итерации
    // извлекать вершину с наименьшим расстоянием и выполнять релаксации по рёбрам из неё
    std::set <pair<int, int>> curr_min_paths;
    curr_min_paths.insert(make_pair(s, graph.short_path_to[s]));
    while (!curr_min_paths.empty()) {
        int v = curr_min_paths.begin()->first;
        curr_min_paths.erase(curr_min_paths.begin());
        for (size_t j = 0; j < graph.dist[v].size(); ++j) {
            int to = graph.dist[v][j].first;
            int len = graph.dist[v][j].second;
            if (graph.short_path_to[v] + len < graph.short_path_to[to]) {
                curr_min_paths.erase(make_pair(to, graph.short_path_to[to]));
                graph.short_path_to[to] = graph.short_path_to[v] + len;
                curr_min_paths.insert(make_pair(to, graph.short_path_to[to]));
            }
        }
    }
}



int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        graph.dist[a].push_back(make_pair(b, c));
        graph.dist[b].push_back(make_pair(a, c));
    }
    int start = 0, end = 0;
    cin >> start >> end;
    Dijkstra(start, graph);
    std::cout << graph.short_path_to[end];
    return 0;
}

