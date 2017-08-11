// 求集合(使用单链表表示)的并、交和差表示

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct Node {
    ElemType data;
    struct Node *nextnode;
} Node, * List;

void dispList(List list)
{
    Node *p = list->nextnode;
    while (p) {
        printf("%3c", p->data);
        p = p->nextnode;
    }
    putchar('\n');
}

// 使用数组中的元素 创建一个链表
List createList(ElemType a[], int n)
{
    int i;
    List head = (List)malloc(sizeof(Node)); // 创建头结点
    head->nextnode = NULL;
    Node *tail = head; // tail始终指向最后一个节点
    Node *p; // P指向待插入的结点
    for (i = 0; i < n; ++i) {
        p = (Node *)malloc(sizeof(Node));
        p->data = a[i];
        p->nextnode = NULL;
        tail->nextnode = p;
        tail = p;
    }
    return head;
}

void deleteList(List list)
{
    Node *p = list; // p指向待删除的结点
    Node *q;
    while (p) {
        q = p->nextnode;
        free(p);
        p = q;
    }
}

// 对链表进行插入排序
void insertSort(List list)
{
    Node *p, *q, *index;
    if (list->nextnode == NULL) return;
    p = list->nextnode->nextnode; // p指向余下的元素
    list->nextnode->nextnode = NULL;
    while (p) {
        q = p->nextnode;
        index = list;
        while (index->nextnode && index->nextnode->data < p->data)
            index = index->nextnode;
        p->nextnode = index->nextnode;
        index->nextnode = p;
        p = q;
    }
}

// 链表的并集
List unionList(List list1, List list2)
{
    Node *list3 = (Node *)malloc(sizeof(Node)); // list3为两个链表的并
    Node *tail3 = list3;  // tail3指向list3的尾部
    Node *p1 = list1->nextnode, *p2 = list2->nextnode;
    Node *p3;
    list3->nextnode = NULL;
    while (p1 && p2) {
        p3 = (Node *)malloc(sizeof(Node));
        if (p1->data < p2->data) {
            p3->data = p1->data;
            p1 = p1->nextnode;
        }
        else if (p1->data > p2->data) {
            p3->data = p2->data;
            p2 = p2->nextnode;
        }
        else {
            p3->data = p1->data;
            p1 = p1->nextnode;
            p2 = p2->nextnode;
        }
        p3->nextnode = tail3->nextnode;
        tail3->nextnode = p3;
        tail3 = p3;
    } // end-while
    if (p1 == NULL) p1 = p2;
    while (p1) {
        p3 = (Node *)malloc(sizeof(Node));
        p3->data = p1->data;
        p3->nextnode = tail3->nextnode;
        tail3->nextnode = p3;
        tail3 = p3;
        p1 = p1->nextnode;
    }
    return list3;
}

// 链表的差集
List subsList(List L1, List L2)
{
    List L3 = (Node *)malloc(sizeof(Node));
    Node *tail3 = L3, *p3;
    Node *p1 = L1->nextnode;
    Node *p2;
    L3->nextnode = NULL;
    while (p1) {
        p2 = L2->nextnode;
        while (p2 && p2->data != p1->data)
            p2 = p2->nextnode;
        if (p2 == NULL) { // 在L2中找不到这个元素
            p3 = (Node *)malloc(sizeof(Node));
            p3->data = p1->data;
            p3->nextnode = tail3->nextnode;
            tail3->nextnode = p3;
            tail3 = p3;
        }
        p1 = p1->nextnode;
    }
    return L3;
}

// 链表的交集
List intersect(List L1, List L2)
{
    List L3 = (Node *)malloc(sizeof(Node));
    Node *tail3 = L3, *p3;
    Node *p1 = L1->nextnode;
    Node *p2;
    L3->nextnode = NULL;
    while (p1) {
        p2 = L2->nextnode;
        while (p2 && p2->data != p1->data)
            p2 = p2->nextnode;
        if (p2) { // 在L2中找到这个元素
            p3 = (Node *)malloc(sizeof(Node));
            p3->data = p2->data;
            p3->nextnode = tail3->nextnode;
            tail3->nextnode = p3;
            tail3 = p3; 
        } 
        p1 = p1->nextnode;
    }

    return L3;
}

int main()
{
    ElemType vec1[] = {'c', 'a', 'e', 'h'};
    ElemType vec2[] = {'f', 'h', 'b', 'g', 'd', 'a'};
    List L1 = createList(vec1, sizeof(vec1)/sizeof(vec1[0]));
    List L2 = createList(vec2, sizeof(vec2)/sizeof(vec2[0]));
    List L1_union_L2;
    List L1_sub_L2;
    List L1_interSect_L2;

    dispList(L1);
    dispList(L2);
    insertSort(L1);
    insertSort(L2);
    dispList(L1);
    dispList(L2);

    L1_union_L2 = unionList(L1, L2);
    printf("union set: ");
    dispList(L1_union_L2);

    L1_sub_L2 = subsList(L1, L2);
    printf("sub set: ");
    dispList(L1_sub_L2);

    L1_interSect_L2 = intersect(L1, L2);
    printf("intersect set: ");
    dispList(L1_interSect_L2);

    deleteList(L1_interSect_L2);
    deleteList(L1_sub_L2);
    deleteList(L1_union_L2);
    deleteList(L1);
    deleteList(L2);
    return 0;
}
