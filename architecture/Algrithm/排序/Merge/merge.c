#include <stdio.h>
#include <stdlib.h>

void merge(int arry[], int left, int middle, int right) 
{
        int i, j, k;
        
        //合并array数组中下标为Left到Middle， 和下标为Middle+1到right的两部分
        int tmp[right-left+1];
        
        for (i = left; i <= right; i++) {
                tmp[i-left] = arry[i];
        }
        
        i = left;
        j = middle+1;
        for (k = left; k <= right; k++) {
                if (i > middle && j <= right) {
                        arry[k] = tmp[j-left];
                        j++;
                } else if (j > right & i <= middle) {
                        arry[k] = tmp[i-left];
                        i++;
                } else if (tmp[i-left] > tmp[j-left]) {
                        arry[k] = tmp[j-left];
                        j++;
                } else if (tmp[i-left] <= tmp[j-left]) {
                        arry[k] = tmp[i-left];
                        i++;
                }
        }
        for (i = left; i <= right; i++) {
                printf("arry[i] = %d\n", arry[i]);
        }
}

void merge_sort(int arry[], int left, int right)
{
        if (left >= right) {
                return;
        }
        int middle = (right+left) / 2;
        merge_sort(arry, left, middle);
        merge_sort(arry, middle+1, right);
        merge(arry, left, middle, right);
}


int main(void)
{
        int i;
        int left, right;
        
        int arry[] = {6, 7, 8, 9, 0, 1, 3, 2, 4, 5};
        left = 0;
        right = 9;
        merge_sort(arry, left, right);
        for (i = left; i <= right; i++) {
                printf("arrary = %d\n", arry[i]);
        }
}
