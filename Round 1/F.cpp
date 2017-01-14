#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 7;

class vertex {
public:
  int id, deg;
};

vertex ver[MAXN];
int n, u[MAXN * MAXN], v[MAXN * MAXN];
int m, s, t, r;

bool cmp(vertex v1, vertex v2) { return v1.deg > v2.deg; }

int Havel_Hakimi() {
  int i, j, ans;
  ans = 0;
  for (int i = 0; i < n; ++i) {
    sort(ver + i, ver + n, cmp);
    if (i + ver[i].deg >= n) //简单无向图每个定点的度数最大为n-1
    {
      ans = -1;
      break;
    } else if (ver[i].deg == 0) //找到S`序列
    {
      break;
    }
    for (j = i + 1; j <= i + ver[i].deg; ++j) {
      ver[j].deg--;
      if (ver[j].deg < 0) //出现负数，不满足S`序列
      {
        ans = -1;
        return ans;
      }
      u[m] = ver[i].id;
      v[m++] = ver[j].id;
    }
    if (j < n && ver[j].deg == ver[j - 1].deg + 1) //存在同构的情况
    {
      ans = 1;
      s = m - 1; //要减一的序列中最后一个顶点的数组下标
      t = ver[j]
              .id;       //要减一的序列中最后一个顶点后面紧挨着的顶点，本来将（i，j）建边，现在将（i，j+1）建边，同构的情况
      r = ver[j - 1].id; //要减一的序列中最后一个顶点的顶点标号
    }
  }
  return ans;
}

void outputAns() {
  printf("%d %d\n", n, m);
  if (m == 0)
    printf("\n\n");
  else {
    for (int i = 0; i < m; i++)
      printf("%d%c", u[i], i == m - 1 ? '\n' : ' ');
    for (int i = 0; i < m; i++)
      printf("%d%c", v[i], i == m - 1 ? '\n' : ' ');
  }
}

int main() {
  while (scanf("%d", &n) != EOF) {
    m = 0;
    int odd = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &ver[i].deg);
      ver[i].id = i + 1;
      if (ver[i].deg & 1)
        odd++;
    }
    if (odd & 1) // 奇数个奇度数，据握手定理知其不可能是一个简单无向图的度序列
    {
      cout << "IMPOSSIBLE" << endl;
      continue;
    } else {
      int mark = Havel_Hakimi();
      if (mark == -1) {
        cout << "IMPOSSIBLE" << endl; //没有S`
      } else if (mark == 0) {
        cout << "UNIQUE" << endl;
        outputAns();
      } else {
        cout << "MULTIPLE" << endl;
        outputAns();
        v[s] = t;                       //同构变换
        for (int i = s + 1; i < m; i++) //找到并交换同构时变换的顶点并对其变换
        {
          if (u[i] == t)
            u[i] = r;
          else if (u[i] == r)
            u[i] = t;
          if (v[i] == t)
            v[i] = r;
          else if (v[i] == r)
            v[i] = t;
        }
        outputAns();
      }
    }
  }
  return 0;
}