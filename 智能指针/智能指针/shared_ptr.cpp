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
	T* _ptr;      //ָ�������Դ��ָ��
	int* _count;      //���ü���
	mutex* _mux;      //������
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









//������  ������  ����ֵ  
//�취��  c++98��  ����������͸�ֵ��������غ���  ˽�л�   ����ֻ������ʵ�֣�
//c++11: ֱ�ӽ�����������delete;



//ģ��ʵ��unique_ptr:

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
//	//C++98��������ʽ��ֻ��������ʵ��
//	UniquePtr(UniquePtr<T> const &);
//	UniquePtr & operator=(UniquePtr<T> const &);
//
//
//	// C++11�������ķ�ʽ��delete   
//	UniquePtr(UniquePtr<T> const &) = delete;
//	UniquePtr & operator=(UniquePtr<T> const &) = delete;
//private:
//	T * _ptr;
//};
//
//
////�ص㣺  �򵥴ֱ�  ������  ����ֵ��
////   ȱ�㣺  ���ܿ�����#include<iostream>
//#include<memory>
//using namespace std;
//


//int main()
//{
//	auto_ptr<Date> ap(new Date);
//	auto_ptr<Date> copy(ap);
//	ap->_year = 2018;       //�Ƿ��ģ���Ϊ������������� ԭ��������ָ��ap�ᱻ���գ�û��ʵ�ʵĵ�ַ�ռ��ˣ�
//	return 0;
//}

//auto_ptrģ��ʵ�֣�

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
//	ap->_year = 2018;    //����ִ�����Ϊap�Ѿ����գ�ͨ��ap������Դ�ᷢ������
//	return 0;
//}
//
//
////auto_ptr�ص�:���ù���Ȩת�ƣ�������ᵼ��ָ�����գ������ȱ�ݣ���
//
//
//
//
//
//
