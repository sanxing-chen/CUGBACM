#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1 << 10 + 7;
const int mod = 1e9 + 7;
long long quick_pow(int a, int b) {
    long long ans = 1;
    long long tmp = a;

    while (b != 0) {
        if (b & 1) ans = ans * tmp % mod; //不可以写 ans=ans*ans%c 结果会变

        tmp = tmp * tmp % mod;
        b = b >> 1;
    }
    return ans;
}

struct Point {
    int x, y;
    Point() {}
    Point(const int &a, const int &b)
        : x(a)
        , y(b) {}
    friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator<(const Point &a, const Point &b) {
        if (a.x == b.x) {
            return a.y < b.y;
        } else {
            return a.x < b.x;
        }
    }
} point[maxn];

map<Point, int> vec;
map<Point, int>::iterator it;

int main() {
    int t, n;
    ios::sync_with_stdio(0);
    while (cin >> t) {
        while (t--) {
            cin >> n;
            for (int i = 1; i <= n; ++i) {
                cin >> point[i].x >> point[i].y;
            }
            sort(point + 1, point + 1 + n);
            ll ans = 0;
            for (int i = 1; i < n; ++i) {
                vec.clear();
                int repeatPoint = 1;
                int _x, _y;
                for (int j = i + 1; j <= n; ++j) {
                    if (point[i] == point[j]) {
                        ++repeatPoint;
                        continue;
                    }
                    _x = point[j].x - point[i].x;
                    _y = point[j].y - point[i].y;
                    int k = __gcd(_x, _y);
                    _x /= k;
                    _y /= k;
                    ++vec[Point(_x, _y)];
                }
                ans = (ans + quick_pow(2, repeatPoint - 1) - 1) % mod;
                for (it = vec.begin(); it != vec.end(); ++it) {
                    ans = (ans + ((quick_pow(2, repeatPoint - 1)) % mod * ((quick_pow(2, it->second) - 1) % mod))) % mod;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}