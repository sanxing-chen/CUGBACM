unsigned long long MAXX;
const int MAX_N = 6 * 6; //最大结点数：模式串个数 X 模式串最大长度
const int CLD_NUM = 26;  //从每个结点出发的最多边数：本题是4个ATCG

struct Matrix {
    unsigned long long mat[MAX_N][MAX_N];
    int n;
    Matrix() {}
    Matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) mat[i][j] = 0;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix ret = Matrix(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) ret.mat[i][j] += mat[i][k] * b.mat[k][j];
        return ret;
    }
};

class ACAutomaton {
  public:
    int n;                    //当前结点总数
    int fail[MAX_N];          // fail指针
    bool tag[MAX_N];          ///标记是否为最后一个
    int trie[MAX_N][CLD_NUM]; // trie tree

    void reset() {
        memset(trie[0], -1, sizeof(trie[0]));
        tag[0] = false;
        n = 1;
    }

    //插入模式串s，构造单词树(keyword tree)
    void add(char *s) {
        int p = 0;
        while (*s) {
            int i = *s - 'a';
            if (-1 == trie[p][i]) {
                memset(trie[n], -1, sizeof(trie[n])); // n节点及其后续位置随用随初始化
                tag[n] = false;                       //标记是否为最后一个
                trie[p][i] = n++;
            }
            p = trie[p][i];
            s++;
        }
        tag[p] = true;
    }

    //用BFS来计算每个结点的fail指针，构造trie树
    void construct() {
        queue<int> Q;
        fail[0] = 0;
        for (int i = 0; i < CLD_NUM; i++) {
            if (-1 != trie[0][i]) {
                fail[trie[0][i]] = 0; ///首字母不匹配则为0 返回ROOT
                Q.push(trie[0][i]);   ///传入首字母的n
            } else {
                trie[0][i] = 0; //不存在于模式串中的首字母
            }
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if (tag[fail[u]]) tag[u] = true;  //这个很重要，当u的后缀匹配，u也不能出现
            for (int i = 0; i < CLD_NUM; i++) //遍历所有的u点的子节点
            {
                int &v = trie[u][i]; ///！！！取地址
                if (-1 != v) {
                    Q.push(v);
                    fail[v] = trie[fail[u]][i];
                } else {
                    v = trie[fail[u]][i]; ///取地址以在此更改值
                }
            }
        }
        unsigned long long mat[MAX_N][MAX_N];
    }

    /* 根据trie树来构建状态转换的邻接矩阵mat[][]
       mat[i][j]表示状态i到状态j有几条边   */
    Matrix getMatrix() {
        Matrix ret = Matrix(n + 1);
        for (int i = 0; i < n; i++) // n为节点 j为n节点的子节点，trie[i][j]为j节点的n值，故构建n*n矩阵
            for (int j = 0; j < CLD_NUM; j++)
                if (!tag[i] && !tag[trie[i][j]]) ret.mat[i][trie[i][j]]++;
        /* 上面为建立n个节点的连通图


        矩阵A可以用ac自动机维护一个跳转表得到。接下来就是考虑如何快速的求得A^1+A^2+....+A^L了。

        根据矩阵的性质

        |A  ,  1|                 |A^n , 1+A^1+A^2+....+A^(n-1)|

        |0  ,  1| 的n次方等于|0     ,                                       1|

        同理后续求26^n+26^(n-1)+...+26

        */
        for (int i = 0; i < n + 1; i++) ret.mat[i][n] = 1;
        return ret;
    }
} AC;

/*    矩阵快速幂       */
Matrix pow_M(Matrix &a, int n) {
    Matrix ret = Matrix(a.n);
    for (int i = 0; i < a.n; i++) ret.mat[i][i] = 1;
    Matrix tmp = a;
    while (n) {
        if (n & 1) ret = ret * tmp;
        tmp = tmp * tmp;
        n >>= 1;
    }
    return ret;
}

int main() {
    int n, m;
    char s[12];

    while (cin >> m >> n) {
        AC.reset();
        while (m--) {
            cin >> s;
            AC.add(s);
        }
        AC.construct();
        Matrix a = AC.getMatrix();
        a = pow_M(a, n);
        unsigned long long res = 0;
        for (int i = 0; i < a.n; i++) res += a.mat[0][i];
        res--;
        /* 此处构造矩阵求26^1+26^2+26^3+...+26^n;   */
        a = Matrix(2);
        a.mat[0][0] = 26;
        a.mat[1][0] = a.mat[1][1] = 1;
        a = pow_M(a, n);
        unsigned long long ans = a.mat[1][0] + a.mat[0][0];
        ans--;
        ans -= res;
        cout << ans << endl;
    }
    return 0;
}