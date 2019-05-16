#include<iostream>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;

class Date
{
public:
	Date()
	{
		cout << "Date()" << endl;
	}
	~Date()
	{
		cout << "~Date()" << endl;
	}
	int _year=0;
	int _month;
	int _day;
};


template<class T>
class sharedptr
{
public:
	sharedptr(T* ptr)
		:_ptr(ptr)
		, _count(new int(1))
		, _mux(new mutex)
	{}

	sharedptr(sharedptr<T>& sp)
		:_ptr(sp._ptr)
		, _count(sp._count)
		, _mux(sp._mux)
	{
		addref();
	}

	sharedptr<T>& operator=(sharedptr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			if (subref() == 0)
			{
				delete _ptr;
				delete _count;
				delete _mux;
			}
			_ptr = sp._ptr;
			_count = sp._count;
			_mux = sp._mux;
			addref();
		}
		return *this;
	}


	int subref()
	{
		_mux->lock();
		--*_count;
		_mux->unlock();
		return *_count;
	}

	int addref()
	{
		_mux->lock();
		++*_count;
		_mux->unlock();
		return *_count;
	}
	~sharedptr()
	{
		if (subref() == 0)
		{
			delete _ptr;
			delete _count;
			delete _mux;
			_ptr = nullptr;
			_count = nullptr;
			_mux = nullptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	
	int count()
	{
		return *_count;
	}



private:
	T* _ptr;      //指向管理资源的指针
	int* _count;      //引用计数
	mutex* _mux;      //互斥锁
};

mutex mux;

void fun(sharedptr<Date>& sp, int n)
{
	for (int i = 0; i < n; i++)
	{
		sharedptr<Date> copy(sp);
		mux.lock();
		copy->_year++;
		mux.unlock();
	}
}

int main()
{
	sharedptr<Date> sp(new Date);
	//sharedptr<Date> copy(sp);
	//sharedptr<Date> copy2(sp);

	int n = 5;
	thread t1(fun, sp, n);
	thread t2(fun, sp, n);
	t1.join();
	t2.join();
	cout << sp.count() << endl;
	cout << sp->_year << endl;
	system("pause");
	return 0;
}









//设计理念：  防拷贝  防赋值  
//办法：  c++98：  将拷贝构造和赋值运算符重载函数  私有化   并且只声明不实现；
//c++11: 直接将这两个函数delete;



//模拟实现unique_ptr:

//#include<iostream>
//#include<memory>
//using namespace std;
//
//template<class T>
//class uniqueptr
//{
//public:
//	uniqueptr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//	~uniqueptr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//			_ptr = nullptr;
//		}
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//private:
//	//C++98防拷贝方式：只声明、不实现
//	UniquePtr(UniquePtr<T> const &);
//	UniquePtr & operator=(UniquePtr<T> const &);
//
//
//	// C++11防拷贝的方式：delete   
//	UniquePtr(UniquePtr<T> const &) = delete;
//	UniquePtr & operator=(UniquePtr<T> const &) = delete;
//private:
//	T * _ptr;
//};
//
//
////特点：  简单粗暴  防拷贝  防赋值；
////   缺点：  不能拷贝、#include<iostream>
//#include<memory>
//using namespace std;
//


//int main()
//{
//	auto_ptr<Date> ap(new Date);
//	auto_ptr<Date> copy(ap);
//	ap->_year = 2018;       //非法的，因为经过拷贝构造后 原来的智能指针ap会被悬空（没有实际的地址空间了）
//	return 0;
//}

//auto_ptr模拟实现：

//template<class T>
//class autoptr
//{
//public:
//	autoptr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//	~autoptr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//		}
//	}
//	autoptr(autoptr<T>& ap)
//		:_ptr(ap._ptr)
//	{
//		ap._ptr = nullptr;
//	}
//	autoptr<T>& operator=(autoptr<T>& ap)
//	{
//		if (this != &ap)
//		{
//			if (_ptr)
//			{
//				delete _ptr;
//			}
//			_ptr = ap._ptr;
//			ap._ptr = nullptr;
//		}
//		return *this;
//	}
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//private:
//	T* _ptr;
//};
//
//int main()
//{
//	autoptr<Date> ap(new Date);
//	autoptr<Date> copy(ap);
//	ap->_year = 2018;    //会出现错误，因为ap已经悬空，通过ap访问资源会发生错误；
//	return 0;
//}
//
//
////auto_ptr特点:采用管理权转移，拷贝完会导致指针悬空，设计有缺陷；；
//
//
//
//
//
//
