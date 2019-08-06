#define _CRT_SECURE_NO_WARNINGS  1
#include<stdio.h>
#include<windows.h>

void swap(int* p1, int* p2)
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

void shellsort(int array[], int size, int gap)
{
	for (int i = gap; i < size; i++)
	{
		int key = array[i];
		int j = 0;
		for (j = i - gap; j >= 0; j = j - gap)
		{
			if (array[j] <= key)
			{
				break;
			}
			else
			{
				array[j + gap] = array[j];
			}

		}
		array[j + gap] = key;
	}

}


int main()
{
	int arr[] = { 2, 6, 4, 3, 8, 7, 6, 9, 4, 0 };
	int size = sizeof(arr) / sizeof(int);
	int gap = size;
	print(arr, size);
	while (1)
	{
		gap = gap / 3 + 1;
		shellsort(arr, size, gap);
		if (1 == gap)
		{
			break;
		}
	}
	printf("\n");
	print(arr, size);
	system("pause");
	return 0;
}









