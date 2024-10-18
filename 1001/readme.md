title: 1001-体测成绩

---

#### 一、实验目的

掌握线性表的链式存储结构和基本操作，重点巩固和体会链表的遍历等基本应用。

#### 二、实验内容

众所周知，大学生体测的成绩一般呈现逐年下降的趋势。

贴心的辅导员为了帮大家记录身体素质最好的时刻，决定统计一下大一新生的体测成绩。

**需求**

1. 存储链表：按头插法将两个班的成绩存储到链表中。注：输入的成绩是降序的，因此链表存储的成绩是升序的。
2. 反转链表：将建立的两个升序链表按降序进行反转。
3. 链表交点：辅导员亲自录入时，由于班级分数最低的若干同学恰好同分，她不小心将链表的尾部交叉到了一起，只保留了一部分同学。辅导员很着急，因为她想重点关注这些体测成绩吊车尾的学生，劝导他们多锻炼身体。现在辅导员请你帮她编程解决这个问题。

你的任务是编程找出两个交叉链表的第一个公共交点，你只能拿到两个链表的头结点。注：创建交叉链表的代码已给出。

#### 三、输入输出格式

- 输入分为三个部分

1. 两个班级的人数n1、n2
2. 两个班级的成绩（两个班分别降序）
3. 两个链表交叉之前的结点个数m1、m2

- 输入示例

```
5 6
Student1 100
Student2 90
Student3 80
Student4 70
Student5 60
Student6 95
Student7 88
Student8 82
Student9 80
Student10 70
Student11 60
3 4
```

- 输出也分为三个部分
1. 存储链表的结果（升序）
2. 反转链表的结果（降序）
3. 链表交点的结点

- 输出示例

```
Store Linkedlist
{ID:Student5, Grade:60}->{ID:Student4, Grade:70}->{ID:Student3, Grade:80}->{ID:Student2, Grade:90}->{ID:Student1, Grade:100}
{ID:Student11, Grade:60}->{ID:Student10, Grade:70}->{ID:Student9, Grade:80}->{ID:Student8, Grade:82}->{ID:Student7, Grade:88}->{ID:Student6, Grade:95}
Reverse Linkedlist
{ID:Student1, Grade:100}->{ID:Student2, Grade:90}->{ID:Student3, Grade:80}->{ID:Student4, Grade:70}->{ID:Student5, Grade:60}
{ID:Student6, Grade:95}->{ID:Student7, Grade:88}->{ID:Student8, Grade:82}->{ID:Student9, Grade:80}->{ID:Student10, Grade:70}->{ID:Student11, Grade:60}
Cross node
{ID:Student4, Grade:70}
```