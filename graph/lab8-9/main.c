// 采用 dijkstra 求取带权图的最短路径
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define INF INT_MAX
#define N_MAX 100
int map[N_MAX][N_MAX];
int n;
int direction;

// 从 s 点出发的最短路径
int minpath[N_MAX]; // 最短路径
int from[N_MAX];    // 到达该节点的最短路径的源
int sureset[N_MAX]; // 已确定最短路径的数组

void dijkstra(int s)
{
    int i;
    int k;
    int min = INF;
    // 确认源结点，并初始化辅助数组
    int surecnt = 1;
    sureset[s] = 1;
    for (i = 0; i < n; ++i) {
        if (map[s][i] != 0) { // 存在路径到达
            minpath[i] = map[s][i];
            from[i] = s;
        }
        else {
            minpath[i] = INF;
        }
    }
    minpath[s] = 0;

    while (surecnt < n) {
        // 最短路径数组中没有被确认的点
        min = INF;
        for (i = 0; i < n; ++i) {
            if (sureset[i] == 0 && minpath[i] < min) { // 没被确认
                min = minpath[i];
                k = i;
            }
        }
        // 确认 k,并更新相应的辅助数组
        // printf(" (%d %d) w = %d\n", from[k], k, map[from[k]][k]);
        sureset[k] = 1;
        for (i = 0; i < n; ++i) {
            if (sureset[i] == 0 && map[k][i] && minpath[i] > map[k][i] + minpath[k]) {
                from[i] = k;
                minpath[i] = map[k][i] + minpath[k];
            }
        }
        surecnt++;
    }
}

// 到达目的结点的路径
void showPath(int s, int d)
{
    int tmp;
    int st[N_MAX];
    int top = -1;
    printf("from %d to %d cost: %d:\t", s, d, minpath[d]);
    while (d != s) {
        st[++top] = d;
        d = from[d];
    }
    st[++top] = s;
    while (top != -1) {
        tmp = st[top--];
        printf("%d ", tmp);
        if (top == -1) printf("\n");
        else printf("--> ");
    }
}

void readGraphFromFile(const char *fileName)
{
    int i, j;
    FILE *fp = fopen(fileName, "r+");

    fscanf(fp, "%d %d", &n, &direction);
    assert(fp != NULL);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            fscanf(fp, "%d", &map[i][j]);
        }
    }
    fclose(fp);
}

void dispMap()
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%d ", map[i][j]);
        }
        putchar('\n');
    }
}

int main()
{
    const char *fileName = "map.txt";
    int s = 0;
    int d;
    readGraphFromFile(fileName);
    dispMap();
    dijkstra(s);

    for (d = 0; d < n; ++d) 
        showPath(s, d);
    return 0;
}
