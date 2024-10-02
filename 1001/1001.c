#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS "passed"

// All right
typedef struct node
{
    char id[11];
    int grade;
    struct node *next;
} list;

// 创建交叉列表
// All right
void create(list *a, list *b, int _before1, int _before2){
    // a 和 b 后面若干结点值相同
    // _before1 为跳过的 a 中的个数, 从第 _before1 + 1 个结点开始相交
    // _before2 为跳过的 b 中的个数, 从第 _before2 + 1 个结点开始相交
    // 相交方法是将 b 中的前一结点指向 a 中的首个相交结点
    list *p, *q;

    while (_before1--)
        a = a -> next;
    while (--_before2)
        b = b -> next;
    
    p = b -> next;
    b -> next = a;
    
    // 销毁野指针结点
    while (p)
    {
        q = p -> next;
        free(p);
        p = q;
    }
}

// 程序结束后销毁交叉列表
// All right
void destroy(list *a, list *b, list *_cross)
{
    list *p = _cross -> next, *q;
    while (p)
    {
        q = p -> next;
        free(p);
        p = q;
    }
    while (a != _cross)
    {
        q = a -> next;
        free(a);
        a = q;
    }
    while (b != _cross)
    {
        q = b -> next;
        free(b);
        b = q;
    }
    free(_cross);
}

// 打印单个结点
// All right
void print_one(list *node){
    printf("{ID:%s, Grade:%d}", node -> id, node -> grade);
    if (node -> next != NULL)
        printf("->");
    else
        printf("\n");
}

// 以下部分是需要学生自己实现的
// All right
void print_all(list *head)
{
    // 用于单个节点输出的函数 print_one 已提供
    // 请你实现遍历链表的逻辑
    list *p = head;
    while (p)
    {
        print_one(p);
        p = p -> next;
    }
}

// 新建一个 node 并返回
// node.grade = grade;
// node.next = NULL;
// All right
list* create_one(char *id, int grade)
{
    // malloc 的时候记得为转化为结构体指针
    list *node = (list*)malloc(sizeof(list));
    strcpy(node -> id, id);
    node -> grade = grade;
    node -> next = NULL;
    return node;
}

// 按照降序插入学生的成绩情况, 并返回链表头指针
// All right
list* add_one(list *head, list *node)
{
    list *p = head, *q = NULL;

    // 第一个
    if (head == NULL)
    {
        head = node;
        return head;
    }

    // p 是上一个 node
    // 四次错误的根源: 忘加等号了...
    while (p && (p -> grade >= node -> grade))
    {
        q = p;
        p = p -> next;
    }

    if (q == NULL)
    {
        node -> next = head;
        head = node;
    }
    else
    {
        q -> next = node;
        node -> next = p;
    }

    return head;
}

// 反转链表
// All right
list* reverse_one(list *head)
{
    list *p = head, *q = NULL, *r;
    while (p)
    {
        r = p -> next;
        p -> next = q;
        q = p;
        p = r;
    }
    return q;
}

// 找到相交的第一个结点
// All right
list* findCrossBeginNode(list *class1, list *class2) {
    // class1 和 class2 在后一部分完全重合 (结点的内存地址相同)
    // 请找出并返回开始相交的第一个结点
    // 请不 (bi) 要 (xu) 简单地通过结点结构体的成员来判断
    list *p = class1, *q = class2;
    while (p != q)
    {
        p = p -> next;
        q = q -> next;
        if (p == NULL)
            p = class2;
        if (q == NULL)
            q = class1;
    }
    return p;
}

int main()
{
    list *class1 = NULL, *class2 = NULL, *node;
    int num1, num2, i, grade, _before1, _before2;
    char id[11];

    // 读取两个班级的人数
    scanf("%d%d", &num1, &num2);

    // ???
    class1 = class2 = NULL;

    // 读取班级1的成绩
    for(i = 0; i < num1; i++)
    {
        scanf("%s%d", id, &grade);
        node = create_one(id, grade);
        class1 = add_one(class1, node);
    }

    // 读取班级2的成绩
    for(i = 0; i < num2; i++)
    {
        scanf("%s%d", id, &grade);
        node = create_one(id, grade);
        class2 = add_one(class2, node);
    }

    // 读取链表交叉之前的结点个数
    scanf("%d%d", &_before1, &_before2);

    // 输出1 存储列表结果
    class1 = reverse_one(class1);
    class2 = reverse_one(class2);

    printf("Store Linkedlist\n");
    print_all(class1);
    print_all(class2);

    // 输出2 反转列表结果
    class1 = reverse_one(class1);
    class2 = reverse_one(class2);
    printf("Reverse Linkedlist\n");
    print_all(class1);
    print_all(class2);

    // 创建交叉链表并找到第一个交点
    create(class1, class2, _before1, _before2);
    node = findCrossBeginNode(class1, class2);

    // 输出3 链表交点
    printf("Cross node\n");
    printf("{ID:%s, Grade:%d}\n", node -> id, node -> grade);

    // 销毁交叉链表
    destroy(class1, class2, node);

    return 0;
}