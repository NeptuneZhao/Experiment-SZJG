#include <stdio.h>
#include <stdlib.h>

#define PASS "passed"

// 我可告诉您, 我是 C# 出身的程序员
// 对你们这些面向过程的挖煤工可是嗤之以鼻
// 谁家好人自己写堆栈 队列 二叉树啊?

// 再, 不要也不允许您评价我的代码
// 我的代码首推美观, 您写的那个可进不了我的眼睛
// 太肮脏了

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

// 虽然全局变量很危险, 但
// 这可是 C 语言
int GlobalSummary = 0;

// HalfCooler 锐评 C 语言程序员
// 能死就赶紧死吧, Rust 已经傲视群雄了

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
