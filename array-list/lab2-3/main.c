// 双链表

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char ElemType;
typedef struct Node {
    ElemType data;
    struct Node *prenode;
    struct Node *nextnode;
} Node, * List;

List initList()
{
    List list = (List)malloc(sizeof(Node)); // 头结点
    list->prenode = NULL;
    list->nextnode = NULL;
}

void destoryList(List list)
{
    Node *p = list; // p指向删除的位置
    Node *q; // q中保存下一个节点的指针
    printf("destory: ");
    while (p) {
        q = p->nextnode; // q保存下一个节点的指针
        if (p == list) printf(" head ");
        else printf("%3c", p->data);
        free(p);
        p = q;
    }
}

void isEmpty(List list)
{
    return list->nextnode == NULL;
}

int listLength(List list)
{
    Node *p = list->nextnode;
    int len = 0;
    while (p) {
        len++;
        p = p->nextnode;
    }
    return len;
}

void dispList(List list)
{
    Node *p = list->nextnode;
    while (p) {
        printf("%4c", p->data);
        p = p->nextnode;
    }
    printf("\tlist length = %d\n", listLength(list));
}


ElemType * getElem(List list, int index)
{
    Node *p = list->nextnode;
    while (index && p) {
        index--;
        p = p->nextnode;
    }
    if (p)
        return p->data;
    return NULL;
}

int localElem(List list, ElemType e)
{
    int i = 0;
    Node *p = list->nextnode;
    while (p) {
        if (p->data == e) return i;
        i++;
        p = p->nextnode;
    }
    return -1;
}

// index从序号0开始
void insertElem(List list, int index, ElemType e)
{
    Node *q = list;   // 指向需要插入位置的前一个元素
    Node *p = (Node *)malloc(sizeof(Node)); // 指向待插入的节点
    p->data = e;
    while (index && q->nextnode) { // q最后停靠位置不超过最后一个元素
        index--;
        q = q->nextnode;
    }

    assert(index == 0); // 确保index有效

    if (q->nextnode) { // 非最后一个节点
        q->nextnode->prenode = p;
    }
    p->nextnode = q->nextnode;
    q->nextnode = p;
    p->prenode = q;
}

// index从序号0开始
void deleteElem(List list, int index, ElemType *e)
{
    Node *p = list->nextnode; // P指向待删除的元素的位置
    while (index && p) {
        index--;
        p = p->nextnode;
    }
    if (p == NULL) return; // 确保 index 位于合法范围以内
    if (p->nextnode) // 存在后继元素
        p->nextnode->prenode = p->prenode;
    p->prenode->nextnode = p->nextnode;
    *e = p->data;
    free(p);
}

int main()
{
    int i;
    ElemType e;
    int index;
    List list = initList();
    for (i = 0; i < 10; ++i)
        insertElem(list, i, 'a' + i);
    dispList(list);
    printf("input delete index = ");
    scanf("%d", &index);
    deleteElem(list, index, &e);
    printf("delete %c at %d\n", e, index);

    destoryList(list);
    return 0;
}
