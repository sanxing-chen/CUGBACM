#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    int n, t, a[50000];
    bool flag = true;
    cin >> n >> t;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n;) {
        i += a[i];
        if (i == t) {
            flag = false;
            break;
        } else if (i > t) {
            break;
        }
    }
    if (flag)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
}