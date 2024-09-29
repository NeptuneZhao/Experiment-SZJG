#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 128

// HalfCooler 锐评 OJ 烂代码
// 什么玩意还要自定义 max?
// 谁教你的数组初始化 array[var]?
// 老师没教过你初始化不能用变量吗? 为什么不用 malloc?
// Github Copilot: 你这个代码写的什么玩意, 你这个代码写的什么玩意

// All right
typedef struct TreeNode
{
    int id;
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *TreeNodePtr;


// All right
typedef struct ListNode
{
    struct TreeNode *node; // 队列的值的类型是树节点指针
    struct ListNode *next;
} ListNode, *ListNodePtr;

// All right
typedef struct Queue
{
    ListNodePtr dummyHead;
    ListNodePtr tail;
    int size;
} *QueuePtr;

// 创建链表的节点
// All right
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next)
{
    ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
    curr -> node = node;
    curr -> next = next;
    return curr;
}

// 创建树节点
int TreeId = 0;

// All right
TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right)
{
    TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    curr -> id = TreeId++;
    curr -> val = val;
    curr -> left = left;
    curr -> right = right;
    return curr;
}

// 单链表队列初始化
// All right
QueuePtr InitQueue()
{
    QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
    TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
    queue -> size = 0;
    queue -> dummyHead = createListNode(dummyTreeNode, NULL);
    queue -> tail = queue -> dummyHead;
    return queue;
}

// 在 queue 的尾部添加一个元素的副本
// All right
void EnQueue(QueuePtr queue, TreeNodePtr node)
{
    ListNodePtr curr = createListNode(node, NULL);
    queue -> tail -> next = curr;
    queue -> tail = queue -> tail -> next;
    queue -> size++;
}

// 删除 queue 中的第一个元素
// All right
void DeQueue(QueuePtr queue)
{
    if (queue -> size == 0)
    {
        // NB 啊, 还会抛异常呢
        perror("error! the size of queue is zero when call DeQueue().");
        return;
    }
    ListNodePtr head = queue -> dummyHead -> next;
    queue -> dummyHead -> next = head -> next;
    queue -> size--;
    if (queue -> size == 0)
        queue -> tail = queue -> dummyHead;
    free(head);
    return;
}

// @param queue 队列
// @return 如果 queue 中没有元素, 返回 true
// All right
bool QueueEmpty(QueuePtr queue)
{
    return queue -> size == 0;
}

// @return queue 中第一个元素的引用
// All right
TreeNodePtr GetHead(QueuePtr queue)
{
    if (QueueEmpty(queue))
    {
        perror("error! the size of queue is zero when call front().");
        return NULL;
    }
    else
        return queue -> dummyHead -> next -> node;
}

// 将输入转换为数组
// All right
void getDigits(char *buff, int *data)
{
    int len = strlen(buff);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        int num = 0;
        if (buff[i] == '#')
        {
            num = -1;
            i++;
        }
        else
        {
            while (buff[i] != ' ' && buff[i] != '\0')
                num = num * 10 + (buff[i++] - '0');
        }
        data[index++] = num;
    }
}

// 创建 dot 可视化文件
// All right
void createDotFile(const char *filename, TreeNodePtr root, int MaxSize)
{
    // 文件指针
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");

    // 利用层次遍历构造
    QueuePtr queue = InitQueue();
    EnQueue(queue, root);
    int id = 1;

    while (!QueueEmpty(queue))
    {
        // 若队列不空, 继续遍历
        // 否则遍历结束
        TreeNodePtr curr = GetHead(queue);
        DeQueue(queue);
        if (curr == NULL) continue;
        fprintf(fp, "%d [shape=circle, label=\"%d\"];\n", curr -> id, curr -> val);
        
        if (curr -> left != NULL)
        {
            // 如果有左孩子，左孩子入队
            EnQueue(queue, curr -> left);
            fprintf(fp, "%d->%d;\n", curr -> id, curr -> left -> id);
        }

        id++;
        // 中间虚拟节点
        fprintf(fp, "_n%d [shape=circle, label=\"#\", style=invis];\n", id);
        fprintf(fp, "%d->_n%d [style=invis, weight=10];\n", curr -> id, id);
        
        if (curr -> right != NULL)
        {
            EnQueue(queue, curr -> right);
            fprintf(fp, "%d->%d;\n", curr -> id, curr -> right -> id);
        }
        id++;
    }
    fprintf(fp, "}\n");
    fclose(fp);
}


// 绘制二叉树图片,调用 createDotFile 并使用 system 执行命令
// All right
void plot(TreeNodePtr tree_root, int i, int size, char *name)
{
    char tree_filename[50], paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, size);

    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);
}


// 删除二叉树
// All right
void destoryTree(TreeNodePtr root)
{
    if (!root)
        return;
    if (root -> left)
    {
        destoryTree(root -> left);
        root -> left = NULL;
    }
    if (root -> right)
    {
        destoryTree(root -> right);
        root -> right = NULL;
    }
    free(root);
}

// 通过队列来实现层次遍历构建二叉树, 并返回二叉树的头结点
TreeNodePtr createTreeWithLevelOrder(int *data, int size)
{
    if (size == 0)
        return NULL;
    TreeNodePtr root = createTreeNode(data[0], NULL, NULL);
    QueuePtr queue = InitQueue();
    EnQueue(queue, root);
    int i = 1;
    while (i < size)
    {
        TreeNodePtr curr = GetHead(queue);
        DeQueue(queue);
        if (data[i] != -1)
        {
            TreeNodePtr left = createTreeNode(data[i], NULL, NULL);
            curr -> left = left;
            EnQueue(queue, left);
        }
        i++;
        if (i < size && data[i] != -1)
        {
            TreeNodePtr right = createTreeNode(data[i], NULL, NULL);
            curr -> right = right;
            EnQueue(queue, right);
        }
        i++;
    }
    return root;
}


// 前序遍历
void preOrderTraverse(TreeNodePtr root)
{
    if (root == NULL)
        return;
    printf("%d ", root -> val);
    preOrderTraverse(root -> left);
    preOrderTraverse(root -> right);
}

// 中序遍历
void inOrderTraverse(TreeNodePtr root)
{
    if (root == NULL)
        return;
    inOrderTraverse(root -> left);
    printf("%d ", root -> val);
    inOrderTraverse(root -> right);
}

// 后序遍历
void postOrderTraverse(TreeNodePtr root)
{
    if (root == NULL)
        return;
    postOrderTraverse(root -> left);
    postOrderTraverse(root -> right);
    printf("%d ", root -> val);
}

int main()
{
    int MAX_NUM = 10, num;
    char buff[SIZE];
    bool use_graphviz = false;

    int i = 0;
    while (scanf("%d\n", &num) == 1)
    {
        fgets(buff, SIZE, stdin);
        // 查找换行符
        char *pos = strchr(buff, '\n'); 
        if (pos)
            *pos = '\0';

        pos = strchr(buff, '\r');
        if (pos)
            *pos = '\0';
        int *data = (int*) malloc(sizeof(int) * num);

        getDigits(buff, data);
        TreeNodePtr tree_root = createTreeWithLevelOrder(data, num);

        printf("preOrderTraverse is:");
        preOrderTraverse(tree_root);
        printf("\n");

        printf("inOrderTraverse is:");
        inOrderTraverse(tree_root);
        printf("\n");

        printf("postOrderTraverse is:");
        postOrderTraverse(tree_root);

        // 通过 graphviz 可视化
        if (use_graphviz)
            plot(tree_root, i, num, "tree");
    }
}
