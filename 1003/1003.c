#include <stdio.h>
#include <stdlib.h>

#define MaxSize 40

// All right
// 1003 - 队列
// 我全部重写了队列形式
// 喜欢勿喷, 不喜欢也别喷

typedef int ElementType;

typedef struct queue
{
    ElementType _data[MaxSize];
    int _front, _rear;
} Queue;

void InitQueue(Queue *queue)
{
    queue -> _front = queue -> _rear = 0;
    return;
}

void PrintQueue(Queue *queue)
{
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
    return;
}

// Opreator 4
// 需要在 main 中重写
void Enqueue(Queue *queue, ElementType element)
{
    if ((queue -> _rear + 1) % MaxSize == queue -> _front)
        return;
    queue -> _data[queue -> _rear] = element;
    queue -> _rear = (queue -> _rear + 1) % MaxSize;
    return;
}

// Opreator 5
// 需要在 main 中重写
ElementType Dequeue(Queue *queue)
{
    if ((queue -> _front) == (queue -> _rear))
    {
        printf("DeQueue failed\n");
        // NMLGB, 经典的人类错误
        // 我 TM 又忘了加大括号了
        return 2147483647;
    }
    ElementType temp = queue -> _data[queue -> _front];
    queue -> _front = (queue -> _front + 1) % MaxSize;
    return temp;
}

// Opreator 6
// 获取队列头元素
void GetHead(Queue *queue)
{
    if (queue -> _front == queue -> _rear)
    {
        printf("GetHead failed\n");
        return;
    }
    printf("GetHead: %d\n", queue -> _data[queue -> _front]);
    PrintQueue(queue);
    return;
}

// Opreator 7
// 判断是否为空
void IsEmpty(Queue *queue)
{
    if (queue -> _front == queue -> _rear)
        printf("The Queue is Empty\n");
    else
    {
        printf("The Queue is not Empty\n");
        PrintQueue(queue);
    }
    return;
}

void RefreshStdin()
{
    char c;
    while ( (c = getchar()) != '\n' && c != EOF );
}

int main()
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    InitQueue(queue);

    int mode, temp, num, step;

    while (scanf("%d", &mode))
    {
        if (mode == -1)
            return 0;
        switch (mode)
        {
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
                break;
        }
    }
    free(queue);
    return 0;
}