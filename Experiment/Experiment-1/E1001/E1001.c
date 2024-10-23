#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 嗨嗨, 我又来了奥!
// 全局变量真的爽
// 一直全局一直爽
int RedDeadRedemption = 0;

// 你看, 每过一轮就删去一点, 这是不是就大大减小了时间开销啦
// @param *array 待处理数组指针
// @param size 数组大小
// @param *new_size 返回出去新数组大小
// @param x 区间小值
// @param y 区间大值
// @param mode 红蓝
// @return 新数组指针
int* filter_array(const int *array, const int size, int *new_size, const int x, const int y, const int mode)
{
    int *new_array = calloc(size, sizeof(int));
    if (!new_array)
        return NULL;

    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] >= x && array[i] <= y)
        {
            if (mode)
                RedDeadRedemption++;
        }
        else
            new_array[count++] = array[i];
    }
    *new_size = count;
    // 似乎分配的内存没有 free
    // TODO
    return realloc(new_array, count * sizeof(int));
}

int main()
{
    int N, n, x, y, mode, count = 0;
    
    scanf("%d", &N); // NOLINT(*-err34-c)
    int *nodes = calloc(N, sizeof(int));

    // 此处还能再精简, 即把 -1 排除
    // TODO
    for (int i = 0; i < N; i++)
    {
        char input[10];
        scanf("%s", input);
        nodes[i] = (int)strtol(input, NULL, 10);
    }
    
    // 好好看, 好好学
    scanf("%d", &n); // NOLINT(*-err34-c)
    // 正在使用一种很新的刷新缓冲区的方法
    // 千万别忘了
    // Windows: End of line - CRLF
    // Unix: LF
    // 我们使用 ku ku 一顿删的方案刷新 stdin
    // 注意! stdin != __acrt_iob_func(0)
    // 上述只是在 Windows 中才有, stdin 实际上是一个被 define 的东西
    // fflush(stdin) 不咋好使, 大家可以试试, 然后反馈一下
    while (getchar() != '\n');
    
    int** edges = calloc(n, sizeof(int*));

    char line[32767];
    fgets(line, 32767, stdin);
    // 注意到有两个'['
    // 能不能用 ++line?
    char *ptr = line + 1;

    // 和 parent 一样, 双重保险
    // count = n 时, *ptr 不是 NULL!
    // #define NULL (void*)0
    while (*ptr && count < n)
    {
        // 也能用 strtol, 不过就麻烦多了, 这里不需要考虑安全性
        if (sscanf(ptr, "[%d %d %d]", &mode, &x, &y) == 3) // NOLINT(*-err34-c)
        {
            // 屎山
            edges[count] = (int*) calloc(3, sizeof(int));
            edges[count][0] = mode;
            edges[count][1] = x;
            edges[count][2] = y;
            count++;
        }
        ptr = strchr(ptr, ']');

        // 此处好像有点问题
        if (ptr)
            ptr += count < n - 1 ? 2 : 1;
    }

    // 倒着看, 因为每个 "下一次" 操作都会覆盖上次的操作
    // 所以我们倒序看操作, 再把每次被操作掉的数删了
    for (int i = n - 1; i > -1; i--)
        nodes = filter_array(nodes, N, &N, edges[i][1], edges[i][2], edges[i][0]);
    printf("%d", RedDeadRedemption);

    // 犯了一个低级错误
    // free(&nodes)
    // 非人哉!
    free(nodes);
    free(edges);

    return 0;
}
