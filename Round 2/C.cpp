#include <bits/stdc++.h>
using namespace std;
bool valid = true;
class Graph {
    int V;
    list<int> *adj;
    void _topological_sort(int v, bool visited[], stack<int> &stack, bool _visited[]);

  public:
    Graph(int v);
    ~Graph();
    void addEdge(int v, int w);
    void Topological_sort();
};

Graph::Graph(int v)
    : V(v) {
    adj = new list<int>[V];
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::_topological_sort(int v, bool visited[], stack<int> &stack, bool _visited[]) {
    visited[v] = _visited[v] = true;
    for (list<int>::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = *it;
        if (_visited[u] == true) {
            valid = false;
            return;
        }
        if (visited[u] == false) _topological_sort(u, visited, stack, _visited);
    }
    stack.push(v);
    _visited[v] = false;
}

void Graph::Topological_sort() {
    /*
    *  dfs 遍历，在单支遍历中如果遇到已经访问过的点说明有环
    *  visited[] 记录总体的分支遍历
    *  _visited[] 记录单分支的遍历
    */
    bool visited[V], _visited[V];
    stack<int> stack;
    for (int i = 0; i < V; i++) visited[i] = false;
    for (int i = V - 1; i >= 0; i--) {
        if (visited[i] == false) {
            memset(_visited, false, sizeof _visited);
            _topological_sort(i, visited, stack, _visited);
        }
    }
    if (!valid) {
        cout << "Impossible" << endl;
        return;
    }
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        std::cout << (char) (v + 'a');
    }
    std::cout << std::endl;
}
int main() {
    ios::sync_with_stdio(false);
    string pos, prev;
    int n;
    Graph g(26);
    bool flag;
    cin >> n >> prev;
    n--;
    for (; n--;) {
        cin >> pos;
        int length = min(pos.size(), prev.size());
        flag = true;
        for (int i = 0; i < length; i++) {
            if (prev[i] != pos[i]) {
                g.addEdge((int) (prev[i] - 'a'), (int) (pos[i] - 'a'));
                flag = false;
                break;
            }
        }
        if (flag && prev.size() > pos.size()) {
            valid = false;
        }
        prev = pos;
    }
    if (!valid)
        cout << "Impossible" << endl;
    else {
        g.Topological_sort();
    }
}