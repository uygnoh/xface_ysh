#include <stdio.h>

void shell_sort(int arr[], int n)
{
	int temp, gap, i, j;
	for (gap = n/2; gap > 0; gap /= 2)
	{
		for (i = gap; i < n; ++i)
		{
			temp = arr[i];
			for (j = i; j >= gap && arr[j-gap] > temp; j -= gap)
				arr[j] = arr[j-gap];
			arr[j] = temp;
		}
	}
}

int main(void)
{
	int arr[] = {9, 1, 2, 5, 0, 3, 7, 8, 4, 6};
	int i;	
	printf("===========================\n");
	for (i = 0; i < 10; i++)
		printf("%d,", arr[i]);
	printf("\n");
	printf("===========================\n");


	shell_sort(arr, 10);
	for (i = 0; i < 10; i++)
		printf("%d,",  arr[i]);
	printf("\n");

	return 0;
}
