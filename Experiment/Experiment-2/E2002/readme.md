# 缴纳过路费

现在有 `m` 条道路将 `n` 座城市连接在一起，形成一个无向图网络。每条道路都是双向通行的，并且任意两座城市之间最多只有一条直接链接的道路。

现在有一个人要通过一条或多条道路从一个城市转移到另一座城市，他对于道路的评判标准是：所有道路之中，最高的过路费即被当作是这一次的过路费。

也就是说，假如从城市1到城市2需要经过三条道路，这三条道路的过路费分别是1，2，3。那么他认为从城市1到城市2需要的过路费就是3，即最大值。

现在给出输入示例：

```plain
5 5 1 2
1 2 2
1 3 5
1 4 1
2 4 5
2 5 4
```

## 输入示例解释

1. 第一行是四个整数 `n` `m` `l` `r` ，表示有 `n` 座城市、 `m` 条道路、 这个人心中预设的过路费下限 `l` 和上限 `r` ；
2. 接下来 `m` 行，每行都有三个整数 `u` `v` `w` ，代表城市 `u` 和城市 `v` 之间有一条道路，过路费是 `w`。输入可以保证每对城市之间最多只有一条直接连接的道路。

现在要设计程序帮助这个人计算一共有多少个城市对满足他的上下限。输出只有一个整数，代表了具有这么多的城市对，满足他的需求。
