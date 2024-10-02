title: 2002 翻转二叉树

#### 实验内容

给定一棵二叉树，求取该树的镜像，即翻转该二叉树，如图所示，并输出翻转后二叉树的中序遍历。

原图：我寻思也TM没图啊
翻转后：我寻思也TM没图啊

> inOrderTraverse of invert tress is: 7 3 10 6 1 5 2 9 4 8

#### 输入输出格式

**输入：**

> 15 // 树结点个数
> 1 2 3 4 5 6 7 8 9 # # # 10 # # // #表示空

**输出：**

> inOrderTraverse of invert trees is: 7 3 10 6 1 5 2 9 4 8 // 翻转后的中序遍历

注：输出的每个数字前面都有一个空格，行末没有空格。因此输出格式应该类似于：

```c
    printf("inOrderTraverse is:"); // 英文冒号，后面不必再加空格
    for(int i = 0; i < strlen(data); i++)
        printf(" %d", %data[i]); // 元素前加空格
```