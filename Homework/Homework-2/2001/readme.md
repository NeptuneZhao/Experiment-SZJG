### 2001 层次遍历建立二叉树及遍历

#### 实验内容

按层次遍历建立二叉树，并输出该二叉树的前序遍历、中序遍历和后序遍历的序列。

图1 ?

以上图所示二叉树为例，第一行输入为15，表示节点的个数，第二行输入为

> 1 2 3 4 5 6 7 8 9 # # # 10 # #

其中，#表示空，表示层次遍历序列。该案例应输出：

```plain
preOrderTraverse is: 1 2 4 8 9 5 3 6 10 7
inOrderTraverse is: 8 4 9 2 5 1 6 10 3 7
postOrderTraverse is: 8 9 4 5 2 10 6 7 3 1
```

**同一序列输出之间用空格隔开，不同序列换行输出。**

注：文件读写已经为你写好，序列

> 1 2 3 4 5 6 7 8 9 # # # 10 # #

将被转换成int数组

> 1 2 3 4 5 6 7 8 9 -1 -1 -1 10 -1 -1

其中，-1表示空。只输入一个 # 时，需要返回空二叉树（即三种遍历的结果都为空）！

**提示：可以使用队列来实现层序遍历构建二叉树。**

#### 输入输出格式

**输入：**

```plain
15 // 树结点个数
1 2 3 4 5 6 7 8 9 # # # 10 # # // #表示空
```

**输出：**

```plain
preOrderTraverse is: 1 2 4 8 9 5 3 6 10 7 // 前序遍历 
inOrderTraverse is: 8 4 9 2 5 1 6 10 3 7 // 中序遍历 
postOrderTraverse is: 8 9 4 5 2 10 6 7 3 1 // 后序遍历 
```

注：输出的每个数字前面都有一个空格，行末没有空格。因此输出格式应该类似于：

```c
    printf("inOrderTraverse is:"); // 英文冒号，后面不必再加空格
    for(int i = 0; i < strlen(data); i++)
        printf(" %d", %data[i]); // 元素前加空格
```

#### 一个非常棒的例子，但是不对

首先，我必须要对聪明婷小姐致敬。没有她，就没有本想法。

下面简述其创建树的过程。

```c
TreeNodePtr createTreeWithLevelOrder(int *data, int size)
{
    if (size <= 0 || data[0] == -1) return NULL;

    QueuePtr queue = InitQueue();
    TreeNodePtr root = createTreeNode(data[0], NULL, NULL);
    EnQueue(queue, root);
    int i = 1;
    while (i < size)
    {
        TreeNodePtr node = GetHead(queue);
        DeQueue(queue);
        if (data[i] != -1)   // 如果当前值不是-1，说明有左孩子
        {
            node->left = createTreeNode(data[i], NULL, NULL);
            EnQueue(queue, node->left);
        }
        i++;
        if (i >= size) break; // 如果已经到达数组末尾，退出循环
        if (data[i] != -1)   // 如果当前值不是-1，说明有右孩子
        {
            node->right = createTreeNode(data[i], NULL, NULL);
            EnQueue(queue, node->right);
        }
        i++;
    }
    return root;
}
```

小品一下，乍一看不会发现错误。具体错误在下述手记体现。

![我的示例](./sample.png)
