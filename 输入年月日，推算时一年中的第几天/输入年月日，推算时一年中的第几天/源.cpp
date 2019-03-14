#define _CRT_SECURE_NO_WARNINGS 

#include<iostream>
#include<windows.h>
using namespace std;

int main()
{
	int arr[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	int year, month, day;
	while (1)
	{
		cin >> year >> month >> day;
		int total = 0;
		total = arr[month - 1] + day;
		if (2 < month&&((year%4==0&&year%100!=0)||year%400==0))
		{
			total += 1;
		}
		cout <<year<< "年的第" << total << "天" << endl;
	}
	system("pause");
	return 0;
}