#define _CRT_SECURE_NO_WARNINGS  1
#include<stdio.h>
#include<windows.h>

void swap(int*p1, int* p2)                  //��������
{
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void print(int array[], int size)            //��ӡ����
{
	for (int i = 0; i < size; i++)
	{
		printf("%d  ", array[i]);
	}

}

void adjustdown(int array[], int size, int root)      //���µ�������
{
	int left = 2 * root + 1;
	int right = 2 * root + 2;
	if (left >= size)             //�ж���û��������
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

void creatheap(int array[], int size)            //����
{
	for (int i = (size - 1 - 1) / 2; i >= 0; i--)
	{
		adjustdown(array, size, i);             // �����һ����Ҷ�ӽڵ㿪ʼ���µ���
	}
}

void heapsort(int array[], int size)          //������
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
	printf("\n�����\n");
	print(arr, size);
	system("pause");
	return 0;
}