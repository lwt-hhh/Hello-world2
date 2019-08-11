#include<iostream>
#include<windows.h>
#include<string>
using namespace std;


void teststring1()
{
	string s;             //定义一个空字符串
	string s2("keda");    //定义并初始化
	s.push_back('h');     //在s中插入字符h  从s的末端插
	s += 'e';             //插入字符‘e’也可以像这样进行+=操作；
	s.append("hello");    //在s中插入字符串  用append接口；
	s += "hello";         //也可以用+=插入字符串；
	s += s2;              //也可以直接+= 另一个对象；
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
	size_t pos = file.find('.');   //find接口  找 ‘.’的位置； find是从前往后找，rfind是从后往前找；
	string s = file.substr(pos, file.size() - pos);  //s就是截取file之后的子串；  substr()是截取字串的接口；
	cout << s << endl;
	size_t pos1 = file.rfind('.');  //rfind接口
	string s1 = file.substr(pos1, file.size() - pos);
	cout << s1 << endl;
	system("pause");
	return 0;

}





