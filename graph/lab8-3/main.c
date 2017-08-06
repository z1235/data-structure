#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

typedef int InfoType;
typedef struct AdjNode{ // 邻接边链表结点
    InfoType info; // 边的数据
    int vertex; // 边指向的结点
    struct AdjNode *nextadj; // 指向下一条邻接边
} AdjNode;

typedef int VertexDataType;
typedef struct VNode{ // 结点结构
    VertexDataType data; // 结点数据
    struct AdjNode *firstadj; // 指向邻接边链表
} VNode;


typedef VNode AdjList[N_MAX]; // 结点数组

typedef struct {  // 基于邻接表的图结构
    AdjList adjlist; // 邻接表
    int n;  // 结点数目
    int e;  // 边的数目
} Graph;

int visited[N_MAX];
int path[N_MAX];


Graph * buildFromFile(const char *fileName)
{
    int n;
    int i, j;
    int tmp;
    AdjNode *p;
    FILE *fp = fopen(fileName, "r+");
    Graph *g = (Graph *)malloc(sizeof(Graph));
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; ++i)
        g->adjlist[i].firstadj = NULL;
    g->n = n;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            fscanf(fp, "%d", &tmp);
            if (tmp != 0 && tmp != -1) {
                g->e++;
                p = (AdjList *)malloc(sizeof(AdjList));
                p->info = tmp;
                p->vertex = j;
                p->nextadj = g->adjlist[i].firstadj;
                g->adjlist[i].firstadj = p;
            } // end-if
        } // end-for
    } // end-for
    fclose(fp);
    return g;
}

// 求出从指定地点v出发的所有深度优先遍历序列并打印出来
// d表示已经存储的路径长， v表示递归起始点
// 注意都在不同的递归栈中 v 和 d都是不同的，在返回上层递归栈帧的时候，将自动归位 
void dfs(Graph *g, int v, int d)
{
    int i;
    AdjNode *p = g->adjlist[v].firstadj;
    visited[v] = 1;
    path[d++] = v;
    if (d == g->n) { // 结束了遍历
        for (i = 0; i < d; ++i)
            printf("%d ", path[i]);
        putchar('\n');
    }

    while (p) {
        if (visited[p->vertex] == 0) { // 从 v 的一个邻接点递归进行深度优先搜索
            dfs(g, p->vertex, d);
        }
        p = p->nextadj;
    }
    visited[v] = 0; // 递归到最深处, 返回恢复现场
}

void dispGraph(Graph *g)
{
    int i;
    AdjNode *p;
    for (i = 0; i < g->n; ++i) {
        printf("%d: ", i);
        p = g->adjlist[i].firstadj;
        while (p) {
            printf(" %d(%d) ", p->vertex, p->info);
            p = p->nextadj;
        }
        putchar('\n');
    } // end-for
}


int main()
{
    const char *fileName = "testG.txt";
    Graph *g = buildFromFile(fileName);
    dispGraph(g);
    // 从1开始的所有深度优先遍历序列
    dfs(g, 1, 0);
    return 0;
}
