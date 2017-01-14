#include <bits/stdc++.h>
#define endl "\n"
#define eps 1e-7
using namespace std;
int getC(int n) {
    return n * (n - 1) * (n - 2) / 6;
}
double dp[150][15000];
double mem[150][150];
int main() {
    int n, m, temp;
    while (cin >> n) {
        memset(dp, 0, sizeof dp);
        memset(mem, 0, sizeof mem);
        n = getC(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%lf", &mem[i][j]);
            }
        }
        scanf("%d", &m);
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d", &temp);
            if (temp < n)
                for (int j = 0; j < n; j++) {
                    dp[j][i] = max(dp[j][i], mem[j][temp] * dp[j][i - 1]);
                    dp[temp][i] = max(dp[temp][i], mem[j][temp] * dp[j][i - 1]);
                }
        }
        double ans = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i][m] > ans) ans = dp[i][m];
        }
        printf("%.6lf\n", ans);
    }
}