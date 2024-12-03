#include <vector>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <queue>
#include <cstdio>
using std::vector;
using std::string;


class State {
public:
    State() {}
    State(int, int, const vector<int>);
    string getPath() const { return path; }
    bool tryMoveLeft();
    bool tryMoveRight();
    bool tryMoveUp();
    bool tryMoveDown();
    double getApproxDist() const;
    int getCmpFunc() const { return path.size() + getApproxDist(); }
    long long getHash() const;
private:
    vector<int> field;
    string path;
    int dim;
    int nullPos;
};

State::State(int _nullPos, int _dim, const vector<int> _field) {
    dim = _dim;
    std::copy(_field.begin(), _field.end(), std::back_inserter(field));
    nullPos = _nullPos;
}

bool State::tryMoveLeft() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == i * dim)
            return false;
    }
    std::swap(field[nullPos], field[nullPos - 1]);
    --nullPos;
    path.push_back('R');
    return true;
}

bool State::tryMoveRight() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == i * dim + dim - 1)
            return false;
    }
    std::swap(field[nullPos], field[nullPos + 1]);
    ++nullPos;
    path.push_back('L');
    return true;
}

bool State::tryMoveUp() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == i)
            return false;
    }
    std::swap(field[nullPos], field[nullPos - 4]);
    nullPos -= 4;
    path.push_back('D');
    return true;
}

bool State::tryMoveDown() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == dim * dim - dim + i)
            return false;
    }
    std::swap(field[nullPos], field[nullPos + 4]);
    nullPos += 4;
    path.push_back('U');
    return true;
}

double State::getApproxDist() const {
    int answer = 0;
    for (int i = 0; i < dim; ++i)
        for (int j = 0; j < dim; ++j) {
            // Число, стоящее в определенной клетке в данный момент
            int num = field[i * dim + j];
            if (num == 0) {
                num = dim * dim;
            }
            // Расстояния до нужных клеток
            int xdest = (num - 1) / dim; // где должны стоять
            int ydest = (num - 1) % dim;
            answer += abs((i - xdest)) + abs((j - ydest));
        }
    return answer * 10;
}


// Хэши для отслеживания уникальных расположений чисел на доске
long long State::getHash() const {
    long long ans = 0;
    long long pow10 = 1;
    for (int i = 0; i < dim * dim; ++i) {
        ans += field[i] * pow10;
        pow10 *= 10;
    }
    return ans;
}

struct Comparison {
    bool operator() (const State& A, const State& B) const { return A.getCmpFunc() > B.getCmpFunc(); }
};

class Solver {
public:
    Solver(int, const State&);
    bool solve(string&);
private:
    // Будем хранить состояния в очереди по неубыванию
    std::priority_queue <State, std::deque<State>, Comparison> states;
    // Сэт хэшей
    std::unordered_set<long long> used;
    int dim;
    State startState;
};

Solver::Solver(int _dim, const State& start) : dim(_dim), startState(start) {}

bool Solver::solve(string& answer) {
    states.push(startState);
    while (!states.empty()) {
        State curState = states.top();
        states.pop();
        // Если такой хэш есть
        if (used.find(curState.getHash()) != used.end()) {
            continue;
        }
        // Если все числа на своих местах, заканчиваем игру
        if (curState.getApproxDist() == 0) {
            answer = curState.getPath();
            return true;
        }
        else {
            used.insert(curState.getHash());
        }
        State left, right, up, down;
        left = right = up = down = curState;
        // Если не нашли хэшей
        if (left.tryMoveLeft()) {
            if (used.find(left.getHash()) == used.end()) {
                states.push(left);
            }
        }
        if (right.tryMoveRight()) {
            if (used.find(right.getHash()) == used.end()) {
                states.push(right);
            }
        }
        if (up.tryMoveUp()) {
            if (used.find(up.getHash()) == used.end()) {
                states.push(up);
            }
        }
        if (down.tryMoveDown()) {
            if (used.find(down.getHash()) == used.end()) {
                states.push(down);
            }
        }
    }
    return false;
}

int inversionCount(const vector<int>& field) {
    int inversion = 0;
    for (int i = 0; i < 16; ++i) {
        if (field[i] != 0) {
            for (int j = i + 1; j < 16; ++j) {
                if (field[i] > field[j] && field[j] != 0) {
                    ++inversion;
                }
            }
        }
    }
    return inversion;
}

int main() {;
    int nullPos = 0;
    vector<int> field(16);
    for (int i = 0; i < 16; ++i) {
        std::cin >> field[i];
        if (field[i] == 0) {
            nullPos = i;
        }
    }
    // Решения головоломки не существует, если эта сумма нечётная
    if ((inversionCount(field) + ((nullPos/4) + 1)) % 2 == 1) {
        std::cout << -1;
    }
    else {
        State A = State(nullPos, 4, field);
        Solver S(4, A);
        string ans = "";
        S.solve(ans);
        std::cout << ans.size() << "\n" << ans.c_str();
    }
    return 0;
}
