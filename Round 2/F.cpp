#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
char colored[510];
int cnt[510];
bool link[510][510];
bool isnear(int x, int y) {
    if (colored[x] == 'a' && colored[y] == 'c') return 0;

    if (colored[x] == 'c' && colored[y] == 'a') return 0;

    return 1;
}
void init() {
    memset(cnt, 0, sizeof(cnt));
    memset(link, 0, sizeof(link));
}
int main() {
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        link[x][y] = link[y][x] = 1;
        cnt[x]++;
        cnt[y]++;
    }
    int flag = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == n - 1) {
            colored[i] = 'b';
        } else {
            if (flag == 0) {
                colored[i] = 'a';
                flag = i;
            }
        }
    }
    if (flag == 0) {
        puts("Yes");
        for (int i = 0; i < n; i++) {
            printf("b");
        }
        cout << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (i == flag) {
            continue;
        }
        if (link[i][flag] == 0) {
            colored[i] = 'c';
        } else {
            if (colored[i] == 0) {
                colored[i] = 'a';
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            } else if (isnear(i, j) == 0 && link[i][j] == 1) {
                puts("No");
                return 0;
            } else if (isnear(i, j) == 1 && link[i][j] == 0) {
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
    for (int i = 1; i <= n; i++) {
        printf("%c", colored[i]);
    }
    cout << endl;
    return 0;
}