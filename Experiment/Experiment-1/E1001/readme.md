# 二叉搜索树-染色

## 题目描述 [LCP 52](https://leetcode.cn/problems/QO5KpG/description/)

一**棵**二叉搜索树, 根节点是 `root`, 树上各个节点值都不重复.

初始时, 所有节点均为蓝色 `blue`.

现在按照顺序对这棵二叉树进行若干次操作.

## Opreation: `ops[i] = [type, x, y]`

表示第 `i` 次操作:

- 当 type 是 0 时即 `while (!type)` 时, 将节点值在 `[x, y]` 内的节点变成 `blue`.
- 当 type 是 1 时即 `while (type)` 时, 将节点值在 `[x, y]` 内的节点变成 `red`.

输出办完事后, 红色节点数量.

## 注意

- 题目保证对于每个操作的 `x` 和 `y` 值定出现在二叉搜索树节点中.

## 实验报告要求的流程

输入元素个数 `N` ->

申请内存, 把即将输入的 `N` 个元素填充到 `nodes` 中 ->

输入操作次数 `n` ->

输入整行操作 `line` ->

用 `sscanf()` 将有效输入填充到 `edge` 中 ->

`edge`代表操作数, 遍历它使用 `filter_array` 进行操作 ->

操作过程记录 `red` 个数 `RedDeadRedemption` ->

操作完了打印个数
