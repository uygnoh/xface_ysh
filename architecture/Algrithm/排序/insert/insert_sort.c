#include <stdio.h>

void insert_sort(int arr[], int len) 
{
        int tmp, i, j;
        for (i=1; i<len; i++) {
                tmp = arr[i];
                j = i-1;
                while ((j >= 0) && (arr[j] > tmp)) {
                        arr[j+1] = arr[j];
                        j--;
                }
                arr[j+1] = tmp;
        }
}

int main(void)
{
        int i;
        int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        insert_sort(arr, 9);
        for (i = 0; i < 9; i++) {
                printf("%d\n", arr[i]);
        }
}
