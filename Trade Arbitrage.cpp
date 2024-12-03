#include <vector>
#include <iostream>
using std::vector;
using std::cin;
using std::cout;

void ford_bellman(vector<vector<double>>& graph, vector<double>& value) {
    for (int j = 0; j < graph.size() - 1; ++j) {
        for (int v = 0; v < graph.size(); ++v) {
            for (int t = 0; t < graph.size(); ++t) {
                if (graph[t][v] != -1) {
                    if (value[t] != -1 && value[v] < value[t] * graph[t][v]) {
                        value[v] = value[t] * graph[t][v];
                    }
                }
            }
        }
    }
}

bool arbitrage(vector<vector<double>>& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        // Вектор стоимостей
        vector<double> value(graph.size(), -1); 
        value[i] = 1;
        ford_bellman(graph, value);
        // Если после n-1 фазы мы выполним ещё одну фазу, и на ней произойдёт
        // хотя бы одна релаксация, то граф содержит цикл отрицательного веса,
        // достижимый из v; в противном случае, такого цикла нет.
        for (int v = 0; v < graph.size(); ++v) { 
            for (int j = 0; j < graph.size(); ++j) {
                if (graph[j][v] != -1) {
                    if (value[j] != -1 && value[v] < value[j] * graph[j][v]) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int n = 0;
    cin >> n;
    vector<vector<double>> graph(n, vector<double>(n, 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double exchange = 0;
                cin >> exchange;
                graph[i][j] = exchange;
            }
        }
    }
    if (arbitrage(graph)) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    return 0;
}
