#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

void teststring1()
{
	string s("123697542");
	cout << s << endl;          //string������������������������ֱ�������������s;
	cout << s.size() << endl;   //s������     9
	cout << s.length() << endl; //s������     9  
	cout << s.capacity() << endl; //������С    15

	s.clear();    //��� size  �Ľӿ�
	cout << "clear֮��" << endl;
	cout << s.size() << endl;   //    ���Ϊ0
	cout << s.length() << endl; //    ���Ϊ0
	cout << s.capacity() << endl; //   ����15������   ֻ���size,�����capacity

	s.resize(5);
	cout << "resize֮��" << endl;
	cout << s.size() << endl;   //    ���Ϊ5
	cout << s.length() << endl; //    ���Ϊ5
	cout << s.capacity() << endl;    //����
	//resize��n���ӿ�
	//n<size:       ԭ��size�Ĵ�С ���Ϊn     capacity����
	//size< n < capacity:     ԭ��size�Ĵ�С���Ϊn   capacity����   size~n֮������ݱ���Ϊ��\0��
	//n>capacity:             ԭ��size���Ϊn    capacity������   size~n֮������ݱ���Ϊ��\0��


	s.reserve(5);
	//reserve��n���ӿ�    ��n>capacityʱ���������ݣ����ı�size�Ĵ�С��   
	//����Ҫ���ݵĵط���ֱ�������ֽӿ����ݣ������Ч�ʣ�
	s.empty();  //�˽ӿ��ж�  �ַ���s�Ƿ�Ϊ�գ�����bool�͵� 
}

int main()
{
	teststring1();
	system("pause");
	return 0;
}