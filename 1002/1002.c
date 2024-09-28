#include <stdlib.h>
#include <stdio.h>

#define PASS "passed"

// 数组容量
#define MaxSize 40

#define PUSH 0
#define POP 1
#define GET_TOP 2
#define STACK_EMPTY 3
#define EXIT -1

typedef int DataType;

typedef struct stack
{
    DataType data[MaxSize];
    int top; // 栈顶指针
} Stack;

/**
 * 初始化一个栈
 * @param S
 */
void InitStack(Stack *s)
{
    s -> top = -1;
}

/**
 * 向栈插入一个元素
 * @param s 操作栈
 * @param e 操作数
 * @return 成功返回1，否则返回0
 */
int Push(Stack *s, DataType e)
{
    if(s -> top == MaxSize - 1)
        return 0;
    s -> top++;
    s -> data[s -> top] = e;
    return 1;
}

/**
 * 从栈中弹出一个元素
 * @param S 操作栈
 * @param e 接受栈弹出的值
 * @return 成功返回1，否则返回0
 */
int Pop(Stack *S, DataType *e)
{
    if(S -> top == -1)
        return 0;
    *e = S -> data[S -> top];
    S -> top--;
    return 1;
}

/**
 * 获取栈顶元素，不删除该元素
 * @param S 操作栈
 * @param e 接受栈顶元素
 * @return 成功返回1，否则返回0
 */
int GetTop(Stack S, DataType *e)
{
    if(S.top == -1)
        return 0;
    *e = S.data[S.top];
    return 1;
}

/**
 * 判断栈是否空
 * @param S
 * @return 为空返回1，否则返回0
 */
int StackEmpty(Stack S)
{
    return S.top == -1;
}

/**
 * 获取栈的一个数组拷贝
 * @param S 操作栈
 * @param seq 栈中元素的一个拷贝
 */
void StackToArray(Stack S, DataType *seq)
{
    for (int i = 0; i <= S.top; i++)
        // 自栈顶至栈底
        seq[i] = S.data[S.top - i];
}

/**
 * 返回栈已使用长度
 * @param S 操作栈
 * @return 返回栈的长度
 */
int StackLength(Stack S)
{
    return S.top + 1;
}

void outputStack(Stack *S)
{
    int seq[MaxSize], i;
    StackToArray(*S, seq);
    printf("Stack: ");
    for (i = 0; i < StackLength(*S); i++)
    {
        printf("%d", seq[i]);
        if(i < StackLength(*S) - 1)
            printf(" ");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    Stack *S = (Stack*)malloc(sizeof(Stack));
    InitStack(S);
    int mode, num, e, status;
    while (scanf("%d", &mode))
    {
        if (mode == EXIT)
            break;
        switch (mode)
        {
            case PUSH:
                num = 0;
                scanf("%d", &num);
                while (num > 0)
                {
                    num--;
                    scanf("%d", &e);
                    status = Push(S, e);
                }
                outputStack(S);
                break;
            case POP:
                num = 0;
                scanf("%d", &num);
                while (num > 0)
                {
                    num--;
                    status = Pop(S, &e);
                    if(status)
                    {
                        printf("Pop: %d\n", e);
                        outputStack(S);
                    }
                    else
                        printf("Pop failed\n");
                }
                break;
            case GET_TOP:
                status = GetTop(*S, &e);
                if(status)
                {
                    printf("GetTop: %d\n", e);
                    outputStack(S);
                }
                else
                    printf("GetTop failed\n");
                break;
            case STACK_EMPTY:
                status = StackEmpty(*S);
                if(status)
                    printf("The Stack is Empty\n");
                else
                {
                    printf("The Stack is not Empty\n");
                    outputStack(S);
                }
                break;
            default:
                break;
        }
    }
    free(S);
    return 0;
}