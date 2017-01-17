#include <bits/stdc++.h>
#define ll long long
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
const int NV = 100005;
map<int, ll> previousMap, currentMap, ans;
int sum[NV << 2];
int a[NV], cnt = 1, n;
void PushUp(int rt) {
    sum[rt] = __gcd(sum[rt << 1], sum[rt << 1 | 1]);
}
void build(int l, int r, int rt = 1) {
    if (l == r) {
        sum[rt] = a[cnt++];
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
int query(int L, int R, int l, int r, int rt = 1) {
    if (L <= l && r <= R) return sum[rt];
    int m = (l + r) >> 1;
    int result_1 = 0, result_2 = 0;
    if (L <= m) result_1 = query(L, R, lson);
    if (m < R) result_2 = query(L, R, rson);
    if (!result_1) return result_2;
    if (!result_2) return result_1;
    return __gcd(result_1, result_2);
}
void getQuery() {
    ans.clear();
    currentMap.clear();
    for (int i = 1; i <= n; i++) {
        previousMap.clear();
        previousMap = currentMap;
        currentMap.clear();
        ans[a[i]]++;
        currentMap[a[i]]++;
        for (auto it = previousMap.begin(); it != previousMap.end(); it++) {
            int k = __gcd(a[i], it->first);
            ans[k] += it->second;
            currentMap[k] += it->second;
        }
    }
}
int main() {
    int t, j = 1, m, l, r, queryAns;
    cin >> t;
    while (t--) {
        cnt = 1;
        printf("Case #%d:\n", j++);
        cin >> n;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        build(1, n);
        getQuery();
        cin >> m;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &l, &r);
            queryAns = query(l, r, 1, n);
            printf("%d %lld\n", queryAns, ans[queryAns]);
        }
    }
}