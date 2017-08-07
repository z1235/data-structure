// 在顺序表中进行二分查找的操作

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef int KeyType;
typedef double InfoType;
typedef struct {
    KeyType key;
    InfoType info;
} Node;

#define N_MAX 10
typedef Node SList[N_MAX];

int mybsearch(SList list, KeyType key)
{
    int l = 0, r = N_MAX - 1;
    int mid;
    assert(isOrder(list));
    while (l <= r) {
        mid = l + (r - l)/2;
        if (list[mid].key == key) return mid;
        else if (list[mid].key > key) r = mid -1;
        else l = mid + 1;
    }
    return -1;
}

int cmp(const void *a, const void *b)
{
    Node *p = (Node *)a;
    Node *q = (Node *)b;
    return p->key - q->key;
}

int isOrder(SList list)
{
    int i;
    for (i = 1; i < N_MAX; ++i) {
        if (list[i].key < list[i - 1].key)
            return 0;
    }
    return 1;
}

int main()
{
    SList list;
    KeyType needKey;
    int pos;
    int i;
    srand(time(NULL));
    for (i = 0; i < N_MAX; ++i)
        list[i].key = rand() % 100;
    qsort(list, N_MAX, sizeof(Node), cmp);
    for (i = 0; i < N_MAX; ++i)
        printf("%d ", list[i].key);
    putchar('\n');
    scanf("%d", &needKey);
    pos = mybsearch(list, needKey);
    if (pos == -1) printf("not find\n");
    else printf("fined at %d\n", pos);
    return 0;
}
