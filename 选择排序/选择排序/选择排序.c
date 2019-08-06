#define _CRT_SECURE_NO_WARNINGS  1
#include<stdio.h>
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

void selectsort(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int max = 0;
		for (int j = 0; j < size - i; j++)
		{
			if (array[j]>array[max])
			{
				max = j;
			}
		}
		swap(array + max, array + size - 1 - i);
	}
}


int main()
{
	int arr[] = { 2, 5, 6, 4, 7, 8, 9, 3, 0 };
	int size = sizeof(arr) / sizeof(int);
	print(arr, size);
	selectsort(arr, size);
	printf("\n≈≈–Ú∫Û:\n");
	print(arr, size);
	system("pause");
	return 0;
}