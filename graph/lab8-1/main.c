#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef int InfoType;
#define V_MAX 100       // 最大顶点的个数
#define INF INT_MAX

// 定义邻接矩阵类型
typedef struct {
    int no;             // 顶点编号
    InfoType info;      // 定点的其他信息
} VertexType;

typedef struct {            // 图的定义
    int edge[V_MAX][V_MAX]; // 邻接矩阵
    VertexType vexs[V_MAX]; // 存放顶点信息
    int n;                  // 顶点的个数
    int e;                  // 边的个数
} MGraph;


// 定义邻接表类型
typedef struct ANode {          // 边的节点结构类型
    int adjvex; //该边的终点位置
    struct ANode *nextarc; // 指向下一条边的指针
    InfoType info;          // 该边的相关信息，这里用来存放权值
} ArcNode;

typedef int Vertex;
typedef struct VNode{  // 邻接表的表头节点类型
    Vertex data;        // 顶点信息
    ArcNode *firstarc; //
} VNode;

typedef VNode AdjList[V_MAX];   // AdjList 是邻接表类型

typedef struct {    // 图的邻接表类型
    AdjList adjlist;    // 邻接表
    int n;          // 存放顶点数
    int e;          // 存放边数
} ALGraph;

// 不带权图的算法
// 带权图的算法
// 显示邻接表
void dispMat1(MGraph *g)
{
    int i, j;
    for (i = 0; i < g->n; ++i) {
        for (j = 0; j < g->n; ++j) {
            if ((g->edge)[i][j] == INF) {
                printf("%-6s", "INF");
            }
            else {
                printf("%-6d", (g->edge)[i][j]);
            }
        }
        putchar('\n');
    }
}

void dispAdj1(ALGraph *ag)
{
    int i;
    ArcNode *p;
    for (i = 0; i < ag->n; ++i) {
        printf("%d: ", i);
        p = (ag->adjlist)[i].firstarc;
        while (p) {
            printf(" %d(%d) ", p->adjvex, p->info);
            p = p->nextarc;
        }
        putchar('\n');
    }
}

// 将邻接矩阵转换为邻接表
void mat2list1(MGraph *mg, ALGraph *ag)
{
    int i, j;
    ArcNode *p;
    for (i = 0; i < mg->n; ++i)     // 给所有的邻接表中的所有头节点的指针域赋初值
        (ag->adjlist)[i].firstarc = NULL;
    for (i = 0; i < mg->n; ++i) {
        for (j = 0; j < mg->n; ++j) {
            if ((mg->edge)[i][j] != 0 && (mg->edge)[i][j] != INF) {
                p = (ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->info = (mg->edge)[i][j];
                p->nextarc = (ag->adjlist)[i].firstarc;
                (ag->adjlist)[i].firstarc = p;

            }
        }
    }
    ag->n = mg->n;
    ag->e = mg->e;
}

void list2Mat(ALGraph *ag, MGraph *mg)
{
    int i, j;
    ArcNode *p;

    for (i = 0; i < ag->n; ++i)
        for (j = 0; j < ag->n; ++j)
            if (i == j) (mg->edge)[i][j] = 0;
            else (mg->edge)[i][j] = INF;


    for (i = 0; i < ag->n; ++i) {
        p = (ag->adjlist)[i].firstarc;
        while (p) {
            (mg->edge)[i][p->adjvex] = p->info;
            p = p->nextarc;
        }
    }
    mg->n = ag->n;
    mg->e = ag->e;
}

int main()
{
    int i, j;
    MGraph mg, mg1;
    ALGraph ag;
    int A[V_MAX][6] = {             // 0表示距离为0， 自己到自己的路径为0， INF表示路径为无穷到，表示无法到达
        {0, 5, INF, 7, INF, INF},
        {INF, 0, 4, INF, INF, INF},
        {8, INF, 0, INF, INF, 9},
        {INF, INF, 5, 0, INF, 6},
        {INF, INF, INF, 5, 0, INF},
        {3, INF, INF, INF, 1, 0}
    };

    mg.n = 6;
    mg.e = 10;
    for (i = 0; i < mg.n; ++i) {
        for (j = 0; j < mg.n; ++j) {
            mg.edge[i][j] = A[i][j];
        }
    }
    printf("matrix:\n");
    dispMat1(&mg);
    printf("change to adj:\n");
    mat2list1(&mg, &ag);
    dispAdj1(&ag);
    list2Mat(&ag, &mg1);
    dispMat1(&mg1);

    return 0;
}
