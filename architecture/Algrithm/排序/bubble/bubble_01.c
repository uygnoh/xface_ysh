#include <stdio.h>

void bubble(int *ptr, int len) 
{
        int i, tmp;
        for (i = 0; i < len-1; i++) {
                if (ptr[i] > ptr[i+1]) {
                        tmp      = ptr[i];
                        ptr[i]   = ptr[i+1];
                        ptr[i+1] = tmp;
                }
        }
}

void bubble_sort(int *ptr, int len)
{
        int i;
        for (i = len; i >= 1; i--) {
                bubble(ptr, i);
        }
}

int main(void) 
{
        int i;
        int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        for (i = 0; i < 10; i++) {
                printf("%d ", a[i]);
        }
        printf("\n");
        
        bubble_sort(a, 10);
        
        for (i = 0; i < 10; i++) {
                printf("%d ", a[i]);
        }
        printf("\n");
        return 0;
}
