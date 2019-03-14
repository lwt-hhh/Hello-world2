#define _CRT_SECURE_NO_WARNINGS  1

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

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
		printf("%d  ", array[i]);
	}
}

void insersort(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int key = array[i];
		for (int j = i-1; j >= 0; j--)
		{
			if (array[j]>array[j + 1])
			{
				array[j + 1] = array[j];
				array[j] = key;
			}
		}
	}
}

int main()
{
	int arr[] = { 2, 3, 6, 8, 2, 5, 4, 6, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	print(arr, size);
	insersort(arr, size);
	printf("\n");
	print(arr, size);
	system("pause");
	return 0;
}