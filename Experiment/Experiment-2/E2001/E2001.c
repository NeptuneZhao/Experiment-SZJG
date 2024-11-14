#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{
    int x, y, g, h, f;
    struct Node* parent;
} Node;

typedef struct PQueue
{
    Node* heap[100 * 100];
    int size;
} PriorityQueue;

void push(PriorityQueue* pq, Node* node)
{
    pq -> heap[pq -> size++] = node;
    int i = pq -> size -1;
    while (i && pq -> heap[i] -> f < pq -> heap[(i - 1) / 2] -> f)
    {
        Node* temp = pq -> heap[i];
        pq -> heap[i] = pq -> heap[(i - 1) / 2];
        pq -> heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node* pop(PriorityQueue* pq)
{
    Node* popped = pq -> heap[0];
    pq -> heap[0] = pq -> heap[--pq -> size];
    int i = 0;
    while (2 * i + 1 < pq -> size)
    {
        int smallest = i;
        if (pq -> heap[2 * i + 1] -> f < pq -> heap[smallest] -> f)
            smallest = 2 * i + 1;
        if (2 * i + 2 < pq -> size && pq -> heap[2 * i + 2] -> f < pq -> heap[smallest] -> f)
            smallest = 2 * i + 2;
        if (smallest != i)
        {
            Node* temp = pq -> heap[i];
            pq -> heap[i] = pq -> heap[smallest];
            pq -> heap[smallest] = temp;
            i = smallest;
        }
        else
            break;
    }
    return popped;
}

int isEmpty(PriorityQueue* pq)
{
    return pq -> size == 0;
}

int 
    a, b,
    pathLength = 0, moveIndex = 0, minDistance = 0,
    visited[100][100], distances[100][100];
char maze[100][100], moves[10000];

// 右下左上的 DFS 索引
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char dir[4] = {'R', 'D', 'L', 'U'};
char opp_dir[4] = {'L', 'U', 'R', 'D'};

int startX, startY, keyX, keyY, exitX, exitY;

void DFS(int x, int y)
{
    if (visited[x][y])
        return;
    visited[x][y] = 1;
    if (x == keyX && y == keyY)
        return;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < a && ny >=0 && ny < b && maze[nx][ny] != '1' && !visited[nx][ny])
        {
            moves[moveIndex++] = dir[i];
            DFS(nx, ny);
            // 找到了
            if (visited[keyX][keyY])
                return;
            // 回溯
            moves[moveIndex++] = opp_dir[i];
        }
    }
}

void BFS()
{
    int queue[100 * 100][2];
    int front = 0, rear = 0;
    queue[rear][0] = startX;
    queue[rear++][1] = startY;
    distances[startX][startY] = 0;
    visited[startX][startY] = 1;

    while (front < rear)
    {
        int x = queue[front][0];
        int y = queue[front++][1];
        if (x == keyX && y == keyY)
        {
            minDistance = distances[x][y];
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < a && ny >= 0 && ny < b && !visited[nx][ny] && maze[nx][ny] != '1')
            {
                visited[nx][ny] = 1;
                distances[nx][ny] = distances[x][y] + 1;
                queue[rear][0] = nx;
                queue[rear++][1] = ny;
            }
        }
    }
}

int inClosedList[100][100], inOpenList[100][100];
Node* nodeDetails[100][100];

void reconstructPath(Node* current)
{
    if (current == NULL)
        return;
    reconstructPath(current -> parent);
    printf("(%d,%d)", current -> x, current -> y);
}

void AStar()
{
    PriorityQueue openList;
    openList.size = 0;

    Node* startNode = malloc(sizeof(Node));
    startNode -> x = keyX;
    startNode -> y = keyY;
    startNode -> g = 0;
    startNode -> h = abs(keyX - (a - 1)) + abs(keyY - (b - 1));
    startNode -> f = startNode -> g + startNode -> h;
    startNode -> parent = NULL;
    
    push(&openList, startNode);
    inOpenList[keyX][keyY] = 1;
    nodeDetails[keyX][keyY] = startNode;

    while (!isEmpty(&openList))
    {
        Node* current = pop(&openList);
        inClosedList[current -> x][current -> y] = 1;
        printf("(%d,%d)", current -> x, current -> y);

        if (current -> x == exitX && current -> y == exitY)
        {
            // 路径重构
            printf("\n");
            Node* temp = current;
            Node* path[100 * 100];
            int path_len = 0;

            while (temp != NULL)
            {
                path[path_len++] = temp;
                temp = temp -> parent;
            }

            for (int i = path_len -1; i >=0; i--)
                printf("(%d,%d)", path[i] -> x, path[i] -> y);

            printf("\n");
            return;
        }

        for (int i =0; i < 4; i++)
        {
            int
                nx = current -> x + dx[i],
                ny = current -> y + dy[i];

            if (nx >= 0 && nx < a && ny >= 0 && ny < b && maze[nx][ny] != '1')
            {
                int gNew = current -> g + 1;
                int hNew = abs(nx - (a - 1)) + abs(ny - (b - 1));
                int fNew = gNew + hNew;

                if (!inClosedList[nx][ny] && (!inOpenList[nx][ny] || fNew < nodeDetails[nx][ny] -> f))
                {
                    Node* successor = malloc(sizeof(Node));
                    successor -> x = nx;
                    successor -> y = ny;
                    successor -> g = gNew;
                    successor -> h = hNew;
                    successor -> f = fNew;
                    successor -> parent = current;

                    push(&openList, successor);
                    inOpenList[nx][ny] = 1;
                    nodeDetails[nx][ny] = successor;
                }
            }
        }
    }
    // No path found
}

int main()
{
    scanf("%d %d", &a, &b);
    
    // 此处刷新缓冲区, 机动处理换行符
    // 有问题就删
    getchar();

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            maze[i][j] = getchar();
            if (maze[i][j] == '\n')
                maze[i][j] = getchar();
            if (maze[i][j] == '*')
            {
                startX = i;
                startY = j;
                maze[i][j] = '0';
            }
            else if (maze[i][j] == '$')
            {
                keyX = i;
                keyY = j;
                maze[i][j] = '0';
            }
            else if (maze[i][j] == '#')
            {
                exitX = i;
                exitY = j;
                maze[i][j] = '0';
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    DFS(startX, startY);
    for (int i = 0; i < moveIndex; i++)
        printf("%c", moves[i]);
    
    printf("\n");
    // 来计算最短路径
    memset(visited, 0, sizeof(visited));
    BFS();
    printf("%d\n", minDistance);
    AStar();

    return 0;
}
