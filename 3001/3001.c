#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __MAX_DIS__ 65536

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
Graph createGraph(int n)
{
    Graph g;
    g.N = n;
    g.matrix = (int**) calloc(sizeof(int*), g.N);

    for (int i = 0; i < n; i++)
        g.matrix[i] = (int*) calloc(sizeof(int), g.N);

    for (int i = 0; i < g.N; i++)
    {
        for (int j = 0; j < g.N; j++) 
            g.matrix[i][j] = __MAX_DIS__;
    }

    for (int i = 0; i < g.N; i++)
        g.matrix[i][i] = 0;

    g.vertex = (string*) calloc(sizeof(string), g.N);
    return g;
}

/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int* node_degree)
{
    for (int i = 0; i < g.N; i++)
    {
        node_degree[i] = 0;
        for (int j = 0; j < g.N; j++)
        {
            if (g.matrix[i][j] != __MAX_DIS__)
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
    int* degree = (int*) calloc(sizeof(int), g.N);
    nodeDegree(g, degree);

    int triangle_num = 0;
    int triple_num = 0;

    for (int i = 0; i < g.N; i++)
    {
        for (int j = 0; j < g.N; j++)
        {
            for (int k = 0; k < g.N; k++)
            {
                if (g.matrix[i][j] != __MAX_DIS__ && g.matrix[j][k] != __MAX_DIS__ && g.matrix[i][k] != __MAX_DIS__)
                    triangle_num++;
                if (g.matrix[i][j] != __MAX_DIS__ || g.matrix[j][k] != __MAX_DIS__ || g.matrix[i][k] != __MAX_DIS__)
                    triple_num++;
            }
        }
    }

    return (double)triangle_num / triple_num;
}

int main()
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

    int *degree = (int*) calloc(sizeof(int), g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i = 0; i < g.N; i++)
        printf("node%s:%d,", g.vertex[i], degree[i]);
    
    printf("\nclustering coefficient:%f\n", clusteringCoefficient(g));
    return 0;
}