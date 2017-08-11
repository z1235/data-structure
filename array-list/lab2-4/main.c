// 实现循环单链表的各种基本运算
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char ElemType;
typedef struct Node {
    ElemType data;
    struct Node *nextnode;
} Node, * List;

// 初始化循环单链表
List initList()
{
    List p = (List)malloc(sizeof(Node)); // 头结点
    p->nextnode = p; // 头结点指向自己
    return p;
}

// 删除循环单链表
void deleteList(List list)
{
    Node *p = list; // p指向待删除的节点
    Node *q;
    printf("delete: ");
    while (p->nextnode != list) {
        q = p->nextnode; // q中记录了p下一个节点的位置
        if (p == list) printf(" head ");
        else printf("%3c", p->data);
        free(p);
        p = q;
    }
    printf("%3c", p->data);
    free(p);
}



// 判断是否是空集
int isEmpty(List list)
{
    return list->nextnode == list;
}

// 求取链表的长度
int lengthOfList(List list)
{
    Node *p = list->nextnode;
    int ret = 0;

    while (p != list) {
        ret++;
        p = p->nextnode;
    }
    return ret;
}

// index从0开始计数，返回为NULL表示没有找到
ElemType * getElemPoint(List list, int index)
{
    Node *p = list->nextnode; // p最终指向定位到的元素
    assert(index >= 0);

    while (index && p != list) {
        index--;
        p = p->nextnode;
    }
    if (p != list) return &(p->data);
    return NULL;
}


// 在链表中插入元素 index表示元素的位置
void insertElem(List list, int index, ElemType e)
{
    Node *p = list; // p最终指向插入位置的前驱结点
    Node *q;

    assert(index >= 0);
    while (index && p->nextnode != list) {
        index--;
        p = p->nextnode;
    }

    if (index == 0) {
        q = (Node *)malloc(sizeof(Node));
        q->data = e;
        q->nextnode = p->nextnode;
        p->nextnode = q;
    }
}

// 返回1表示删除成功，负数表示出现错误
int deleteElem(List list, int index, ElemType *e)
{
    Node *p = list; // p最终指向删除位置的前驱结点
    Node *q; // q指向删除的元素

    while (index && p->nextnode != list) {
        index--;
        p = p->nextnode;
    }
    if (p->nextnode != list) { // p不是最后一个结点
        q = p->nextnode;
        p->nextnode = q->nextnode;
        *e = q->data;
        free(q);
        return 1;
    }
    return -1;
}

void dispElem(List list)
{
    Node *p = list->nextnode;
    while (p != list) {
        printf("%3c", p->data);
        p = p->nextnode;
    }
    printf("\tlength = %d\n", lengthOfList(list));
}



int main()
{
    int i;
    int index;
    ElemType e;
    int ret;
    List list = initList();
    printf("empty ? %s\n", isEmpty(list) ? "Yes" : "No");
    for (i = 0; i < 10; ++i)
        insertElem(list, i, 'a' + i);
    dispElem(list);
    printf("empty ? %s\n", isEmpty(list) ? "Yes" : "No");
    printf("delete index = ");
    scanf("%d", &index);
    ret = deleteElem(list, index, &e);
    if (ret == 1) printf("delete %c OK at %d\n", e, index);
    else printf("delete error\n");
    dispElem(list);
    deleteList(list);
    return 0;
}
