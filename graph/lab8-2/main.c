#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100 // 最多处理的节点数

typedef int InfoType;
typedef struct ANode{   // 存储邻接边信息的结点
    int vertex;         // 连线指向的目的结点
    InfoType info;      // 用于存放连线上的权值信息
    struct ANode *nextarc;  // 指向下一个邻接边
} ArcNode;

typedef int Vertex;
typedef struct {
    Vertex data;    // 存放结点的信息
    ArcNode *firstarc;  // 结点的邻接边的链表
} VNode;

typedef VNode AdjList[N_MAX];

typedef struct {
    AdjList adjlist;
    int n;
    int e;
} AGraph;   // 基于邻接表的图

int visited[N_MAX] = {0, }; // 访问数组

// 从文件中建立一个图
AGraph * buildFromFile(const char *fileName)
{
    int i, j;
    int n;
    int tmp;
    ArcNode *p;
    FILE *fp = fopen(fileName, "r+");
    AGraph *ag = (AGraph *)malloc(sizeof(AGraph));

    fscanf(fp, "%d", &n);
    ag->n = n;
    for (i = 0; i < n; ++i)
        (ag->adjlist)[i].firstarc = NULL;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            fscanf(fp, "%d", &tmp);
            if (tmp != 0 && tmp != -1) {
                p = (ArcNode *)malloc(sizeof(ArcNode));
                p->vertex = j;
                p->info = tmp;
                p->nextarc = (ag->adjlist)[i].firstarc;
                (ag->adjlist)[i].firstarc = p;
                ag->e++;
            }
        }
    }
    fclose(fp);
    return ag;
}

void dispAdj(AGraph *ag)
{
    int i;
    ArcNode *p;
    for (i = 0; i < ag->n; ++i) {
        printf("%d: ", i);
        p = (ag->adjlist)[i].firstarc;
        while (p) {
            printf(" %d(%d) ", p->vertex, p->info);
            p = p->nextarc;
        }
        putchar('\n');
    }
}

// 对有向图 ag 从顶点 0 开始进行深度优先遍历
void dfsGraph(AGraph *ag, int v)
{
    ArcNode *p = (ag->adjlist)[v].firstarc;

    visited[v] = 1;
    printf("%d ", v);
    while (p) {
        if (visited[p->vertex] == 0) // 没有访问，继续深搜
            dfsGraph(ag, p->vertex);
        p = p->nextarc;
    }
}

// 非递归的深度优先遍历
void dfsGraph2(AGraph *ag, int v)
{
    int st[N_MAX];
    int top = -1;
    int i, w;
    ArcNode *p;
    int flag; // flag表示所有的邻接结点都访问过了，只有所有的邻接结点都被访问过了之后，结点才能够从栈中取出来
    for (i = 0; i < ag->n; ++i)
        visited[i] = 0;

    visited[v] = 1;
    printf("%d ", v);
    st[++top] = v;
    while(top != -1) {
        w = st[top];
        flag = 1;
        p = ag->adjlist[w].firstarc;
        while (p) {
            if (visited[p->vertex] == 0) {
                flag = 0; // 还有结点没有被访问
                st[++top] = p->vertex; // 邻接结点入栈
                visited[p->vertex] = 1;
                printf("%d ", p->vertex);
                break;
            }
            p = p->nextarc;
        }
        if (flag)
            top--;
    }

    putchar('\n');
}

// 广度优先遍历
void bfsGraph(AGraph *ag,  int v)
{
    ArcNode *p;
    int que[N_MAX];
    int front = 0, rear = 0;
    int i, w;
    for (i = 0; i < ag->n; ++i)
        visited[i] = 0;

    visited[v] = 1;
    printf("%d ", v);
    rear = (rear + 1) % N_MAX;
    que[rear] = v; // v进队
    while (front != rear) {
        front = (front + 1) % N_MAX;
        w = que[front]; // 出队
        p = ag->adjlist[w].firstarc;
        while (p) {
            if (visited[p->vertex] == 0) {
                visited[p->vertex] = 1;
                printf("%d ", p->vertex);
                rear = (rear + 1) % N_MAX;
                que[rear] = p->vertex;
            }
            p = p->nextarc;
        }
    }
}

int main()
{
    const char *fileName = "testG.txt";
    AGraph *ag = buildFromFile(fileName);
    dispAdj(ag);
    dfsGraph2(ag, 0);
    bfsGraph(ag, 0);
    putchar('\n');
    return 0;
}
