// 设计一个程序求取 所有小于等于 n 的素数
// 其中n是一个大于2的整数，要求每行输出10个素数，尽量使用较优的算法
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int isPrime(int value)
{
    int i;
    assert(value >= 2);
    if (value == 2) return 1;
    for (i = 2; i <= (int)sqrt(value); ++i)
        if (value % i == 0)
            return 0; // 不是素数
    return 1; // 素数
}

void slove(int maxValue)
{
    int i;
    int cnt = 1;
    printf("%8d", 2);
    for (i = 3; i < maxValue; i += 2) {
        if (isPrime(i)) {
            cnt++;
            printf("%8d", i);
            if(cnt % 10 == 0) putchar('\n');
        }
    }
    printf("\ntotal = %d\n", cnt);
}

int main()
{
    int n;
    scanf("%d", &n);
    slove(n);
    return 0;
}

