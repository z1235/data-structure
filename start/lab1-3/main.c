#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE_MAX 1024

// 判断一个字符串是否是回文
int isParlindrome(char *str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len/2; ++i)
        if (str[i] != str[len - 1 -  i])
            return 0;
    return 1;
}

int main()
{
    char buf[BUF_SIZE_MAX];
    scanf("%s", buf);
    if (isParlindrome(buf)) printf("is parlindrome\n");
    else printf("isn't parlindrome\n");

    return 0;
}
