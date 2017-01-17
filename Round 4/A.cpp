#include <bits/stdc++.h>
#define ll long long
using namespace std;
int dp[1000000], pre[1000000];
int main()
{
    int n, m, temp;
    while(~scanf("%d%d", &m, &n)) {
        for (int i = 0; i <= n; i++) {
            pre[i] = dp[i] = -100000000;
        }
        dp[1] = pre[0] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &temp);
            for (int j = m; j >= 1; j--) {
                dp[j] = temp + max(dp[j], pre[j - 1]);
                // cout << "&&" << dp[j] << " " << " " << j - 1 << ":" << pre[j - 1] << endl;
                pre[j] = max(pre[j], dp[j]);
            }
        }
        printf("%d\n", pre[m]);
    }
}