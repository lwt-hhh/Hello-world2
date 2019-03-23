#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

void teststring1()
{
	string s("123697542");
	cout << s << endl;          //string类重载了输出流运算符，可以直接这样输出对象s;
	cout << s.size() << endl;   //s自身长度     9
	cout << s.length() << endl; //s自身长度     9  
	cout << s.capacity() << endl; //容量大小    15

	s.clear();    //清空 size  的接口
	cout << "clear之后" << endl;
	cout << s.size() << endl;   //    会变为0
	cout << s.length() << endl; //    会变为0
	cout << s.capacity() << endl; //   还是15，不变   只清空size,不清空capacity

	s.resize(5);
	cout << "resize之后" << endl;
	cout << s.size() << endl;   //    会变为5
	cout << s.length() << endl; //    会变为5
	cout << s.capacity() << endl;    //不变
	//resize（n）接口
	//n<size:       原来size的大小 会变为n     capacity不变
	//size< n < capacity:     原来size的大小会变为n   capacity不变   size~n之间的内容被置为‘\0’
	//n>capacity:             原来size会变为n    capacity会增容   size~n之间的内容被置为‘\0’


	s.reserve(5);
	//reserve（n）接口    当n>capacity时，进行增容，不改变size的大小；   
	//有需要增容的地方，直接用这种接口增容，会提高效率；
	s.empty();  //此接口判断  字符串s是否为空；它是bool型的 
}

int main()
{
	teststring1();
	system("pause");
	return 0;
}