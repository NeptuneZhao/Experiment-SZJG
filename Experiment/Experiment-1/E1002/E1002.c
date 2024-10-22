#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HalfCooler_Creation 1

typedef struct number
{
    int origin, mapped;
} Number;

int get_mapped_value(const int num, int *mapping)
{
    if (mapping == NULL)
        return 0;
    
    // Store the string converted from the number
    // Store the mapped string
    char str[12], mapped_str[12];
    sprintf(str, "%d", num);

    int i = 0;
    
    // Convert string-number according to the mapping rule
    while (str[i] != '\0')
        mapped_str[i++] = mapping[str[i] - '0'] + '0';

    mapped_str[i] = '\0';
    return (int)strtol(mapped_str, NULL, 10);
}

// From LeetCode Ti Jie
// Name: 【Python3 & Java & C++ & C】【排序】2191. 将杂乱无章的数字排序
// Author: Duck不必
// 写得太帅了!
int get_mapped_value2(int num, int *mapping)
{
    if (mapping == NULL)
        return 0;
    
    int ret = 0, digit = 1;

    if (num <= 9)
        return mapping[num];

    while (num > 0)
    {
        ret += mapping[num % 10] * digit;
        digit *= 10;
        num /= 10;
    }
    return ret;
}

// 使用一个稳定的排序, 因为题目要求相同的数按照输入顺序输出
void merge_sort(Number *numbers, int left, int right)
{
    if (left >= right)
        return;
    
    int mid = (left + right) / 2;
    merge_sort(numbers, left, mid);
    merge_sort(numbers, mid + 1, right);

    Number *tmp = (Number*) calloc(right - left + 1, sizeof(Number));
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (numbers[i].mapped <= numbers[j].mapped)
            tmp[k++] = numbers[i++];
        else
            tmp[k++] = numbers[j++];
    }

    while (i <= mid)
        tmp[k++] = numbers[i++];
    
    while (j <= right)
        tmp[k++] = numbers[j++];
    
    for (int i = 0; i < k; i++)
        numbers[left + i] = tmp[i];
    
    free(tmp);
}

// 有 bug, 别用
int _input_int()
{
    char buffer[10];
    long value;
    
    while (1)
    {
        if (fgets(buffer, sizeof(buffer), __acrt_iob_func(0)) != NULL)
        {
            char *endptr;
            value = strtol(buffer, &endptr, 10);

            if (endptr != buffer && *endptr == '\n' && value >= INT_MIN && value <= INT_MAX)
                return (int)value;
        }
    }
}

int input_int()
{
    int value;
    scanf("%d", &value);
    return value;
}

int main(void)
{
    // I remember sometimes (int*) is not necessary
    int *mapping = (int*) calloc(10, sizeof(int)), n = input_int(), tmp;
    Number *numbers = (Number*) calloc(n, sizeof(Number));
    // From hints we can get:
    // nums[i]: 1000000000 = 10^9
    // int_max: 2147483647 = 2^31 - 1
    // So we can use int to store the number
    for (int i = 0; i < 10; i++)
        mapping[i] = input_int();
    for (int i = 0; i < n; i++)
    {
        tmp = input_int();
        numbers[i].origin = tmp;
        numbers[i].mapped = get_mapped_value(tmp, mapping);
    }

    merge_sort(numbers, 0, n - 1);

    // 此处注意机动处理末尾是否有空格
    for (int i = 0; i < n; i++)
        printf("%d ", numbers[i].origin);

    free(mapping);
    free(numbers);
    return 0;
}