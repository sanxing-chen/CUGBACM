#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define eps 1e-8
#define INF 0x7fffffff
#define maxn 100005
#define PI acos(-1.0)
#define seed 31 // 131,1313
Typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
int n, m;
int v[1000];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int sum = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        sum += min(v[a - 1], v[b - 1]);
    }
    cout << sum << endl;
    return 0;
}