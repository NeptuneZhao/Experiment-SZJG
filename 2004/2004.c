#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS "passed"

// 我也来玩点神秘的
#define __DEEP_LENGTH__ 16

typedef struct BinaryTreeNode
{
    int index;
    struct BinaryTreeNode *lchild, *rchild;
} BiTree;

BiTree* createNode(int index)
{
    BiTree* newNode = (BiTree*) malloc(sizeof(BiTree));

    newNode -> index = index;
    newNode -> lchild = newNode -> rchild = NULL;
    return newNode;
}

BiTree* createTree(int* nodes, int index, int size)
{
    if (index >= size || nodes[index] == -1)
        return NULL;
    
    BiTree* root = createNode(nodes[index]);

    root -> lchild = createTree(nodes, 2 * index + 1, size);
    root -> rchild = createTree(nodes, 2 * index + 2, size);
    return root;
}

int deepFS(BiTree *node, int end, char *path, int path_len)
{
    // Nodes is NULL, return 0
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
    if ( deepFS(node -> lchild, end, path, path_len) || deepFS(node -> rchild, end, path, path_len) )
        return 1;
    
    return 0;
}

void findPath(BiTree *root, int start, int end)
{
    BiTree *stack[__DEEP_LENGTH__], *cur = root;
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
            cur = cur -> lchild;
        }
        if (top != -1 && stack[top] -> index == start)
            break;
        cur = stack[top--] -> rchild;
    }

    if (!cur)
    {
        printf("Too Far!!!\n");
        return;
    }

    char path[__DEEP_LENGTH__ * 4] = {0};

    if (deepFS(cur, end, path, 0))
        printf("%s\n", path);
    else
        printf("Too Far!!!\n");
}

int main()
{
    int n, start, end;
    scanf("%d", &n);
    
    int* nodes = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        char input[3];
        scanf("%s", input);

        nodes[i] = input[0] == '#' ? -1 : atoi(input);
    }
    
    BiTree* root = createTree(nodes, 0, n, NULL);

    scanf("%d%d", &start, &end);
    findPath(root, start, end);

    free(nodes);
    free(root);

    return 0;
}
