#include <stdio.h>
#include <stdlib.h>

#define MaxSize 40
#define PASS "passed"

// All right
// 1003 - 队列
// 我全部重写了队列形式
// 喜欢勿喷, 不喜欢也别喷

// 再次强调, 拿 C 去写自己的运行库显然是不合理且荒谬的
// C 语言是一门死语言, 我们不应该强行添加任何新功能
// 如果想使用其他功能, 请移步 C++ 或者其他语言如 Java, C#
// Github Copilot: 但是这里是 OJ, 我们只能使用 C 语言, 所以我只能这样写了

typedef int ElementType;

typedef struct queue
{
    ElementType _data[MaxSize];
    int _front, _rear;
} Queue;

void InitQueue(Queue *queue)
{
    if (queue == NULL)
        return;
    queue -> _front = queue -> _rear = 0;
}

void PrintQueue(const Queue *queue)
{
    if (queue == NULL)
        return;
    int i = queue -> _front;
    printf("Queue: ");
    while (i != queue -> _rear)
    {
        printf("%d", queue -> _data[i]);
        if ((i + 1) % MaxSize != queue -> _rear)
            printf(" ");
        i = (i + 1) % MaxSize;
    }
    printf("\n");
}

// Operator 4
// 需要在 main 中重写
void Enqueue(Queue *queue, ElementType element)
{
    if (queue == NULL)
        return;
    if ((queue -> _rear + 1) % MaxSize == queue -> _front)
        return;
    queue -> _data[queue -> _rear] = element;
    queue -> _rear = (queue -> _rear + 1) % MaxSize;
}

// Operator 5
// 需要在 main 中重写
ElementType Dequeue(Queue *queue)
{
    if (queue == NULL)
        return 0;
    if (queue -> _front == queue -> _rear)
    {
        printf("DeQueue failed\n");
        // LMAO, 经典的人类错误
        // 我 TM 又忘了加大括号了
        return 2147483647;
    }
    const ElementType temp = queue -> _data[queue -> _front];
    queue -> _front = (queue -> _front + 1) % MaxSize;
    return temp;
}

// Operator 6
// 获取队列头元素
void GetHead(const Queue *queue)
{
    if (queue == NULL)
        return;
    if (queue -> _front == queue -> _rear)
    {
        printf("GetHead failed\n");
        return;
    }
    printf("GetHead: %d\n", queue -> _data[queue -> _front]);
    PrintQueue(queue);
}

// Operator 7
// 判断是否为空
void IsEmpty(const Queue *queue)
{
    if (queue == NULL)
        return;
    if (queue -> _front == queue -> _rear)
        printf("The Queue is Empty\n");
    else
    {
        printf("The Queue is not Empty\n");
        PrintQueue(queue);
    }
}

void RefreshStdin()
{
    int c;
    while ( (c = getchar()) != '\n' && c != EOF );
}

int main_()
{
    Queue *queue = malloc(sizeof(Queue));
    InitQueue(queue);

    int mode, temp, num, step;

    while (scanf("%d", &mode))
    {

        switch (mode)
        {
            case -1:
                free(queue);
                return -1;
            case 4:
                // Enqueue
                scanf("%d", &num);
                for (int i = 0; i < num; i++)
                {
                    scanf("%d", &temp);
                    Enqueue(queue, temp);
                }
                PrintQueue(queue);
                RefreshStdin();
                break;
            case 5:
                // Dequeue
                scanf("%d", &step);
                for (int i = 0; i < step; i++)
                {
                    temp = Dequeue(queue);
                    if (temp != 2147483647)
                    {
                        printf("DeQueue: %d\n", temp);
                        PrintQueue(queue);
                    }
                }
                RefreshStdin();
                break;
            case 6:
                // GetHead
                GetHead(queue);
                RefreshStdin();
                break;
            case 7:
                // IsEmpty
                IsEmpty(queue);
                RefreshStdin();
                break;
            default:
                RefreshStdin();
                break;
        }
    }
    free(queue);
    return 0;
}