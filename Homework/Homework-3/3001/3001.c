#include <stdio.h>

#define MAX_NODES 100

typedef struct edge_
{
    int u, v;
} Edge;

int adjacencyMatrix[MAX_NODES][MAX_NODES], degree[MAX_NODES], nodeCount, edgeCount;

Edge edges[MAX_NODES];

// 输入：程序首先读取节点数和边数。然后读取每条边的信息
// (IMPORTANT) 更新邻接矩阵。

// 度计算：通过遍历邻接矩阵，计算每个节点的度

// 聚类系数计算：
// 对于每个节点，找出其邻居。

// 计算邻居之间实际存在的边数
// 计算邻居之间可能存在的最大边数
// 计算每个节点的聚类系数，并累加以计算平均值。

void calculateDegrees()
{
    for (int i = 0; i < nodeCount; i++)
    {
        degree[i] = 0;
        for (int j = 0; j < nodeCount; j++)
        {
            if (adjacencyMatrix[i][j])
                degree[i]++;
        }
    }
}

double calculateClusteringCoefficient()
{
    double totalClusteringCoefficient = 0.0;

    for (int i = 0; i < nodeCount; i++)
    {
        int neighborCount = 0;
        for (int j = 0; j < nodeCount; j++)
        {
            if (adjacencyMatrix[i][j])
                neighborCount++;
        }

        if (neighborCount < 2)
            continue;

        int actualEdges = 0;

        for (int j = 0; j < nodeCount; j++)
        {
            if (adjacencyMatrix[i][j])
            {
                for (int k = j + 1; k < nodeCount; k++)
                {
                    if (adjacencyMatrix[i][k] && adjacencyMatrix[j][k])
                        actualEdges++;
                }
            }
        }

        const int possibleEdges = neighborCount * (neighborCount - 1) / 2;
        totalClusteringCoefficient += (double)actualEdges / possibleEdges;
    }

    return totalClusteringCoefficient / nodeCount;
}

int main() {
    scanf("%d", &nodeCount); // NOLINT(*-err34-c)
    scanf("%d", &edgeCount); // NOLINT(*-err34-c)

    for (int i = 0; i < edgeCount; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w); // NOLINT(*-err34-c)
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }

    calculateDegrees();

    printf("degree distribution:\n");
    for (int i = 0; i < nodeCount; i++)
        printf("node%d:%d,", i, degree[i]);
    printf("\n");

    const double clusteringCoefficient = calculateClusteringCoefficient();
    printf("clustering coefficient:%.6f\n", clusteringCoefficient);

    return 0;
}