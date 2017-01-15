#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 100 + 50;
const int INF = 0x7fffffff;

struct monster {
    int exp, cost;
    monster(int e, int c)
        : exp(e)
        , cost(c) {} //声明及定义结构体构造函数
};

int dp[MAXN][MAXN];
vector<monster> v; //使用容器存储结构体

int main() {
    int n, m, k, s, e, c, ans, x, y, i;
    while (scanf("%d%d%d%d", &n, &m, &k, &s) == 4) {
        v.clear();                  //初始化容器
        memset(dp, -1, sizeof(dp)); //初始化dp数组
        ans = -1;                   //将最终结果储存为负无穷
        while (k--) {
            scanf("%d%d", &e, &c);
            v.push_back(monster(e, c)); //容器中添加怪物类型
        }
        dp[n][s] = m;            //初始化状态
        for (y = n; y >= 0; y--) //遍历所有经验状态
        {
            for (x = s; x > 0; x--) //遍历所有杀怪数量
            {
                if (dp[y][x] >= 0) //判断当前状态是否有效
                {
                    for (i = 0; i < v.size(); i++) {
                        if (dp[y][x] - v[i].cost >= 0) //当新状态满足状态更新条件
                        {
                            //当新状态满足状态终止条件时更新最终结果
                            if (y - v[i].exp <= 0) ans = max(ans, dp[y][x] - v[i].cost);
                            //当新状态仅满足状态更新条件时仅更新状态
                            else
                                dp[y - v[i].exp][x - 1] = max(dp[y][x] - v[i].cost, dp[y - v[i].exp][x - 1]);
                        }
                    }
                }
            }
        }
        printf("%d\n", ans); //输出最终结果
    }
    return 0;
}