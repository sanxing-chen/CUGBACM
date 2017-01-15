#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
using namespace std;
typedef long long ll;
const int inf = 1e7;
const int maxn = 3000 + 5;
int n, m;
int d[maxn][maxn];         //用于保存任意两点间的最短距离
vector<int> G[maxn];       //记录第i个点连接的点
void AddEdge(int u, int v) //添加新边，将所连接的点添加到数组里
{
    G[u].push_back(v);
    G[v].push_back(u);
}
void bfs(int cur) //暴力bfs cur点到其他点间的最短路
{
    memset(d[cur], 0, sizeof d[cur]); //初始化
    queue<int> q;
    q.push(cur);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        foreach (it, G[u])
            if (!d[cur][*it]) {
                d[cur][*it] = d[cur][u] + 1;
                q.push(*it);
            }
    }
    for (int i = 1; i <= n; i++)
        if (!d[cur][i]) d[cur][i] = inf;
    d[cur][cur] = 0;
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) //初始化
        {
            G[i].clear();
        }
        for (int i = 1; i <= m; i++) //新增一条边
        {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
        }
        for (int i = 1; i <= n; i++) {
            bfs(i);
        }
        int s1, t1, l1, s2, t2, l2;
        scanf("%d%d%d%d%d%d", &s1, &t1, &l1, &s2, &t2, &l2);
        if (d[s1][t1] > l1 || d[s2][t2] > l2) //如果起始条件不满足题意，输出-1
        {
            puts("-1");
            continue;
        }
        int res = d[s1][t1] + d[s2][t2];
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                int dis1 = min(d[s1][i] + d[i][j] + d[j][t1], d[s1][j] + d[j][i] + d[i][t1]);
                int dis2 = min(d[s2][i] + d[i][j] + d[j][t2], d[s2][j] + d[j][i] + d[i][t2]);
                if (dis1 > l1 || dis2 > l2) continue;
                res = min(res, dis1 + dis2 - d[i][j]);
            }
        }
        printf("%d\n", m - res);
    }
    return 0;
}