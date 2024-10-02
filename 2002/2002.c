#include <stdio.h>
#include <stdlib.h>

// On the basis of 2001
#define PASS "passed"

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

void inOrderTraverse(BiTree* node)
{
    if (node == NULL)
        return;
    
    inOrderTraverse(node -> lchild);
    printf(" %d", node -> index);
    inOrderTraverse(node -> rchild);
}

// 有了遍历的思想, 递归这几行就很好理解了
// 我当时也是绞尽脑汁, 一直在想怎么把左右子树的指针交换
// 我没转过来的弯是, 交换了这个指针, 他的孩子也变化了
// 管他呢, 都是对称的, 无脑递归就行了
BiTree* invertTree(BiTree* root)
{
    if (root == NULL)
        return NULL;
    
    BiTree* temp = root -> lchild;
    root -> lchild = invertTree(root -> rchild);
    root -> rchild = invertTree(temp);
    return root;
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
    
    BiTree* root = invertTree(createTree(nodes, 0, n));

    printf("inOrderTraverse of invert trees is:");
    inOrderTraverse(root);
    printf("\n");

    free(nodes);
    free(root);

    return 0;
}
