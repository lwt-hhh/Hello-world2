#define _CRT_SECURE_NO_WARNINGS  1
#include<stdio.h>
#include<windows.h>

void swap(int*p1, int* p2)                  //交换函数
{
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void print(int array[], int size)            //打印函数
{
	for (int i = 0; i < size; i++)
	{
		printf("%d  ", array[i]);
	}

}

void adjustdown(int array[], int size, int root)      //向下调整函数
{
	int left = 2 * root + 1;
	int right = 2 * root + 2;
	if (left >= size)             //判断有没有左子树
	{
		return;
    }
	int mid = left;
	if (right<size&&array[right]>array[mid])    
	{
		mid = right;
	}
	if (array[mid] > array[root])
	{
		swap(array + mid, array + root);
		adjustdown(array, size, mid);
	}
}

void creatheap(int array[], int size)            //建堆
{
	for (int i = (size - 1 - 1) / 2; i >= 0; i--)
	{
		adjustdown(array, size, i);             // 从最后一个非叶子节点开始向下调整
	}
}

void heapsort(int array[], int size)          //堆排序
{
	creatheap(array, size);
	for (int i = 0; i < size; i++)
	{
		swap(array, array + size - 1 - i);
		adjustdown(array, size - 1 - i, 0);
	}
}


int main()
{
	int arr[] = {0,3,1,5,2,6,7,4};
	int size = sizeof(arr) / sizeof(int);
	print(arr, size);
	heapsort(arr, size);
	printf("\n排序后\n");
	print(arr, size);
	system("pause");
	return 0;
}