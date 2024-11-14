#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n, m, Q;
int adj[1000][1000];
int dist[1000][1000];
int queue[1000];
int front, rear;

void bfs(int start) {
    int visited[1000] = {0};
    dist[start][start] = 0;
    front = rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] && !visited[v]) {
                dist[start][v] = dist[start][u] + 1;
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &Q);
    memset(adj, 0, sizeof(adj));
    memset(dist, -1, sizeof(dist));
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a][b] = 1;
        adj[b][a] = 1;
    }
    for (int i = 1; i <= n; i++) {
        bfs(i);
    }
    double total = 0.0;
    for (int i = 0; i < Q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        int count = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[x][j] != -1 && dist[x][j] <= y) {
                count++;
            }
        }
        total += count;
    }
    double expected = total / Q;
    printf("%.2f\n", expected);
    return 0;
}
