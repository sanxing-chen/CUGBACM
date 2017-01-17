#include <cstdio>

int main() {
    double a, v1, v2;
    while (scanf("%lf%lf%lf", &a, &v1, &v2) == 3) {
        if (a == 0)
            printf("0\n");
        else if (v1 > v2)
            printf("%.10f\n", a * v1 / (v1 * v1 - v2 * v2));
        else
            printf("Infinity\n");
    }
    return 0;
}