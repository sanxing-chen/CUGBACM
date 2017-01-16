#include <bits/stdc++.h>

using namespace std;

int main()
{
        int t;
        scanf("%d", &t);
        while(t--)
        {
                int k, n, m;
                scanf("%d%d%d", &k, &n, &m);
                if(k == 1)
                {
                        if(m % 2 == 0 || n % 2 == 0)
                        {
                                puts("B");
                        }
                        else puts("G");
                }
                else if(k == 2)
                {
                        if(n == m)
                                puts("G");
                        else puts("B");
                }
                else if(k == 3)
                {
                        if((n+m-2) % 3) //走不到终点
                                puts("D");
                        else
                        {
                                if(abs((2*m-n-1)/3 - (2*n-m-1)/3) == 0)
                                        puts("G");
                                else if(abs((2*m-n-1)/3 - (2*n-m-1)/3) == 1)
                                        puts("B");
                                else puts("D");
                        }
                }
                else
                {
                        n--;
                        m--;
                        if(n < m) //n>m
                                swap(n, m);
                        int k = n-m;
                        n = k*(1+sqrt(5)) / 2.0;
                        if(n == m)
                                puts("G");
                        else puts("B");
                }
        }
        return 0;
}
