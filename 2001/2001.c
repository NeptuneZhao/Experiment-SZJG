#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode {
    int id;
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef struct ListNode {
    struct TreeNode *node; // 队列的值的类型是树节点指针
    struct ListNode *next;
} ListNode, *ListNodePtr;

typedef struct Queue {
    ListNodePtr dummyHead;
    ListNodePtr tail;
    int size;
} *QueuePtr;

// 创建链表的节点
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next) {
    ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
    curr->node = node;
    curr->next = next;
    return curr;
}

// 创建树的节点
int TreeId = 0;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right) {
    TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    curr->id = TreeId++;
    curr->val = val;
    curr->left = left;
    curr->right = right;
    return curr;
}

// 单链表队列初始化
QueuePtr InitQueue() {
    QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
    TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
    queue->size = 0;
    queue->dummyHead = createListNode(dummyTreeNode, NULL);
    queue->tail = queue->dummyHead;
    return queue;
}

// 在 queue 的尾部添加一个元素的副本
void EnQueue(QueuePtr queue, TreeNodePtr node) {
    ListNodePtr curr = createListNode(node, NULL);
    queue->tail->next = curr;
    queue->tail = queue->tail->next;
    queue->size++;
}

// 删除 queue 中的第一个元素
void DeQueue(QueuePtr queue) {
    if (queue->size == 0) {
        perror("error! the size of queue is zero when call DeQueue().");
        return;
    }
    ListNodePtr head = queue->dummyHead->next;
    queue->dummyHead->next = head->next;
    queue->size--;
    if (queue->size == 0) queue->tail = queue->dummyHead;
    free(head);
}

// 如果 queue 中没有元素, 返回 true
bool QueueEmpty(QueuePtr queue) {
    return queue->size == 0;
}

// 返回 queue 中第一个元素的引用
TreeNodePtr GetHead(QueuePtr queue) {
    if (QueueEmpty(queue)) {
        perror("error! the size of queue is zero when call front().");
        return NULL;
    } else {
        return queue->dummyHead->next->node;
    }
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

// 将输入转换为数组
void getDigits(char *buff, int *data) {
    int len = strlen(buff);
    int index = 0;
    for (int i = 0; i < len; i++) {
        int num = 0;
        if (buff[i] == '#') {
            num = -1;
            i++;
        } else {
            while (buff[i] != ' ' && buff[i] != '\0') {
                num = num * 10 + (buff[i++] - '0');
            }
        }
        data[index++] = num;
    }
}

// 创建 dot 可视化文件
void createDotFile(const char *filename, TreeNodePtr root, int MaxSize) {
    FILE *fp = fopen(filename, "w");    // 文件指针
    if (fp == NULL) {   // 为NULL则返回
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // 开头
    // 利用层次遍历构造
    QueuePtr queue = InitQueue();
    EnQueue(queue, root);
    int id = 1;
    while (!QueueEmpty(queue)) { // 若队列不空，继续遍历。否则，遍历结束
        TreeNodePtr curr = GetHead(queue);
        DeQueue(queue);
        if (curr == NULL) continue;
        fprintf(fp, "%d [shape=circle, label=\"%d\"];\n", curr->id, curr->val);
        if (curr->left != NULL) { // 如果有左孩子，左孩子入队
            EnQueue(queue, curr->left);
            fprintf(fp, "%d->%d;\n", curr->id, curr->left->id);
        }
        id++;
        // 中间虚拟节点
        fprintf(fp, "_n%d [shape=circle, label=\"#\", style=invis];\n", id);
        fprintf(fp, "%d->_n%d [style=invis, weight=10];\n", curr->id, id);
        if (curr->right != NULL) { // 如果有右孩子，右孩子入队
            EnQueue(queue, curr->right);
            fprintf(fp, "%d->%d;\n", curr->id, curr->right->id);
        }
        id++;
    }
    fprintf(fp, "}\n"); // 结尾
    fclose(fp); // 关闭IO
}


// 绘制二叉树图片,调用 createDotFile 并使用 system 执行命令
void plot(TreeNodePtr tree_root, int i, int size, char *name) {
    char tree_filename[50], paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, size);
    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);
}


// 删除二叉树
void destoryTree(TreeNodePtr root) {
    if (!root) return;
    if (root->left) {
        destoryTree(root->left);
        root->left = NULL;
    }
    if (root->right) {
        destoryTree(root->right);
        root->right = NULL;
    }
    free(root);
}

/** TODO:  任务一：请你通过队列来实现层次遍历构建二叉树，并返回二叉树的头结点 */

TreeNodePtr createTreeWithLevelOrder(int *data, int size) {

}


/** TODO: 任务一：请你输出该二叉树的前序遍历、中序遍历、后序遍历的序列 */
/**
 * ================================================
 * ||                  前序遍历                   ||
 * ================================================
 */
void preOrderTraverse(TreeNodePtr root) {

}

/**
 * ================================================
 * ||                  中序遍历                   ||
 * ================================================
 */
void inOrderTraverse(TreeNodePtr root) {

}

/**
 * ================================================
 * ||                  后序遍历                   ||
 * ================================================
 */
void postOrderTraverse(TreeNodePtr root) {

}



int main() {

    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    int num;
    bool use_graphviz = false;



    int i = 0;
    while (scanf("%d\n", &num) == 1) {
        fgets(buff, SIZE, stdin);
        char *pos = strchr(buff, '\n');          //查找换行符
        if (pos)                            //如果find不为空指针
            *pos = '\0';                    //就把一个空字符放在这里

        // Mac/Linux 替换\r
        pos = strchr(buff, '\r');
        if (pos)
            *pos = '\0';

        int size = num;
        int data[size];
        getDigits(buff, data);
        TreeNodePtr tree_root = createTreeWithLevelOrder(data, size);
        printf("preOrderTraverse is:");
        preOrderTraverse(tree_root);
        printf("\n");
        printf("inOrderTraverse is:");
        inOrderTraverse(tree_root);
        printf("\n");
        printf("postOrderTraverse is:");
        postOrderTraverse(tree_root);

        /** 通过 graphviz 可视化 */
        if (use_graphviz) {
            plot(tree_root, i, size, "tree");
        }
    }
}
