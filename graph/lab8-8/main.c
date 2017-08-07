// 使用kruskal算法求最小生成树
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N_MAX 100
int map[N_MAX][N_MAX];
int n;
int directed;

typedef struct {
    int u;
    int v;
    int w;
} Edge;
Edge edges[N_MAX];
int e_size;

int vunion[N_MAX]; // 用于区分不同的顶点集合，类似于 UnionFind 数组


int cmp(const void *a, const void *b)
{
    Edge *p = (Edge *)a;
    Edge *q = (Edge *)b;
    return p->w - q->w;
}

// 从矩阵中获得边集，并按照从小到大的顺序输入
void shordEdge()
{
    int i, j;
    Edge tmp;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (map[i][j]) {
                edges[e_size].u = i;
                edges[e_size].v = j;
                edges[e_size].w = map[i][j];
                e_size++;
            }
        }
    } // end-for
    // insertion sort
    // qsort(edges, e_size, sizeof(Edge), cmp);
    for (i = 1; i < e_size; ++i) {
        tmp = edges[i];
        for (j = i; j > 0 && edges[j - 1].w > tmp.w; j--)
            edges[j] = edges[j - 1];
        edges[j] = tmp;
    }
}



/*读取图数据并显示*/
void readGraphFromFile(const char *fileName)
{
    int w;
    int i, j;
    FILE *fp = fopen(fileName, "r+");
    assert(fp != NULL);

    fscanf(fp, "%d %d", &n, &directed);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            fscanf(fp, "%d", &w);
            map[i][j] = w;
        }
    }
    fclose(fp);
}

void dispGraph()
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            printf("%d ", map[i][j]);
        putchar('\n');
    }
}

/*kruskal 算法的实现*/
void kruskal()
{
    int m = 0; // 边集合个数
    int k = 0; // 指示寻找到的满足条件的最小边
    int i;
    int u, v;
    int minSpanWet = 0;
    // 初始化 Union 辅助数组， 用于判断是否形成环路
    for (i = 0; i < n; ++i)
        vunion[i] = i;


    while (m < n - 1) {
        // 找到一条最小的边，其中顶点位于不同的集合中
        u = edges[k].u;
        v = edges[k].v;
        // 判断需要加入的边的两个顶点 isConnected ?
        if (vunion[u] != vunion[v]) {
            m++;
            printf(" (%d, %d) w = %d\n", u, v, edges[k].w);
            minSpanWet += edges[k].w;
            // 进行一次 union 操作
            for (i = 0; i < n; ++i)
                if (vunion[i] == vunion[v])
                    vunion[i] = vunion[u];
        }
        k++; // 继续向后查找
    }
    printf("min: %d\n", minSpanWet);
}


int main()
{
    const char *fileName = "map.txt";
    readGraphFromFile(fileName);
    dispGraph();
    shordEdge();
    kruskal();

    return 0;
}
