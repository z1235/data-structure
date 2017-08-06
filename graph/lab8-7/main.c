// 使用 Prim 计算从顶点0开始的最小生成树

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V_MAX 20
#define INF INT_MAX

// 图
int n = 6;
int map[][V_MAX] = {
    {0, 5, 8, 7, INF, 3},
    {5, 0, 4, INF, INF, INF},
    {8, 4, 0, 5, INF, 9},
    {7, INF, 5, 0, 5, INF},
    {INF, INF, INF, 5, 0, 1},
    {3, INF, 9, INF, 1, 0}
};

struct {
    int u;         // 边的头部
    int w;       // 边的权重
} closedge[V_MAX];      // 辅助数据结构，表示边， 其中序号表示边的尾部

int prim(int u)
{
    int i, j;
    int min, k; // 用于寻找最小值
    int ret = 0;
    // 将 u 加入到集合 U 中,当边的权重为0的时候，表示边已经加入到集合 U 中
    // closedge 维护了到 U-V 中顶点的最小边的集合
    for (i = 0; i < n; ++i) {
        closedge[i].u = u;
        closedge[i].w = map[u][i];
    }

    // 将其余节点加入到集合 V - U 中
    for (i = 0; i < n - 1; ++i) {
        min = INF;
        k = 0;
        for (j = 0; j < n; ++j) {
            if (closedge[j].w != 0 && closedge[j].w < min) {
                min = closedge[j].w;
                k = j;
            }
        } // end-for-j
        printf(" (%d->%d) w = %d\n", closedge[k].u, k, closedge[k].w);
        ret += closedge[k].w;
        for (j = 0; j < n; ++j) {
            if (closedge[j].w != 0 && map[k][j] < closedge[j].w) {
                closedge[j].w = map[k][j];
                closedge[j].u = k;
            }
        }
    } // end-for-i
    return ret;
}



int main()
{
    int s;
    int mincost = 0;
    scanf("%d", &s);
    mincost = prim(s); // 从s结点开始运行 prim 算法
    printf("%d\n", mincost);

    return 0;
}

