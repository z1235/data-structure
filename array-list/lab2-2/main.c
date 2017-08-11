// 使用单链表完成各种基本运算

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct Node{
    ElemType data;
    struct Node *nextnode;
} Node, * List;

// 初始化链表，创建头结点
List initList()
{
    List list = (List)malloc(sizeof(Node));
    list->nextnode = NULL;
}

void deleteList(List list)
{
    Node *p = list;
    Node *q = list->nextnode;
    while (q) {
        free(p);
        p = q;
        q = q->nextnode;
    }
    free(p);
}

// 头插
void insertNode(List list, ElemType e)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = e;
    p->nextnode = list->nextnode;
    list->nextnode = p;
}

// 删除节点 index 从0开始计数
int deleteNode(List list, int index, ElemType *e)
{
    // p 指向第 index个元素
    Node *pre = list;
    Node *p = list->nextnode;
    while (index && p) {
        pre = p;
        p = p->nextnode;
        index--;
    }
    if (p) {
        pre->nextnode = p->nextnode;
        e = p->data;
        free(p);
        return 1;

    }
    return -1;
}

void dispList(List list)
{
    Node *p = list->nextnode;
    while (p) {
        printf("%4c", p->data);
        p = p->nextnode;
    }
    putchar('\n');
}

int findElem(List list, ElemType e)
{
    Node *p = list->nextnode;
    int index = 0;
    while (p) {
        if (p->data == e) return index;
        p = p->nextnode;
        index++;
    }
    return -1;
}

int main()
{
    int i;
    ElemType e;
    List list = initList();
    for (i = 0; i < 10; ++i) {
        insertNode(list, 'a' + i);
    }
    dispList(list);
    deleteNode(list, 2, &e);
    printf("delete %c at 2\n", e);
    dispList(list);
    printf("find f at %d", findElem(list, 'f'));
    deleteList(list);

    return 0;
}
