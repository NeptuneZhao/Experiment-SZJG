#include <stdio.h>
#include <stdlib.h>

#define HalfCooler_Creation 1

typedef struct number
{
    int origin, mapped;
} Number;

int get_mapped_value(const int num, const int *mapping)
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
        mapped_str[i++] = (char)(mapping[str[i] - '0'] + (int)'0');

    mapped_str[i] = '\0';
    return strtol(mapped_str, NULL, 10);
}

// From LeetCode Ti Jie
// Name: 【Python3 & Java & C++ & C】【排序】2191. 将杂乱无章的数字排序
// Author: Duck不必
// 写得太帅了!
int get_mapped_value2(int num, const int *mapping)
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
void merge_sort(Number *numbers, const int left, const int right) //NOLINT(*-no-recursion)
{
    if (left >= right || numbers == NULL)
        return;

    const int mid = (left + right) / 2;
    merge_sort(numbers, left, mid);
    merge_sort(numbers, mid + 1, right);

    Number *tmp = calloc(right - left + 1, sizeof(Number));
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
    
    for (int h = 0; h < k; h++)
        numbers[left + h] = tmp[h];
    
    free(tmp);
}

int input_int()
{
    int value;
    scanf("%d", &value); // NOLINT(cert-err34-c)
    return value;
}

int main(void)
{
    // I remember sometimes (int*) is not necessary
    int *mapping = calloc(10, sizeof(int)), n = input_int();
    Number *numbers = calloc(n, sizeof(Number));
    // From hints, we can get:
    // nums[i]: 1000000000 = 10^9
    // int_max: 2147483647 = 2^31 - 1
    // So we can use int to store the number
    for (int i = 0; i < 10; i++)
        mapping[i] = input_int();
    for (int i = 0; i < n; i++)
    {
        const int tmp = input_int();
        numbers[i].origin = tmp;
        numbers[i].mapped = get_mapped_value(tmp, mapping);
    }

    merge_sort(numbers, 0, n - 1);

    // 此处最后有空格
    // 别问我咋知道的
    for (int i = 0; i < n; i++)
        printf("%d ", numbers[i].origin);
    
    free(mapping);
    free(numbers);
    return 0;
}
