#include<iostream>
#include<windows.h>
#include<string>
using namespace std;


void teststring1()
{
	string s;             //����һ�����ַ���
	string s2("keda");    //���岢��ʼ��
	s.push_back('h');     //��s�в����ַ�h  ��s��ĩ�˲�
	s += 'e';             //�����ַ���e��Ҳ��������������+=������
	s.append("hello");    //��s�в����ַ���  ��append�ӿڣ�
	s += "hello";         //Ҳ������+=�����ַ�����
	s += s2;              //Ҳ����ֱ��+= ��һ������
	cout << s << endl;
}

int main()
{
	teststring1();
	return 0;
}




int main()
{
	string file("test.cpp.com");
	size_t pos = file.find('.');   //find�ӿ�  �� ��.����λ�ã� find�Ǵ�ǰ�����ң�rfind�ǴӺ���ǰ�ң�
	string s = file.substr(pos, file.size() - pos);  //s���ǽ�ȡfile֮����Ӵ���  substr()�ǽ�ȡ�ִ��Ľӿڣ�
	cout << s << endl;
	size_t pos1 = file.rfind('.');  //rfind�ӿ�
	string s1 = file.substr(pos1, file.size() - pos);
	cout << s1 << endl;
	system("pause");
	return 0;

}





