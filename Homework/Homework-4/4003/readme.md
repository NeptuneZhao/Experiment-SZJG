# 4003 逆序对

## 题目描述

最近，Tom 和 Jerry 在上数据分析课。今天的课程内容是一个人类称之为“逆序对”的东西。

逆序对的定义如下：对于给定的一段正整数序列 ${a_i}$, 逆序对就是序列中满足 $a_i> a_j$ 且 $i < j$ 的有序对。

学习了这个概念后，他们决定比赛谁先算出给定的一段正整数序列中逆序对的数目。

可怜的 Tom 还在研究如何更快的暴力求解，你能帮 Jerry 想出一个更快的方法吗？
 
**注：序列中可能有重复数字。**

## 输入输出格式

第一行输入为一个整数 N（$1 <= N <= 100,000$），表示正整数序列共有 N 个正整数；

第二行输入为由N个正整数构成的序列 ${a_i}$。

满足对任意的 $a_i$ 有 $1 <= a_i <= 1,000,000,000$ 。

参考:

> int 最大值: $2, 147, 483, 647$
> 
> n 最大值: $1, 000, 000, 000$

- 输入:

> 6
>
> 5 4 2 6 3 1

- 输出：

一个整数 A，表示这个序列中逆序对的数目。

> 11