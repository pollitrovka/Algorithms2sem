#include "ListGraph.cpp"
#include "MatrixGraph.cpp"
#include "SetGraph.cpp"
#include "ArcGraph.cpp"

int main() {
    cout << "Сколько вершин и ребёр будет в графе?" << endl;
    int verAmount, edgAmount;
    cin >> verAmount >> edgAmount;
    ListGraph listGraph(verAmount);
    cout << "Введите индексы вершин, между которыми есть ребро" << endl;
    for (int i = 0; i < edgAmount; ++i) {
        int from, to;
        cin >> from >> to;
        listGraph.AddEdge(from, to);
    }
    cout << "ListGraph успешно создан!" << endl;
    MatrixGraph matrixGraph(&listGraph);
    cout << "Количество вершин в MatrixGraph " << matrixGraph.VerticesCount() << endl;
    ArcGraph arcGraph(&matrixGraph);
    SetGraph setGraph(&arcGraph);
    cout << arcGraph.VerticesCount() << endl;
    vector<int> next_vert, prev_vert;
    cout << "Потомки какой вершины в ArcGraph хотите узнать?" << endl;
    int u;
    cin >> u;
    cout << "Предки какой вершины в SetGraph хотите узнать?" << endl;
    int v;
    cin >> v;
    arcGraph.GetNextVertices(u, next_vert);
    setGraph.GetPrevVertices(v, prev_vert);
    for (int vertex: next_vert) {
        cout << vertex << " ";
    }
    cout << endl;
    for (int vertex: prev_vert) {
        cout << vertex << " " << endl;
    }
    ListGraph lstGraph(&setGraph);
    cout << "ListGraph успешно создался из SetGraph!";
    return 0;
}
