#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define mem(a, b) memset(a, b, sizeof(a))
#define INF 1000000070000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int cnt, n, head[900010], vis[900010];
int repeat[900010]; //记录重复的边
ll dist[900010], Map[900010];
struct node {
    int v, next, w;
} e[900005];
void add(int u, int v, int w) {
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt++;
}
void spfa() {
    int i;
    priority_queue<int> q;
    for (i = 0; i <= n; i++) {
        dist[i] = INF;
    }
    repeat[1] = 1;
    q.push(1);
    vis[1] = 1;
    dist[1] = 0;
    while (q.empty() == 0) {
        int u = q.top();
        q.pop();
        vis[u] = 0;
        for (i = head[u]; i != -1; i = e[i].next) {
            if (dist[e[i].v] > dist[u] + e[i].w) {
                dist[e[i].v] = dist[u] + e[i].w;
                repeat[e[i].v] = repeat[u];
                if (vis[e[i].v] == 0) {
                    vis[e[i].v] = 1;
                    q.push(e[i].v);
                }
            } else if (dist[e[i].v] == dist[u] + e[i].w) {
                repeat[e[i].v] += repeat[u];
                if (repeat[e[i].v] >= 2) {
                    repeat[e[i].v] = 2;
                }
            }
        }
    }
}
int main() {
    int m, k, i, u, v, w, sum = 0; // sum表示需要保留的火车线路
    mem(head, -1);
    cin >> n >> m >> k;
    for (i = 0; i <= n; i++) {
        Map[i] = INF;
    }
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    for (i = 0; i < k; i++) {
        scanf("%d%d", &v, &w);
        if (Map[v] > w) {
            Map[v] = w;
        }
    }
    for (i = 1; i <= n; i++) {
        if (Map[i] != INF) {
            add(1, i, Map[i]);
            add(i, 1, Map[i]);
            sum++;
        }
    }
    spfa();
    for (i = 1; i <= n; i++) {
        if (Map[i] != INF) {
            if (dist[i] == Map[i] && repeat[i] == 2) {
                sum--;
            } else if (dist[i] < Map[i]) {
                sum--;
            }
        }
    }
    printf("%d\n", k - sum); //总的减去保留在最短路里面的
    return 0;
}