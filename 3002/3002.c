#include <stdio.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

int graph[MAX_NODES][MAX_NODES];
int dist[MAX_NODES];
int visited[MAX_NODES];
int path[MAX_NODES];
int nodeCount, edgeCount;

// 初始化图的邻接矩阵
// 所有节点间的距离初始为 2147483647
// 除了自身到自身的距离为 0
void initializeGraph()
{
    for (int i = 0; i < nodeCount; i++)
        for (int j = 0; j < nodeCount; j++) graph[i][j] = i == j ? 0 : INF;
}

// 计算从起始节点到所有其他节点的最短路径
void dijkstra(const int start)
{
    for (int i = 0; i < nodeCount; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        path[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < nodeCount; i++)
    {
        int u = -1;
        for (int j = 0; j < nodeCount; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;

        if (dist[u] == INF) break;

        visited[u] = 1;

        for (int v = 0; v < nodeCount; v++)
        {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }
    }
}

void printPath(const int end)  // NOLINT(*-no-recursion)
{
    if (path[end] == -1)
    {
        printf("%d", end);
        return;
    }
    printPath(path[end]);
    printf("->%d", end);
}

// 连通性检查
int isConnected()
{
    dijkstra(0);
    for (int i = 0; i < nodeCount; i++)
        if (dist[i] == INF) return 0;
    return 1;
}

int calculateEccentricity(const int start)
{
    dijkstra(start);
    int maxDist = 0;
    for (int i = 0; i < nodeCount; i++)
        if (dist[i] != INF && dist[i] > maxDist) maxDist = dist[i];

    return maxDist;
}

// 计算每个节点的离心率，并据此计算直径和半径
void calculateDiameterAndRadius()
{
    int diameter = 0, radius = INF;

    for (int i = 0; i < nodeCount; i++)
    {
        const int ecc = calculateEccentricity(i);
        if (ecc > diameter) diameter = ecc;
        if (ecc < radius) radius = ecc;
    }

    printf("diameter:%d\n", diameter);
    printf("radius:%d\n", radius);
}

int main() {
    scanf("%d %d", &nodeCount, &edgeCount);  // NOLINT(*-err34-c)

    initializeGraph();

    for (int i = 0; i < edgeCount; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w); // NOLINT(*-err34-c)
        graph[u][v] = w;
        graph[v][u] = w; // Assuming undirected graph
    }

    if (isConnected())
    {
        printf("connected: 1\n");

        const int start = 1, end = 3;
        dijkstra(start);
        printf("the minimum fare between %d and %d: %d\n", start, end, dist[end]);

        printf("Path: ");
        printPath(end);
        printf("\n");

        calculateDiameterAndRadius();
    }
    else
        printf("connected: 0\n");

    return 0;
}
