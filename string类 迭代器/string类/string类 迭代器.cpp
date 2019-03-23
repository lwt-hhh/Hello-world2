#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

//正向迭代器 （begin  end）
#include<vector>
#include<list>

void printstring(const string& s)
{
	string::const_iterator sit = s.begin();   //const迭代器
	while (sit != s.end())
	{
		cout << *sit << " ";
	}
	cout << endl;
}


void testiterator()
{
	string s1("bitekeji");
	string::iterator sit = s1.begin();          //一般迭代器
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




//反向迭代器 （rbegin   rend）


void reverseiterator()
{
	string s1("bitekeji");
	string::reverse_iterator sit = s1.rbegin();          //注意有reverse_
	while (sit != s1.rend())
	{
		cout << *sit << " ";
		++sit;     //这里写的++ ，其实内部是--；
	}
	cout << endl;
}
int main()
{
	testiterator();      //正向迭代器  
	reverseiterator();   //反向迭代器     正向和反向输出字符串顺序相反；
	system("pause");
	return 0;
}

//迭代器：

//1.涉及模式：访问机制
//2.在外部：看作指针使用，内部实现上，不同容器有不同的实现方式，不一定是原生指针。

//迭代器分类：
//1.正向迭代器（可读可写）
//2.反向迭代器（可读可写）
//3.const迭代器（只读）
//begin: 第一个元素的位置
//end:最后一个元素的下一个位置位置
//rbegin：最后一个元素的位置
//rend: 第一个元素的前一个位置；



//operator[]:  

void teststring2()
{
	string s1("keda");
	for (int i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
		cout << s1.operator[](i) << endl;    //可以用于输出
	}
	cout << endl;
}
int main()
{
	teststring2();
	return 0;
}


//迭代器就是一种类似于指针的东西；

//迭代器提供了一种统一的方式去访问容器，屏蔽了底层复杂的结构细节；



