#define _CRT_SECURE_NO_WARNINGS  1
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
swap(int*p1, int*p2)
{
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}
void print(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);

	}
}

void bubblesort(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j]>array[j + 1])
			{
				swap(array + j, array + j + 1);
			}
		}
	}

}

int binarysearch(int array[], int size, int n)
{
		int left = 0;
		int right = size - 1;
		int mid = 0;
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (n == array[mid])
			{
				return mid;
			}
			else if (n > array[mid])
			{
				left = mid+1;
			}
			else
			{
				right = mid-1;
			}
		}
}

int main()
{
	int arr[] = { 2, 5, 3, 6, 0, 7, 8, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	print(arr, size);
	bubblesort(arr, size);
	printf("\n");
	print(arr, size);
	printf("\n");
	int m =binarysearch(arr, size,9);
	printf("9的下标为 %d\n", m);
	system("pause");
	return 0;
}

