
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

//int partion(int array[], int left, int right)          //找基准值函数
//{
//	int begin = left;
//	int end = right;
//	while (begin < end)
//	{
//		while (begin < end&&array[begin] <= array[right])
//		{
//			begin++;
//		}
//		//begin卡住了,走end
//		while (begin < end&&array[end] >= array[right])
//		{
//			end--;
//		}
//		//end也卡住了，交换begin和end所在下标的值
//		swap(array + begin, array + end);
//	}
//	//走到这里肯定是begin和end 相遇了，然后交换begin和right下标所在的值
//	swap(array + begin, array + right);
//	//返回begin，就是基准值的下标；
//	return begin;
//}
//
//
//void quicksort(int array[], int left, int right)
//{
//	if (left >= right)      //判定一下需不需要排序
//	{
//		return;
//	}
//	int div = partion(array, left, right);
//	quicksort(array, left, div - 1);       //先递归左边区间
//	quicksort(array, div+1, right );       //再递归右边区间
//}
//
//int main()
//{
//	int arr[] = { 2, 6, 7, 5, 9, 4, 3, 1, 0, 10 };
//	int size = sizeof(arr) / sizeof(int);
//	printf("排序前:\n");
//	print(arr, size);
//	printf("\n排序后：\n");
//	quicksort(arr, 0, size - 1);
//	print(arr, size);
//	system("pause");
//	return 0;
//}
//



//快速排序------挖坑法

int partion2(int array[], int left, int right)
{
	int begin = left;
	int end = right;
	int provite = array[right];
	while (begin < end)
	{
		
		while (begin < end&&array[begin] <= provite)
		{
			begin++;
		}
		array[end] = array[begin];
		while (begin < end&&array[end] >= provite)
		{
			end--;
		}
		array[begin] = array[end];
	}
	array[begin] = provite;
	return begin;
}

void quicksort(int array[], int left, int right)
{
	if (left >= right)      //判定一下需不需要排序
	{
		return;
	}
	int div = partion2(array, left, right);
	quicksort(array, left, div - 1);       //先递归左边区间
	quicksort(array, div+1, right );       //再递归右边区间
}
int main()
{
	int arr[] = { 2, 6, 7, 5, 9, 4, 3, 1, 0, 10 };
	int size = sizeof(arr) / sizeof(int);
	printf("排序前:\n");
	print(arr, size);
	printf("\n排序后：\n");
	quicksort(arr, 0, size - 1);
	print(arr, size);
	system("pause");
	return 0;
}