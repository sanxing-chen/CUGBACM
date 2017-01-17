#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
const int MAXN = 100000 + 5;

int M;
int S[MAXN], A[MAXN], B[MAXN];

int LIS() {
    int len = 0;
    for (int i = 1; i <= M; i++) {
        int pos = lower_bound(B, B + len, A[i]) - B;
        if (len == pos) {
            B[len++] = A[i];
        } else {
            B[pos] = A[i];
        }
    }
    return len;
}

int main() {
    int t;
    scanf("%d", &t);
    int cas = 0;
    while (t--) {
        cas++;
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &S[i]);
        }
        int sum = 0;
        M = 0;
        for (int i = 1; i <= n; i++) {
            if (S[i] == 0) {
                sum++;
            } else {
                A[++M] = S[i] - sum;
            }
        }
        printf("Case #%d: %d\n", cas, LIS() + sum);
    }
}