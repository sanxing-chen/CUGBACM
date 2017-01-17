#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

/*
树状数组
从右边往左扫看右边有多少个数是小于当前位置的数的，
然后可以达到的最右距离就是最初始的位置加上小于它的数的数量
可以达到的最左距离是min(最初始的位置,i)
所以最右减去最左就是i的答案了.
*/
int bit[N];
int num[N], tmp[N], r[N];

int lowbit(int x) {
    return x & (-x);
}

void update(int x) {
    while (x <= N) {
        bit[x] += 1;
        x += lowbit(x);
    }
}

int query(int x) {
    int ans = 0;
    while (x) {
        ans += bit[x];
        x -= lowbit(x);
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; cas++) {
        memset(bit, 0, sizeof(bit));
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", num + i);
            tmp[num[i]] = i;
        }
        for (int i = n; i > 0; i--) {
            update(num[i]);
            r[num[i]] = query(num[i] - 1);
        }

        printf("Case #%d: ", cas);
        for (int i = 1; i <= n; i++) {
            if (i != n) {
                printf("%d ", abs(tmp[i] + r[i] - min(tmp[i], i)));
            } else {
                printf("%d\n", abs(tmp[i] + r[i] - min(tmp[i], i)));
            }
        }
    }
    return 0;
}