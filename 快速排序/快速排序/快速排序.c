
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

//int partion(int array[], int left, int right)          //�һ�׼ֵ����
//{
//	int begin = left;
//	int end = right;
//	while (begin < end)
//	{
//		while (begin < end&&array[begin] <= array[right])
//		{
//			begin++;
//		}
//		//begin��ס��,��end
//		while (begin < end&&array[end] >= array[right])
//		{
//			end--;
//		}
//		//endҲ��ס�ˣ�����begin��end�����±��ֵ
//		swap(array + begin, array + end);
//	}
//	//�ߵ�����϶���begin��end �����ˣ�Ȼ�󽻻�begin��right�±����ڵ�ֵ
//	swap(array + begin, array + right);
//	//����begin�����ǻ�׼ֵ���±ꣻ
//	return begin;
//}
//
//
//void quicksort(int array[], int left, int right)
//{
//	if (left >= right)      //�ж�һ���費��Ҫ����
//	{
//		return;
//	}
//	int div = partion(array, left, right);
//	quicksort(array, left, div - 1);       //�ȵݹ��������
//	quicksort(array, div+1, right );       //�ٵݹ��ұ�����
//}
//
//int main()
//{
//	int arr[] = { 2, 6, 7, 5, 9, 4, 3, 1, 0, 10 };
//	int size = sizeof(arr) / sizeof(int);
//	printf("����ǰ:\n");
//	print(arr, size);
//	printf("\n�����\n");
//	quicksort(arr, 0, size - 1);
//	print(arr, size);
//	system("pause");
//	return 0;
//}
//



//��������------�ڿӷ�

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
	if (left >= right)      //�ж�һ���費��Ҫ����
	{
		return;
	}
	int div = partion2(array, left, right);
	quicksort(array, left, div - 1);       //�ȵݹ��������
	quicksort(array, div+1, right );       //�ٵݹ��ұ�����
}
int main()
{
	int arr[] = { 2, 6, 7, 5, 9, 4, 3, 1, 0, 10 };
	int size = sizeof(arr) / sizeof(int);
	printf("����ǰ:\n");
	print(arr, size);
	printf("\n�����\n");
	quicksort(arr, 0, size - 1);
	print(arr, size);
	system("pause");
	return 0;
}