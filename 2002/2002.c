#include <stdio.h>
#include <stdlib.h>

// On the basis of 2001
#define PASS "passed"

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

void inOrderTraverse(const BiTree* node) // NOLINT(*-no-recursion)
{
    if (node == NULL)
        return;
    
    inOrderTraverse(node -> left);
    printf(" %d", node -> index);
    inOrderTraverse(node -> right);
}

// 有了遍历的思想, 递归这几行就很好理解了
// 我当时也是绞尽脑汁, 一直在想怎么把左右子树的指针交换
// 我没转过来的弯是, 交换了这个指针, 他的孩子也变化了
// 管他呢, 都是对称的, 无脑递归就行了
BiTree* invertTree(BiTree* root) // NOLINT(*-no-recursion)
{
    if (root == NULL)
        return NULL;
    
    BiTree* temp = root -> left;
    root -> left = invertTree(root -> right);
    root -> right = invertTree(temp);
    return root;
}

int main_()
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
