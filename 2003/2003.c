#include <stdio.h>
#include <stdlib.h>

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

int GlobalSummary = 0;

int IsLeftLeave(BiTree* node, BiTree* parent)
{
    if (node == NULL)
        return 0;
    // Is Leave
    else if (node -> lchild == NULL && node -> rchild == NULL)
    {
        // Is Left Child
        if (parent != NULL && parent -> lchild == node)
            return node -> index;
    }
    return 0;
    // 我犯了一个错误, 之前的代码是这样写的:
    // int IsLeftLeave(BiTree* node, BiTree* parent)
    // {
    //     if (node == NULL)
    //     return 0;
    //     // Is Leave
    //     else if (node -> lchild == NULL && node -> rchild == NULL)
    //     {
    //         // Is Left Child
    //         if (parent != NULL && parent -> lchild == node)
    // Here:
    //             return node -> index;
    //     }
    //     else
    //         return 0;
    // }
    // 那里, 如果不满足条件, 则直接退出了, 没有 return, 自然结果就是随机数啦
    // 我说怎么出一堆危险内存呢
}

// 随便找一个遍历就好了
void preOrderTraverse(BiTree* node, BiTree* parent)
{
    if (node == NULL)
        return;
    GlobalSummary += IsLeftLeave(node, parent);

    preOrderTraverse(node -> lchild, node);
    preOrderTraverse(node -> rchild, node);
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
    preOrderTraverse(root, NULL);
    printf("%d\n", GlobalSummary);

    free(nodes);
    free(root);

    return 0;
}
