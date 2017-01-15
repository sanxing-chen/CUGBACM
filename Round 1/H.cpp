#define PI acos(-1)
#define eps 1e-8
#define inf 0x3f3f3f3f
#define debug(x) cout << "---" << x << "---" << endl
#define LL long long
using namespace std;

long long a, b, c, mod;
typedef struct { long long m[3][3]; } Mat;
Mat A = {
    1, 0, 0, 0, 1, 0, 0, 0, 1,
};

long long Num_quick_pow(long long a, long long n) //快速幂模运算
{
    long long ans = 1;
    while (n) {
        if (n & 1) {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

Mat Mat_Mul(Mat a, Mat b) //矩阵乘法
{
    Mat ans;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            ans.m[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j] % (mod - 1));
            }
        }
    return ans;
}

long long Mat_quick_pow(Mat P, long long n) // 矩阵快速幂
{
    Mat Ans = A;
    while (n) {
        if (n & 1) {
            Ans = Mat_Mul(Ans, P);
        }
        P = Mat_Mul(P, P);
        n >>= 1;
    }
    return (Ans.m[0][0] * b % (mod - 1) + Ans.m[0][2] * b % (mod - 1)) % (mod - 1);
}

int main() {
    int T;
    long long n;
    scanf("%d", &T);
    while (T--) {
        scanf("%I64d%I64d%I64d%I64d%I64d", &n, &a, &b, &c, &mod);
        if (n == 1) {
            printf("1\n");
            continue;
        }
        if (n == 2) {
            printf("%I64d\n", Num_quick_pow(a, b));
            continue;
        }
        Mat C = {c, 1, 1, 1, 0, 0, 0, 0, 1};
        if (a % mod == 0) //！！！
        {
            printf("0\n");
        } else {
            cout << Num_quick_pow(a, Mat_quick_pow(C, n - 2)) << endl;
        }
    }
    return 0;
}