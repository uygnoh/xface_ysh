#include <stdio.h>

//查找最大值，返回最大值的位置（下标）
int find_max_pos(int arr[], int n)
{
        int i, max, pos;
        max = arr[0];
        pos = 0;
        for (i = 0; i < n; i++) {
                if (arr[i] > max) {
                        max = arr[i];
                        pos = i;
                }
        }
        return (pos);
}

void selection_sort(int arr[], int n)
{
        int pos, tmp;
        while (n > 1) {
                pos = find_max_pos(arr, n);
                tmp = arr[pos];
                arr[pos] = arr[n-1];
                arr[n-1] = tmp;
                n--;
        }
}

int main(void)
{
        int i;
        int arr[] = {5, 8, 9, 7, 6, 1, 2, 4, 3};
        selection_sort(arr, 9);
        for (i = 0; i < 9; i++) {
                printf("%d\n", arr[i]);
        }
}
