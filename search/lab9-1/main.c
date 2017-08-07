#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

typedef char InfoType[10];
typedef int KeyType;

typedef struct {
    KeyType key;
    InfoType data;
} Node;

typedef Node SeqList[N_MAX];


int seqSearch(SeqList plist, int n, KeyType key)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (plist[i].key == key) {
            return i;
        }
    }
    return -1;
}


int main()
{
    SeqList list; // 在栈中分配了一个数组空间，并且list指向了这个数组的首元素
    int i;
    KeyType key = 5;
    int pos;
    int n = 10;
    int a[] = {3, 6, 2, 10, 1, 8, 5, 7, 4, 9};

    for (i = 0; i < n; ++i)
        list[i].key = a[i];
    printf("key list: ");
    for (i = 0; i < n; ++i)
        printf("%3d", list[i].key);
    putchar('\n');
    pos = seqSearch(list, n, key);
    if (pos == -1)
        printf("not find\n");
    else
        printf("find at %d\n", pos);
    return 0;
}
