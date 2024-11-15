#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 50
#define MAX_COL 50

typedef struct {
    int x, y;
} Point;

typedef struct Node {
    Point pt;
    int g, h, f;
    struct Node* parent;
    struct Node* next;
} Node;

char maze[MAX_ROW][MAX_COL];
int visited[MAX_ROW][MAX_COL];
int a, b;

char path[1000];
int pathLen = 0;
int minSteps = -1;

Point start, keyPos, exitPos;

void readMaze() {
    scanf("%d %d", &a, &b);
    for (int i = 0; i < a; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j < b; j++) {
            if (maze[i][j] == '*') {
                start.x = i;
                start.y = j;
            } else if (maze[i][j] == '$') {
                keyPos.x = i;
                keyPos.y = j;
            } else if (maze[i][j] == '#') {
                exitPos.x = i;
                exitPos.y = j;
            }
        }
    }
}

int dx[4] = {0, 1, 0, -1}; // Right, Down, Left, Up
int dy[4] = {1, 0, -1, 0};
char dir[4] = {'R', 'D', 'L', 'U'};
char backDir[4] = {'L', 'U', 'R', 'D'};

int dfsFlag = 0;

void dfs(int x, int y, int steps) {
    if (dfsFlag) return;
    if (x == keyPos.x && y == keyPos.y) {
        if (minSteps == -1 || steps < minSteps) {
            minSteps = steps;
        }
        dfsFlag = 1;
        return;
    }

    visited[x][y] = 1;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        // Check bounds and if cell is walkable and not visited
        if (nx >= 0 && nx < a && ny >= 0 && ny < b &&
            maze[nx][ny] != '1' && !visited[nx][ny]) {
            path[pathLen++] = dir[i];
            dfs(nx, ny, steps + 1);
            if (dfsFlag) return;
            path[pathLen++] = backDir[i];
        }
    }

    visited[x][y] = 0;
}

Node* openList = NULL;
Node* closedList = NULL;

void addNode(Node** list, Node* node) {
    node->next = *list;
    *list = node;
}

Node* popBestNode() {
    Node *prev = NULL, *bestPrev = NULL, *cur = openList, *best = NULL;
    int bestF = -1;
    while (cur) {
        int f = cur->f;
        if (bestF == -1 || f < bestF ||
            (f == bestF && (cur->pt.x > best->pt.x ||
            (cur->pt.x == best->pt.x && cur->pt.y > best->pt.y)))) {
            bestF = f;
            best = cur;
            bestPrev = prev;
        }
        prev = cur;
        cur = cur->next;
    }
    if (bestPrev) {
        bestPrev->next = best->next;
    } else {
        openList = best->next;
    }
    return best;
}

int inList(Node* list, int x, int y) {
    while (list) {
        if (list->pt.x == x && list->pt.y == y) return 1;
        list = list->next;
    }
    return 0;
}

void printPath(Node* node) {
    if (node == NULL) return;
    printPath(node->parent);
    printf("(%d,%d)", node->pt.x, node->pt.y);
}

void aStar() {
    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->pt = keyPos;
    startNode->g = 0;
    startNode->h = abs(keyPos.x - exitPos.x) + abs(keyPos.y - exitPos.y);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = NULL;
    startNode->next = NULL;
    openList = startNode;

    while (openList) {
        Node* current = popBestNode();
        addNode(&closedList, current);
        printf("(%d,%d)", current->pt.x, current->pt.y);

        if (current->pt.x == exitPos.x && current->pt.y == exitPos.y) {
            // Path found
            printf("\n");
            printPath(current);
            printf("\n");
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current->pt.x + dx[i];
            int ny = current->pt.y + dy[i];
            if (nx >= 0 && nx < a && ny >= 0 && ny < b &&
                maze[nx][ny] != '1' && !inList(closedList, nx, ny)) {
                int gNew = current->g + 1;
                int hNew = abs(nx - exitPos.x) + abs(ny - exitPos.y);
                int fNew = gNew + hNew;

                Node* successor = NULL;
                Node* temp = openList;
                while (temp) {
                    if (temp->pt.x == nx && temp->pt.y == ny) {
                        successor = temp;
                        break;
                    }
                    temp = temp->next;
                }

                if (successor == NULL) {
                    successor = (Node*)malloc(sizeof(Node));
                    successor->pt.x = nx;
                    successor->pt.y = ny;
                    successor->g = gNew;
                    successor->h = hNew;
                    successor->f = fNew;
                    successor->parent = current;
                    addNode(&openList, successor);
                } else if (fNew < successor->f ||
                           (fNew == successor->f && (nx > successor->pt.x ||
                           (nx == successor->pt.x && ny > successor->pt.y)))) {
                    successor->g = gNew;
                    successor->h = hNew;
                    successor->f = fNew;
                    successor->parent = current;
                }
            }
        }
    }
    printf("\n");
}

int main() {
    readMaze();
    memset(visited, 0, sizeof(visited));
    dfsFlag = 0;
    dfs(start.x, start.y, 0);
    for (int i = 0; i < pathLen; i++) {
        printf("%c", path[i]);
    }
    printf("\n%d\n", minSteps);
    aStar();
    return 0;
}
