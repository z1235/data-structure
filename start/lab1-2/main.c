// 求取一个数字的各位数字之和
#include <stdio.h>
#include <stdlib.h>

int slove(int num)
{
    int sum = 0;
    sum += num % 10;
    num /= 10;
    while (num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// 对循环进行优化
int slove2(int num)
{
    int sum = 0;
    do {
        sum += num % 10;
        num /= 10;
    } while (num);
    return sum;
}

int main()
{
    int num;
    int sum;
    scanf("%d", &num);
    sum = slove2(num);
    printf("sum = %d\n", sum);
    return 0;
}

