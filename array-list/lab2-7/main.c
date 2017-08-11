// 求两个多项式的加法和减法

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double coef;
    int exp;
} Poly;

typedef struct Node{
    Poly data;
    struct Node *nextnode; // 指向下一个节点
} Node, *List;

void dispPoly(List list)
{
    Node *p = list->nextnode;
    while (p) {
        if (p != list->nextnode && p->data.coef > 0) //p不是第一个节点，并且序号大于0
            printf("+");
        printf(" %.2lf ", p->data.coef);
        if (p->data.exp) printf("x^%d ", p->data.exp);
        p = p->nextnode;
    }
    printf("\n");
}

List buildList(Poly polyarray[], int n)
{
    int i;
    List head = (Node *)malloc(sizeof(Node));
    Node *newNode;
    Node *tail = head;
    head->nextnode = NULL;
    for (i = 0; i < n; ++i) {
        newNode = (Node *)malloc(sizeof(Node));
        newNode->data = polyarray[i];
        newNode->nextnode = tail->nextnode;
        tail->nextnode = newNode;
        tail = newNode;
    }
    return head;
}

// 使用插入排序对链表进行排序
void sortList(List L)
{
    Node *p;
    Node *q;
    Node *index;
    if (L->nextnode == NULL || L->nextnode->nextnode == NULL)
        return; // 空集或者单个元素直接返回
    p = L->nextnode->nextnode;
    L->nextnode->nextnode = NULL; // L中留下一个元素
    index = L->nextnode; // index最终指向插入位置的前驱结点
    while (p) {
        q = p->nextnode;
        index = L;
        // 循环，指导index到最后一个节点或者下一个节点的指数大于或等于p
        while (index->nextnode && index->nextnode->data.exp < p->data.exp)
            index = index->nextnode;
        p->nextnode = index->nextnode;
        index->nextnode = p;
        p = q;
    }
}

void addlist(List L1, List L2)
{
    Node *p2 = L2->nextnode;
    Node *p1;
    Node *index, *pre;
    Node *newNode;
    if (L1->nextnode == NULL || L2->nextnode == NULL) return; // 空集
    while (p2) {
        index = L1; // index指向最后一个元素或者下一个节点大于p2
        pre = NULL;
        while (index->nextnode && index->nextnode->data.exp <= p2->data.exp) {
            pre = index;
            index = index->nextnode;
        }
        if (index->data.exp == p2->data.exp) { // index节点元素等于p2
            index->data.coef += p2->data.coef;
            if (index->data.coef == 0) { // 删除这个节点
                pre->nextnode = index->nextnode;
                free(index);
            }
        }
        else { // 没有与其一致的节点，新增一个节点
            newNode = (Node *)malloc(sizeof(Node));
            newNode->data = p2->data;
            newNode->nextnode = index->nextnode;
            index->nextnode = newNode;
        }
        p2 = p2->nextnode;
    }
}



int main()
{
    Poly polyarray1[] = {{3.2, 3}, {2.5, 1}, {1.2, 0}, {-2.5, 5}};
    Poly polyarray2[] = {{-1.2, 0}, {2.5, 1}, {3.2, 3}, {2.5, 5}, {5.4, 10}};
    List list1 = buildList(polyarray1, sizeof(polyarray1)/sizeof(polyarray1[0]));
    List list2 = buildList(polyarray2, sizeof(polyarray2)/sizeof(polyarray2[0]));
    sortList(list1);
    sortList(list2);
    dispPoly(list1);
    dispPoly(list2);
    addlist(list1, list2);
    dispPoly(list1);


    return 0;
}
