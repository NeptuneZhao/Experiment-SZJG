#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000

typedef struct edge_
{
    int u, v, weight;
} Edge;

typedef struct subset_
{
    int parent, rank;
} Subset;

// 查找根并压缩
int find(Subset *subsets, const int i)  // NOLINT(*-no-recursion)
{
    if (subsets == NULL)
        return 0;

    // 不是就再找呗, 里边没有就是 parent
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// 使用秩策略合并两个集合
void unionSets(Subset *subsets, const int x, const int y)
{
    if (subsets == NULL)
        return;

    const int rootX = find(subsets, x), rootY = find(subsets, y);

    // 大的大
    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;

    // 小的小
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else
    {
        // 大小中间找
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// 用于排序, 其实相当于委托, 4002 实际上也是这样
int compareEdges(const void *a, const void *b)
{
    // 大的大
    // 小的小
    // 大小中间找
    // 中间没有就是 0
    const Edge *edgeA = (Edge*) a, *edgeB = (Edge*) b;
    return edgeA -> weight - edgeB -> weight;
}

// compareEdges 用于按权重对边进行排序
//
// kruskalMST(...)
// 首先对所有边按权重排序
// 然后依次选择边
// 确保不会形成环
// 直到形成最小生成树
int kruskalMST(Edge *edges, const int n, const int m)
{
    qsort(edges, m, sizeof(Edge), compareEdges);

    Subset *subsets = calloc(n , sizeof(Subset));
    for (int i = 0; i < n; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int mstWeight = 0, edgesInMST = 0;

    // 嘿嘿, ++i, 嘿嘿
    // 哈哈, i++, 哈哈
    for (int i = 0; i < m && edgesInMST < n - 1; ++i)
    {
        const int
            u = edges[i].u,
            v = edges[i].v,
            weight = edges[i].weight,

            setU = find(subsets, u),
            setV = find(subsets, v);

        if (setU != setV)
        {
            mstWeight += weight;
            edgesInMST++;
            unionSets(subsets, setU, setV);
        }
    }

    free(subsets);
    return mstWeight;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m); // NOLINT(*-err34-c)

    Edge edges[MAX_EDGES];

    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight); // NOLINT(*-err34-c)

    const int result = kruskalMST(edges, n, m);
    printf("%d", result);

    return 0;
}
