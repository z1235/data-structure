// 实现循环双链表的算法

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char ElemType;
typedef struct Node {
    ElemType data;
    struct Node *nextnode;
    struct Node *prenode;
} Node, * List;

List initList()
{
    List list = (List)malloc(sizeof(Node));
    list->nextnode = list;
    list->prenode = list;
    return list;
}

void deleteList(List list)
{
    Node *p = list; // p指向待删除的元素
    Node *q;
    while (p->nextnode != list) {
        q = p->nextnode;
        free(p);
        p = q;
    }
    free(p); // 删除最后一个元素
}

int isEmpty(List list)
{
    return list->nextnode == list;
}

int getListLength(List list)
{
    Node *p = list->nextnode;
    int ret = 0; // ret记录了list的长度
    while (p != list) {
        ret++;
        p = p->nextnode;
    }
    return ret;
}

void dispList(List list)
{
    Node *p = list->nextnode; // p循环遍历链表中
    while (p != list) {
        printf("%c", p->data);
        p = p->nextnode;
        if (p == list) printf("\n");
        else printf(" --> ");
    }
}

// 向循环双链表中插入元素
void insertList(List list, int index, ElemType e)
{
    Node *p; // 指向插入的节点
    Node *q = list; // q指向插入元素的前置节点
    assert(index >= 0);
    while (index && q->nextnode != list) {
        index--;
        q = q->nextnode;
    }
    assert(index == 0);
    p = (Node *)malloc(sizeof(Node));
    p->data = e;
    p->nextnode = q->nextnode;
    p->prenode = q;
    q->nextnode->prenode = p;
    q->nextnode = p;
}

void deleteElem(List list, int index, ElemType *e)
{
    Node *p = list->nextnode; // p最终指向删除的元素
    assert(index >= 0);
    while (index && p != list) {
        index--;
        p = p->nextnode;
    }
    assert(index == 0 && p != list);
    p->nextnode->prenode = p->prenode;
    p->prenode->nextnode = p->nextnode;
    *e = p->data;
    free(p);
}

int main()
{
    int i;
    int index;
    ElemType e;
    List list = initList();
    for (i = 0; i < 10; ++i)
        insertList(list, i, 'a' + i);
    dispList(list);
    printf("delete test!! input index = ");
    scanf("%d", &index);
    deleteElem(list, index, &e);
    printf("delete %c at %d\n", e, index);
    dispList(list);
    printf("insert test!! input index and elem: ");
    scanf("%d %c", &index, &e);
    printf("index = %d elem = %c\n", index, e);
    insertList(list, index, e);
    dispList(list);
    deleteList(list);
    return 0;
}
