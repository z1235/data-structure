// Folyd
// 采用弗洛伊德算法计算从有权图的某个顶点到达其余各顶点的最短路径的长度和最短路径
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define INF (INT_MAX/2)
#define N_MAX 100

int map[N_MAX][N_MAX];
int n;


void buildGraphFromFile(const char *fileName)
{
    int i, j;
    FILE *fp = fopen(fileName, "r+");
    assert(fp != NULL);
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            fscanf(fp, "%d", &map[i][j]);
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

void showArray(int A[][N_MAX], int path[][N_MAX])
{
    int i, j;
    printf("A:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (A[i][j] != INF) printf("%6d ", A[i][j]);
            else printf("%6s", "INF");
        }
        putchar('\n');
    }
    printf("path:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            printf("%3d", path[i][j]);
        putchar('\n');
    }
}

// 打印出从 i 到 j的路径信息

void reFindPath(int path[][N_MAX], int s, int d)
{
    int st[N_MAX];
    int top = -1;
    while (d != s) {
        st[++top] = d;
        d = path[s][d];
    }
    st[++top] = s;
    while (top != -1) {
        printf("%d ", st[top--]);
        if (top == -1) printf("\n");
        else printf("--> ");
    }
}
void dispPath(int A[][N_MAX], int path[][N_MAX])
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("from %d to %d cost %d: ", i, j, A[i][j]);
            reFindPath(path, i, j);
        }
        putchar('\n');
    }
}

void folyd()
{
    int i, j, k;
    int A[N_MAX][N_MAX];  // 邻接矩阵，记录了从 i 到 j 的最短路径
    int path[N_MAX][N_MAX]; // path 标记了从 i 到 j 是否有路径到达
    // 初始化辅助数组
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (map[i][j] != 0 || i == j) {
                A[i][j] =  map[i][j];
                path[i][j] = i;
            }
            else {
                A[i][j] = INF;
                path[i][j] = -1;
            }
        }
    } //end-init


    // dynamic progreamming
    for (k = 0; k < n; ++k) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
        printf("================k = %d==================\n\n", k);
        showArray(A, path);
    }

    dispPath(A, path);
}




int main()
{
    const char *fileName = "map.txt";
    buildGraphFromFile(fileName);
    dispGraph();
    folyd();

    return 0;
}
