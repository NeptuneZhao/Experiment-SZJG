# 数字排序

## 题目 [LeetCode 2191](https://leetcode.cn/problems/sort-the-jumbled-numbers/description/)

现在给出一个 `index` 从 `0` 开始的整数数组 `mapping`, 表示一个十进制数字的映射规则.

- `mapping[i] = j` 表示在这个规则下将数位 `i` 映射为数位 `j`.
- 一个整数**映射**后的值为: 将原数字每一个数位 `i` `(0 <= i <= 9)` 映射为 `mapping[i]`.

另外给出一个整数数组 `nums`, 将它其中每个数按照它们的映射后对应的数字以**非递减顺序**排序后输出.

## 注意

1. 两个数字映射后的对应数字大小相同, 那么它们将按照**输入中的相对顺序**进行排序.
2. `nums` 中的元素只有在排序的时候需要按照映射后的值进行比较, 返回的值应该是输入元素其本身.

## 输入输出规则

### 输入

- Line 1: the number of `nums`
- Line 2: the `mapping`
- Line 3: the `nums`

### 输出

- Line: the mapped `nums`

### Sample 1

#### Input-1

```c
3
8 9 4 0 2 1 3 5 7 6
991 338 38
```

#### I DO NOT KNOW WHETHER THERE EXISTS A SPACE AT THE END OF THE OUTPUT

(Maybe it is the correct output form.)

```c
338 38 991
```

### Sample 2

#### Input-2

```c
3
0 1 2 3 4 5 6 7 8 9
789 456 123
```

#### Output-2

```c
123 456 789
```

## 提示

- `mapping.length == 10`
- `0 <= mapping[i] <= 9`
- `mapping[i]` 的值互不相同
- $1 \leq nums.length \leq 3 * 10^4$
- $0 \leq nums[i] < 10^9$

## 实验报告要求的流程

为 `mapping` `numbers` 分配内存(前提是 `n` 已经读取了) ->

输入 `10` 个 `mapping` 规则 ->

输入 `n` 个 `origin` 并根据规则填充映射值 ->

根据映射值对 `numbers` 这个结构体数组进行归并排序 ->

打印
