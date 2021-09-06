#include <stdio.h>

void bubble_sort(int* ptr, int len) {
	int i, j, tmp;
	for (i = 0; i < len-1; i++) {
		for (j = 0; j < len-i-1; j++) {
			if (ptr[j] > ptr[j+1]) {
				tmp = ptr[j];
				ptr[j] = ptr[j+1];
				ptr[j+1] = tmp;
			}
		}
	}
}

int main(void) {
	int i;
	int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	bubble_sort(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
