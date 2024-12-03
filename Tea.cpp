#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::make_pair;
using std::vector;
using std::numeric_limits;
using std::max;

class Edge {
public:
    size_t getFrom () const {
        return from;
    }
    size_t getTo () const {
        return to;
    }
    size_t getCapacity() const {
        return capacity;
    }
    void setCapacity (size_t capacity) {
        this->capacity = capacity;
    }
    void setFlow (long long flow) {
        this->flow = flow;
    }
    //Остаточная пропускная способность
    long long getResidualCapacity() const {
        return static_cast<long long>(capacity) - flow;
    }
    void increaseFlow(long long increment) {
        flow += increment;
    }
    Edge(size_t from, size_t to, size_t capacity) : from(from), to(to), capacity(capacity), flow(0) {}
private:
    size_t from, to;
    // Пропускная способность
    size_t capacity;
    long long flow;
};

class Net {
public:
    typedef pair<Edge*, Edge*> Arc;
    Net(size_t, size_t, size_t);
    ~Net();
    void addEdge(const Edge&);
    const vector<Arc>& getOuterEdges(size_t from) const {
        return edges[from];
    }
    size_t getVerticesCount () const {
        return verticesCount;
    }
    size_t getSource () const {
        return source;
    }
    size_t getSink () const {
        return sink;
    }
private:
    size_t verticesCount;
    size_t source;
    size_t sink;
    vector<vector<Arc>> edges;
};

Net::Net(size_t verticesCount, size_t source, size_t sink) {
    this->verticesCount = verticesCount;
    this->source = source;
    this->sink = sink;
    edges.resize(verticesCount);
}

Net::~Net() {
    for (const vector<Arc> &arcs: edges) {
        for (const Arc &arc: arcs) {
            delete arc.first;
        }
    }
}

void Net::addEdge(const Edge& edge) {
    Edge* straightEdge = new Edge(edge.getFrom(), edge.getTo(), edge.getCapacity());
    // Обратное ребро с нулевым потоком
    Edge* reverseEdge = new Edge(edge.getTo(), edge.getFrom(), 0);
    Arc straightArc = make_pair(straightEdge, reverseEdge);
    Arc reverseArc = make_pair(reverseEdge, straightEdge);
    edges[edge.getFrom()].push_back(straightArc);
    edges[edge.getTo()].push_back(reverseArc);
}

// Поиск блокирующего потока
long long tryPushFlowToTheSink(const Net& net, const vector<size_t>& layers, size_t vertex, vector<size_t>& edgeIterators,
                               long long pushingFlow = std::numeric_limits<long long>::max()) {
    if (vertex == net.getSink() || pushingFlow == 0) {
        return pushingFlow;
    }
    const vector<Net::Arc>& arcs = net.getOuterEdges(vertex); //////////////////////
    for (size_t i = edgeIterators[vertex]; i < arcs.size(); ++i) {
        const Edge edge = *arcs[i].first;
        if (layers[edge.getFrom()] + 1 != layers[edge.getTo()] || edge.getResidualCapacity() <= 0) {
            continue;
        }
        const long long newPushingFlow = std::min<long long>(pushingFlow, edge.getResidualCapacity());
        const long long pushedFlow = tryPushFlowToTheSink(net, layers, edge.getTo(), edgeIterators, newPushingFlow);
        if (pushedFlow != 0) {
            arcs[i].first->increaseFlow(pushedFlow);
            arcs[i].second->increaseFlow(-pushedFlow);
            return pushedFlow;
        }
    }
    if (edgeIterators[vertex] != arcs.size()) {
        ++edgeIterators[vertex];
    }
    return 0;
}

// Слоистая сеть
vector<size_t> buildLayeredNetwork (const Net& net) {
    std::queue<size_t> que;
    // Заполняем максимальными значениями
    vector<size_t> layers(net.getVerticesCount(), static_cast<size_t>(-1));
    layers[net.getSource()] = 0;
    vector<bool> used(net.getVerticesCount(), false);
    que.push(net.getSource());
    while (!que.empty()) {
        const size_t vertex = que.front();
        que.pop();
        if (used[vertex]) {}
        else {
            for (const Net::Arc& arc: net.getOuterEdges(vertex)) {
                if (arc.first->getResidualCapacity() <= 0) {
                    continue;
                }
                const size_t nextVertex = arc.first->getTo();
                if (layers[nextVertex] == numeric_limits<size_t>::max()) {
                    layers[nextVertex] = layers[vertex] + 1;
                    que.push(nextVertex);
                }
            }
        }
        used[vertex] = true;
    }
    return layers;
}

long long SetMaxFlow (const Net& net) {
    long long maxFlow = 0;
    while (true) {
        vector<size_t> layers = buildLayeredNetwork(net);
        if (layers[net.getSink()] == static_cast<size_t>(-1)) {
            break;
        }
        long long augmentation = 0;
        vector<size_t> edgeIterators(net.getVerticesCount(), 0);
        do {
            augmentation = tryPushFlowToTheSink(net, layers, net.getSource(), edgeIterators);
            maxFlow += augmentation;
        }
        while (augmentation > 0);
    }
    return maxFlow;
}

void clearFlow (Net& net) {
    for (size_t i = 0; i < net.getVerticesCount(); i ++) {
        for (const typename Net::Arc& arc: net.getOuterEdges(i)) {
            arc.first->setFlow(0);
        }
    }
}

bool canDrink (Net& net, const size_t& employeesCount, const size_t& days) {
    for (const typename Net::Arc& arc: net.getOuterEdges(net.getSource())) {
        arc.first->setCapacity(days);
    }
    const long long maxFlow = SetMaxFlow(net);
    bool out = (maxFlow == employeesCount * days);
    clearFlow(net);
    return out;
}



int main() {
    size_t employeesCount, teaTypesCount;
    cin >> employeesCount >> teaTypesCount;
    const size_t verticesCount = 2 + employeesCount + teaTypesCount;
    const size_t source = 0;
    const size_t sink = verticesCount - 1;
    Net net(verticesCount, source, sink);
    for (size_t i = 0; i < employeesCount; ++i) {
        const size_t capacity = numeric_limits<uint32_t>::max();
        Edge edge(source, 1 + i, capacity);
        net.addEdge(edge);
    }
    for (size_t i = 0; i < teaTypesCount; ++i) {
        size_t capacity;
        cin >> capacity;
        Edge edge(1 + employeesCount + i, sink, capacity);
        net.addEdge(edge);
    }
    // Стоим сеть из 4х слоев: в 1м - мнимая вершина-источник, во 2м - сотрудники, в 3м - сорта чая,
    // в 4м - мнимая вершина-сток
    for (size_t i = 0; i < employeesCount; ++i) {
        size_t favouriteTeaTypesCount;
        cin >> favouriteTeaTypesCount;
        for (size_t j = 0; j < favouriteTeaTypesCount; ++j) {
            size_t favouriteTeaTypeId;
            cin >> favouriteTeaTypeId;
            --favouriteTeaTypeId;
            const size_t capacity = numeric_limits<uint32_t>::max();
            Edge edge(1 + i, 1 + employeesCount + favouriteTeaTypeId, capacity);
            net.addEdge(edge);
        }
    }
    size_t left = 0;
    size_t right = numeric_limits<uint32_t>::max();
    // Бинарным поиском ищем максимальное кол-во дней
    // На каждой итераии бин. поиска перестаиваем сеть и запускаем метод canDrink, 
    // чтобы узнать хватит ли чая на middle дней. Бин. поиском по ответу находим верхнюю границу.
    while (right - left > 1) {
        const size_t middle = (left + right) / 2;
        if (canDrink(net, employeesCount, middle)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    cout << left << endl;
    return 0;
}
