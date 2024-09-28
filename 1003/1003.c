#include <stdlib.h>
#include <stdio.h>

// 数组容量
#define MaxSize 40

#define PUSH 0
#define POP 1
#define GET_TOP 2
#define STACK_EMPTY 3
#define EXIT -1
#define ENQUEUE 4
#define DEQUEUE 5
#define GET_HEAD 6
#define QUEUE_EMPTY 7

typedef int DataType;

typedef struct stack
{
    DataType data[MaxSize];
    int top; // 栈顶指针
} Stack;

typedef struct queue
{
    Stack *stack_in;
    Stack *stack_out;
} Queue;

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
    int i = 0;
    for (; i <= S.top; i++)
    {
        seq[i] = S.data[S.top-i]; // 自栈顶至栈底
    }
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

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    Q -> stack_in = (Stack*)malloc(sizeof(Stack));
    Q -> stack_out = (Stack*)malloc(sizeof(Stack));
    InitStack(Q -> stack_in);
    InitStack(Q -> stack_out);
}

/**
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    if(StackEmpty(*Q.stack_out))
    {
        if(StackEmpty(*Q.stack_in))
            return 0;
        else
        {
            while(!StackEmpty(*Q.stack_in))
            {
                DataType temp;
                Pop(Q.stack_in, &temp);
                Push(Q.stack_out, temp);
            }
        }
    }
    GetTop(*Q.stack_out, e);
    return 1;
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    return StackEmpty(*Q.stack_in) && StackEmpty(*Q.stack_out);
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（真满和假满）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    if(QueueLength(*Q) == MaxSize)
        return 0;
    Push(Q -> stack_in, e);
    return 1;
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    if(StackEmpty(*Q -> stack_out))
    {
        if(StackEmpty(*Q -> stack_in))
            return 0;
        else
        {
            while(!StackEmpty(*Q -> stack_in))
            {
                DataType temp;
                Pop(Q -> stack_in, &temp);
                Push(Q -> stack_out, temp);
            }
        }
    }
    Pop(Q -> stack_out, e);
    return 1;
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(Q -> stack_in);
    InitStack(Q -> stack_out);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(*Q.stack_in) + StackLength(*Q.stack_out);
}

/**
 * 获取队列的一个数组拷贝
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    int i = 0;
    StackToArray(*Q.stack_in, seq);
    for (; i < StackLength(*Q.stack_out); i++)
    {
        seq[i+StackLength(*Q.stack_in)] = Q.stack_out -> data[StackLength(*Q.stack_out) - i - 1];
    }
}

void outputStack(Stack *S)
{
    int seq[MaxSize], i = 0;
    StackToArray(*S, seq);
    printf("Stack: ");
    for (i = 0; i < StackLength(*S); i++)
    {
        printf("%d", seq[i]);
        if(i<StackLength(*S) - 1){
            printf(" ");
        }
    }
    printf("\n");
}


void outputQueue(Queue *Q)
{
    int seq[MaxSize], i = 0;
    QueueToArray(*Q, seq);
    printf("Queue: ");
    for (i = 0; i < QueueLength(*Q); i++)
    {
        printf("%d", seq[i]);
        if(i<QueueLength(*Q) - 1){
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    InitQueue(Q);
    Stack *S = (Stack *)malloc(sizeof(Stack));
    InitStack(S);

    int mode, num, e, status;
    while (scanf("%d", &mode))
    {
        if (mode == EXIT)
        {
            break;
        }
        switch (mode)
        {
        case ENQUEUE:
            num = 0;
            scanf("%d", &num);
            while (num > 0)
            {
                num--;
                scanf("%d", &e);
                status = EnQueue(Q, e);
            }
            outputQueue(Q);
            break;
        case DEQUEUE:
            num = 0;
            scanf("%d", &num);
            while (num > 0)
            {
                num--;
                status = DeQueue(Q, &e);
                if(status)
                {
                    printf("DeQueue: %d\n", e);
                    outputQueue(Q);
                }
                else
                {
                    printf("DeQueue failed\n");
                }
            }
            break;
        case GET_HEAD:
            status = GetHead(*Q, &e);
            if(status)
            {
                printf("GetHead: %d\n", e);
                outputQueue(Q);
            }
            else
            {
                printf("GetHead failed\n");
            }
            break;
        case QUEUE_EMPTY:
            status = QueueEmpty(*Q);
            if(status)
            {
                printf("The Queue is Empty\n");
            }
            else
            {
                printf("The Queue is not Empty\n");
                outputQueue(Q);
            }
            break;
        default:
            break;
        }
    }
    free(Q);
    free(S);
    return 0;
}