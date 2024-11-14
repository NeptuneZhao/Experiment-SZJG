#include <stdio.h>

int dist[500][500];

int main()
{
    int n, m, l, r;
    scanf("%d%d%d%d", &n, &m, &l, &r);

    // 带着距离的矩阵
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = 88888888;
        }
    }

    // 读入边
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if(dist[u][v] > w)
        {
            // 多边，让它保持最小
            dist[u][v] = dist[v][u] = w;
        }
    }

    // Floyd 算法
    for (int k = 1; k <= n; k++)
    {
        for (int u = 1; u <= n; u++)
        {
            for (int v = 1; v <= n; v++)
            {
                int maxUV = dist[u][v];
                int maxThroughK = (dist[u][k] > dist[k][v]) ? dist[u][k] : dist[k][v];
                if (maxUV > maxThroughK)
                    dist[u][v] = maxThroughK;
            }
        }
    }

    int count = 0;
    for (int u = 1; u <= n; u++)
    {
        for (int v = u + 1; v <= n; v++)
        {
            if (dist[u][v] >= l && dist[u][v] <= r)
                count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
