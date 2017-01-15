#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define inf 0x7fffffff
using namespace std;
const int nodes = 200;
const int edges = 40000 + 50;
int n, s, t;
struct node {
    int v, next, flow;
} e[edges]; //建立邻接表
int head[nodes], cur[nodes], cnt;
char map[nodes][nodes];
class Dinic {
  public:
    int spath() // spfa求最短路径
    {
        queue<int> q;
        while (!q.empty()) q.pop();
        memset(dis, -1, sizeof(dis));
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i + 1; i = e[i].next) {
                int v = e[i].v;
                if (dis[v] == -1 && e[i].flow > 0) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        return dis[t] != -1;
    }
    int Min(int a, int b) {
        if (a < b) return a;
        return b;
    }
    int dfs(int u, int flow) {
        int cost = 0;
        if (u == t) return flow;
        for (int &i = cur[u]; i + 1; i = e[i].next) {
            // cur[u]=i;
            int v = e[i].v;
            if (dis[v] == dis[u] + 1 && e[i].flow > 0) {
                int minn = dfs(v, Min(e[i].flow, flow - cost));
                if (minn > 0) {
                    e[i].flow -= minn;
                    e[i ^ 1].flow += minn;
                    cost += minn;
                    if (cost == flow) break;
                } else
                    dis[v] = -1;
            }
        }
        return cost;
    }
    int result() {
        int xx = 0;
        while (spath()) {
            for (int i = s; i <= t; i++) cur[i] = head[i];
            xx += dfs(s, inf);
        }
        return xx;
    }

  private:
    int dis[nodes];
} dinic;
void Init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void add(int a, int b, int c) {
    e[cnt].v = b;
    e[cnt].next = head[a];
    e[cnt].flow = c;
    head[a] = cnt++;

    e[cnt].v = a;
    e[cnt].flow = 0;
    e[cnt].next = head[b];
    head[b] = cnt++;
}
void build_map(int val) //建一个虚拟起点和终点与点之间距离为val的图
{
    Init();
    for (int i = 1; i <= n; i++) {
        add(s, i, val);
        add(i + n, t, val);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == 'Y') {
                add(i, j + n, 1);
            }
        }
    }
}
int find_mid() //查找最大匹配数，即为各自不同的站法
{
    int low = 0, up = n, ans = 0;
    while (low <= up) {
        int mid = (low + up) >> 1;
        build_map(mid); //建一个mid图
        if (dinic.result() == mid * n) {
            ans = mid;
            low = mid + 1; //因为要找最大的匹配次数
        } else
            up = mid - 1;
    }
    return ans;
}
void find_one_ans_del() {
    int res[nodes];
    for (int i = 1; i <= n; i++) //仍未确认这一个循环的必要性
    {
        for (int j = head[i]; j + 1; j = e[j].next) {
            int v = e[j].v;
            if (v != s && !e[j].flow) {
                res[v - n] = i;
                map[i][v - n] = 'N';
                break; //剪枝
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i == 1)
            printf("%d", res[i]);
        else
            printf(" %d", res[i]);
    }
    printf("\n");
    /*for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j+1;j=e[j].next)
        {
            int v=e[j].v;
            if(v!=s&&e[j].flow==0)
            {
                map[i][v-n]='N';
                break;
            }
        }
    }*/
}
void treatment(int rmid) //确定每一种情况的具体站位
{
    printf("%d\n", rmid); // s输出最大完美匹配数
    build_map(rmid);      //建图
    dinic.result();       //求最大流
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j + 1; j = e[j].next) {
            int v = e[j].v;
            if (v != s && e[j].flow == 1) {
                map[i][v - n] = 'N';
            }
        }
    }
    while (rmid--) {
        build_map(1); //建一个k=1的图
        dinic.result();
        find_one_ans_del(); //找到具体的位置信息
    }
}
int main() {
    while (~scanf("%d", &n), n) {
        for (int i = 1; i <= n; i++) {
            scanf("%s", map[i] + 1);
        }
        s = 0;
        t = 2 * n + 1;
        int kr = find_mid();
        treatment(kr);
    }
    return 0;
}