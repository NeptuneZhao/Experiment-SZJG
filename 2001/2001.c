#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// HalfCooler 锐评 OJ 烂代码
// 什么玩意还要自定义 max?
// 谁教你的数组初始化 array[var]?
// 老师没教过你初始化不能用变量吗? 为什么不用 malloc?
// Github Copilot: 你这个代码写的什么玩意, 你这个代码写的什么玩意

// HalfCooler 重写二叉树代码

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

void preOrderTraverse(BiTree* node)
{
    if (node == NULL)
        return;
    
    printf(" %d", node -> index);
    preOrderTraverse(node -> lchild);
    preOrderTraverse(node -> rchild);
}

void inOrderTraverse(BiTree* node)
{
    if (node == NULL)
        return;
    
    inOrderTraverse(node -> lchild);
    printf(" %d", node -> index);
    inOrderTraverse(node -> rchild);
}

void postOrderTraverse(BiTree* node)
{
    if (node == NULL)
        return;
    
    postOrderTraverse(node -> lchild);
    postOrderTraverse(node -> rchild);
    printf(" %d", node -> index);
}

int main()
{
    int n;
    scanf("%d", &n);
    
    int* nodes = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        char input[3];
        scanf("%s", input);

        nodes[i] = input[0] == '#' ? -1 : atoi(input);
    }
    
    BiTree* root = createTree(nodes, 0, n);

    printf("preOrderTraverse is:");
    preOrderTraverse(root);
    printf("\n");

    printf("inOrderTraverse is:");
    inOrderTraverse(root);
    printf("\n");

    printf("postOrderTraverse is:");
    postOrderTraverse(root);

    free(nodes);
    free(root);

    return 0;
}
