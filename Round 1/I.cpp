#define inf 0x7fffffff
#define mod 1000000007
#define ll long long
const int maxn = (1 << 11) + 10;
bool pali[12][maxn];
long long dp[405][maxn];
int bit[12];
int n, k;
void init() //预处理
{
  bit[1] = 1;
  for (int i = 2; i <= 11; i++) {
    bit[i] = bit[i - 1] << 1;
  }
  memset(pali, 0, sizeof(pali));
  pali[1][0] = 1, pali[1][1] = 1;
  for (int i = 2; i <= 11; i++) {
    int half = i / 2;
    int up = (1 << half) - 1; //左移half位
    for (int x = 0; x <= up; x++) {
      int temp = x;
      int R = 0;
      for (int j = 1; j <= half; j++)
        R = (R << 1) + (temp & 1), temp >>= 1; // t
      if (i & 1)                               //
      {                                        //
        pali[i][(x << 1) << half | R] = true;
        pali[i][(x << 1 | 1) << half | R] = true;
      } else
        pali[i][x << half | R] = true;
    }
  }
}
int cal(int state, int last) {
  if (state >= bit[k])
    state -= bit[k];
  return state << 1 | last;
}

int main() {
  init();
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    ll ans = 0;
    int up = (1 << k) - 1;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= up; j++) {
        if (dp[i - 1][j] == 0)
          continue;
        for (int x = 0; x <= 1; x++) {
          int sta = cal(j, x);
          if (i >= k && pali[k][sta])
            continue;
          if (i >= k + 1 && pali[k + 1][j << 1 | x])
            continue;
          dp[i][sta] += dp[i - 1][j];
          dp[i][sta] %= mod;
        }
      }
    }
    for (int i = 0; i <= up; i++) {
      ans = (ans + dp[n][i]) % mod;
    }
    cout << ans << endl;
  }
}