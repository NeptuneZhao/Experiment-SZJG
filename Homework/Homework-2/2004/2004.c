#include <stdio.h>
#include <stdlib.h>

#define PASS "passed"

// 我也来玩点神秘的
#define DEEP_LENGTH 16

typedef struct BinaryTreeNode
{
    int index;
    struct BinaryTreeNode *left, *right;
} BiTree;

BiTree* createNode(const int index)
{
    BiTree* newNode = malloc(sizeof(BiTree));

    newNode -> index = index;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}

BiTree* createTree(int* nodes, const int index, const int size) // NOLINT(*-no-recursion)
{
    if (nodes == NULL)
        return NULL;
    if (index >= size || nodes[index] == -1)
        return NULL;
    
    BiTree* root = createNode(nodes[index]);

    root -> left = createTree(nodes, 2 * index + 1, size);
    root -> right = createTree(nodes, 2 * index + 2, size);
    return root;
}

// 太神秘啦!
int deepFS(BiTree *node, const int end, char *path, int path_len) // NOLINT(*-no-recursion)
{
    // Nodes are NULL, return 0
    // It means we don't find
    if (!node)
        return 0;
    
    path_len += sprintf(path + path_len, "%d->", node -> index);

    // If we find the end node, we return 1, and cut the end of the path "->"
    if (node -> index == end)
    {
        path[path_len - 2] = '\0';
        return 1;
    }

    // If the node is not the end node, we continue to find children
    if ( deepFS(node -> left, end, path, path_len) || deepFS(node -> right, end, path, path_len) )
        return 1;
    
    return 0;
}

// 太神秘啦!
void findPath(BiTree *root, int start, int end)
{
    BiTree *stack[DEEP_LENGTH], *cur = root;
    int top = -1;

    while (cur || top != -1)
    {
        while (cur)
        {
            // Don't forget the difference between ++top and top++
            // ++top means top = top + 1, top++ means top = top and top = top + 1
            stack[++top] = cur;
            if (cur -> index == start)
                break;
            cur = cur -> left;
        }
        if (top != -1 && stack[top] -> index == start)
            break;
        cur = stack[top--] -> right;
    }

    if (!cur)
    {
        printf("Too Far!!!\n");
        return;
    }

    char path[DEEP_LENGTH * 4] = {0};

    if (deepFS(cur, end, path, 0))
        printf("%s\n", path);
    else
        printf("Too Far!!!\n");
}

int main_()
{
    int n, start, end;
    scanf("%d", &n); // NOLINT(cert-err34-c)
    
    int* nodes = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        char input[3];
        scanf("%s", input); // NOLINT(cert-err34-c)

        nodes[i] = input[0] == '#' ? -1 : strtol(input, NULL, 10);
    }
    
    BiTree* root = createTree(nodes, 0, n);

    scanf("%d%d", &start, &end); // NOLINT(cert-err34-c)
    findPath(root, start, end);

    free(nodes);
    free(root);

    return 0;
}
