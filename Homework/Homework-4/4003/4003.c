#include <stdio.h>
#include <stdlib.h>

int total = 0, n = 0;

void Merge(int *arr, int *temp, const int l, const int mid, const int r)
{
    if (arr == NULL || temp == NULL)
        return;

    int i = l, p = l, j = mid;

    while (i < mid && j <= r)
    {
        if (arr[i] <= arr[j])
            temp[p++] = arr[i++];
        else
        {
            temp[p++] = arr[j++];
            total += mid - i;
        }
    }

    while (i < mid)
        temp[p++] = arr[i++];
    while (j <= r)
        temp[p++] = arr[j++];

    p = i = l;
    while (p <= r)
        arr[i++] = temp[p++];
}

void MergeSort(int *arr, int *temp, const int l, const int r) // NOLINT(*-no-recursion)
{
    if (l < r)
    {
        const int mid = (l + r) / 2;
        MergeSort(arr, temp, l, mid);
        MergeSort(arr, temp, mid + 1, r);
        Merge(arr, temp, l, mid + 1, r);
    }
}

int main(void)
{
    scanf("%d", &n); // NOLINT(*-err34-c)

    int
        *array = calloc(n, sizeof(int)),
        *temp = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", array + i); // NOLINT(*-err34-c)

    MergeSort(array, temp, 0, n - 1);
    // Time is just money.
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = i + 1; j < n; j++)
    //     {
    //         if (array[i] > array[j])
    //             total++;
    //     }
    // }

    printf("%d", total);
    free(array);
    free(temp);

}