#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS "unpassed"

typedef struct BinaryTreeNode
{
    int index;
    struct BinaryTreeNode *lchild, *rchild, *parent;
} BiTree;

BiTree* createNode(int index, BiTree* parent)
{
    BiTree* newNode = (BiTree*) malloc(sizeof(BiTree));

    newNode -> index = index;
    newNode -> lchild = newNode -> rchild = NULL;
    newNode -> parent = parent;
    return newNode;
}

BiTree* createTree(int* nodes, int index, int size, BiTree* parent)
{
    if (index >= size || nodes[index] == -1)
        return NULL;
    
    BiTree* root = createNode(nodes[index], parent);

    root -> lchild = createTree(nodes, 2 * index + 1, size, root);
    root -> rchild = createTree(nodes, 2 * index + 2, size, root);
    return root;
}

// 第一步, 找到 index 对应的节点
// All right
BiTree* findNode(BiTree* node, int index)
{
    if (node == NULL)
        return NULL;
    else if (node -> index == index)
        return node;
    
    BiTree* left = findNode(node -> lchild, index);
    BiTree* right = findNode(node -> rchild, index);
    return left == NULL ? right : left;
}

// 第二步, 从初始节点开始遍历, 直到结束节点(如果找不到直接拜拜)
char* findChildNode(BiTree* beginNode, BiTree* endNode, char* path)
{

    if (beginNode == NULL)
        return "Too Far!!!";
    else if (beginNode == endNode)
    {
        return ";";
    }

    findChildNode(beginNode -> lchild, endNode, path);
    findChildNode(beginNode -> rchild, endNode, path);
}

int main()
{
    int n, a, b;
    scanf("%d", &n);
    
    int* nodes = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        char input[3];
        scanf("%s", input);

        nodes[i] = input[0] == '#' ? -1 : atoi(input);
    }
    
    BiTree* root = createTree(nodes, 0, n, NULL);
    char* num = (char*) malloc(2 * sizeof(char));
    scanf("%d%d", &a, &b);
    itoa(a, num, 10);
    BiTree *beginNode = findNode(root, a), *endNode = findNode(root, b);
    printf("%s\n", findChildNode(beginNode, endNode, num));

    free(nodes);
    free(root);

    return 0;
}
