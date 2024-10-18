#include <stdio.h>
#include <stdlib.h>

#define MAX_DIS 65536

typedef char string[4];

typedef struct GraphNode
{
    int N, E; // N 是顶点数, E 是边数
    int** matrix; // 邻接矩阵
    string* vertex; // 节点的名字
} Graph;

/**
 * 创建一个节点数为 n 的图
 * @param n 节点个数
 * @return 这个图
 */
Graph createGraph(const int n)
{
    Graph g;
    g.N = n;
    g.E = 0;
    g.matrix = (int**) calloc(sizeof(int*), g.N);

    for (int i = 0; i < n; i++)
        g.matrix[i] = (int*) calloc(sizeof(int), g.N);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            g.matrix[i][j] = MAX_DIS;
    }

    for (int i = 0; i < n; i++)
        g.matrix[i][i] = 0;

    g.vertex = (string*) calloc(sizeof(string), g.N);
    return g;
}

/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(const Graph g, int* node_degree)
{
    if (node_degree == NULL || g.matrix == NULL)
        return;

    for (int i = 0; i < g.N; i++)
    {
        node_degree[i] = 0;
        for (int j = 0; j < g.N; j++)
        {
            if (g.matrix[i][j] != MAX_DIS)
                node_degree[i]++;
        }
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 聚类系数
 */
double clusteringCoefficient(Graph g)
{
    if (g.matrix == NULL)
        return 0;

    int* degree = calloc(sizeof(int), g.N);
    nodeDegree(g, degree);

    int triangle_num = 0;
    int triple_num = 0;

    for (int i = 0; i < g.N; i++)
    {
        for (int j = 0; j < g.N; j++)
        {
            for (int k = 0; k < g.N; k++)
            {
                if (g.matrix[i][j] != MAX_DIS && g.matrix[j][k] != MAX_DIS && g.matrix[i][k] != MAX_DIS)
                    triangle_num++;
                if (g.matrix[i][j] != MAX_DIS || g.matrix[j][k] != MAX_DIS || g.matrix[i][k] != MAX_DIS)
                    triple_num++;
            }
        }
    }
    free(degree);
    return (double)triangle_num / triple_num;
}

int main_()
{
    int node_num, edge_num;
    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);

    for(int i = 0; i < node_num; i++)
        sprintf(g.vertex[i], "%d", i);

    for (int i = 0; i < edge_num; i++)
    {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);

        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }

    int *degree = calloc(sizeof(int), g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i = 0; i < g.N; i++)
        printf("node%s:%d,", g.vertex[i], degree[i]);
    printf("\n");
    printf("clustering coefficient:%f\n", clusteringCoefficient(g));

    // Do we have to free by line?
    for (int i = 0; i < g.N; i++)
        free(g.matrix[i]);
    free(g.matrix);
    free(g.vertex);
    free(degree);
    return 0;
}