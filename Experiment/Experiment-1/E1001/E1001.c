#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RedDeadRedemption = 0;

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
    // CLion tells me that the allocated memory is not freed
    // What can I do?
    return realloc(new_array, count * sizeof(int));
}

int main()
{
    int N, n, x, y, mode, count = 0;
    
    scanf("%d", &N); // NOLINT(*-err34-c)
    int *nodes = calloc(N, sizeof(int));

    // 此处还能再精简, 即把 -1 排除
    for (int i = 0; i < N; i++)
    {
        char input[10];
        scanf("%s", input);
        nodes[i] = (int)strtol(input, NULL, 10);
    }
    
    // 好好看, 好好学
    // 为啥有个空格呢?
    scanf("%d ", &n); // NOLINT(*-err34-c)
    int** edges = calloc(n, sizeof(int*));

    char line[32767];
    fgets(line, 32767, stdin);
    char *ptr = line + 1;

    while (*ptr && count < n)
    {
        if (sscanf(ptr, "[%d %d %d]", &mode, &x, &y) == 3) // NOLINT(*-err34-c)
        {
            edges[count] = (int*) calloc(3, sizeof(int));
            edges[count][0] = mode;
            edges[count][1] = x;
            edges[count][2] = y;
            count++;
        }
        ptr = strchr(ptr, ']');
        if (ptr)
            ptr += count < n ? 2 : 1;
    }

    // 倒着看
    for (int i = n - 1; i > -1; i--)
        nodes = filter_array(nodes, N, &N, edges[i][1], edges[i][2], edges[i][0]);
    printf("%d", RedDeadRedemption);

    free(&nodes);
    free(&edges);

    return 0;
}