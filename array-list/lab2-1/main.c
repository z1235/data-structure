
// 实现顺序表各种基本运算的算法
// 1. 初始化顺序表
// 2. 一次使用尾插法插入 a b c d e元素
// 3. 输出顺序表
// 4. 输出顺序表 L 的长度
// 5. 判断顺序表 L 是否为空
// 6. 输出顺序表 L 的第3个元素
// 7. 输出元素 a 的位置
// 8. 在第4个位置上插入 f 元素
// 9. 输出顺序表
// 10. 删除顺序表的第 3 个元素
// 11. 输出顺序表
// 12. 释放顺序表

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE_MAX 10

typedef char ElemType;
typedef struct {
    ElemType data[SIZE_MAX];
    int size;
} SqList;

void initSqList(SqList **list)
{
    (*list) = (SqList *)malloc(sizeof(SqList));
    (*list)->size = 0;
}

void destoryList(SqList *list)
{
    free(list);
}

int isEmpty(SqList *list)
{
    return list->size == 0;
}

int listSize(SqList *list)
{
    return list->size;
}

void dispList(SqList *list)
{
    int i;
    if (isEmpty(list)) return;
    for (i = 0; i < list->size; ++i) {
        printf("%4c", list->data[i]);
    }
    printf("\n");
}

ElemType getElem(SqList *list, int i)
{
    assert(i >= 0 && i < list->size);
    return list->data[i];
}

int locateElem(SqList *list, ElemType e)
{
    int i;
    for (i = 0; i < list->size; ++i)
        if (list->data[i] == e)
            return i;
    return -1;
}

// pos表示数组的序号从0开始
void insertItem(SqList *list, int pos, ElemType e)
{
    int i;
    assert(list->size < SIZE_MAX);
    // [pos, size - 1] 搬移到 [pos + 1, size]
    for (i = list->size; i > pos; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[i] = e;
    list->size++;
}

// 删除位置 pos的元素
void deleteItem(SqList *list, int pos)
{
    int i;
    // 使用[pos + 1, size)填充 [pos, size - 1) 数组
    for (i = pos; i < list->size - 1; ++i)
        list->data[i] = list->data[i + 1];
    list->size--;
}

int main()
{
    SqList *list;
    int pos;
    ElemType e;
    int i;
    initSqList(&list);
    for (i = 0; i < 6; ++i)
        insertItem(list, i, 'a' + i);
    dispList(list);
    printf("len = %d\n", listSize(list));
    printf("index = 3 value = %c\n", getElem(list, 3));
    printf("delete index 2 and 3\n");
    deleteItem(list, 3);
    deleteItem(list, 2);
    dispList(list);
    e = 'f';
    pos = locateElem(list, e);
    if (pos == -1) printf("not find %c\n", e);
    else printf("find %c at %d\n", e, pos);
    return 0;
}
