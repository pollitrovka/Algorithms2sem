#include <iostream>
#include <vector>
#include <algorithm>


// Перед k-ой фазой величина d[i][j] равна длине кратчайшего пути из вершины i в j,
// при этом этому пути разрешается заходить только в вершины с номерами, не большими k
void floyd(std::vector<std::vector<int>>& graph) {
    for (int k = 0; k < graph.size(); ++k) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    return;
}


int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = 0;
            std::cin >> x;
            graph[i].push_back(x);
        }
    }
    floyd(graph);
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            std::cout << graph[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}

