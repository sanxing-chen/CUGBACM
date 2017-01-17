#include <bits/stdc++.h>
using namespace std;
int a[maxn];
int p[maxn]; //第i个导弹拦截系统已经拦截的最低的导弹高度
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            p[i] = inf;
            //用刚好比a[i]大的系统来拦截 把能拦截更高高度的系统留着
            sort(p + 1, p + ans + 1);
            int flag = lower_bound(p + 1, p + ans + 2, a[i]) - p;
            if (flag == ans + 1) //使用了新系统
            {
                ans++;
            }
            p[flag] = a[i]; //更新系统情况
        }
        if (n != 0)
            printf("%d\n", ans);
        else
            printf("0\n");
    }
    return 0;
}