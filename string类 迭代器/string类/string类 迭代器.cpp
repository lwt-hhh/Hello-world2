#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

//��������� ��begin  end��
#include<vector>
#include<list>

void printstring(const string& s)
{
	string::const_iterator sit = s.begin();   //const������
	while (sit != s.end())
	{
		cout << *sit << " ";
	}
	cout << endl;
}


void testiterator()
{
	string s1("bitekeji");
	string::iterator sit = s1.begin();          //һ�������
	while (sit != s1.end())
	{
		cout << *sit << " ";
		++sit;
	}
	cout << endl;

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	vector<int>::iterator vit = v.begin();
	while (vit != v.end())
	{
		cout << *vit << " ";
		++vit;
	}
	cout << endl;


	list<char> l;
	l.push_back('a');
	l.push_back('b');
	l.push_back('c');
	l.push_back('d');
	l.push_back('e');
	l.push_back('f');

	list<char>::iterator lit = l.begin();
	while (lit != l.end())
	{
		cout << *lit << " ";
		++lit;
	}
	cout << endl;
}




//��������� ��rbegin   rend��


void reverseiterator()
{
	string s1("bitekeji");
	string::reverse_iterator sit = s1.rbegin();          //ע����reverse_
	while (sit != s1.rend())
	{
		cout << *sit << " ";
		++sit;     //����д��++ ����ʵ�ڲ���--��
	}
	cout << endl;
}
int main()
{
	testiterator();      //���������  
	reverseiterator();   //���������     ����ͷ�������ַ���˳���෴��
	system("pause");
	return 0;
}

//��������

//1.�漰ģʽ�����ʻ���
//2.���ⲿ������ָ��ʹ�ã��ڲ�ʵ���ϣ���ͬ�����в�ͬ��ʵ�ַ�ʽ����һ����ԭ��ָ�롣

//���������ࣺ
//1.������������ɶ���д��
//2.������������ɶ���д��
//3.const��������ֻ����
//begin: ��һ��Ԫ�ص�λ��
//end:���һ��Ԫ�ص���һ��λ��λ��
//rbegin�����һ��Ԫ�ص�λ��
//rend: ��һ��Ԫ�ص�ǰһ��λ�ã�



//operator[]:  

void teststring2()
{
	string s1("keda");
	for (int i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
		cout << s1.operator[](i) << endl;    //�����������
	}
	cout << endl;
}
int main()
{
	teststring2();
	return 0;
}


//����������һ��������ָ��Ķ�����

//�������ṩ��һ��ͳһ�ķ�ʽȥ���������������˵ײ㸴�ӵĽṹϸ�ڣ�



