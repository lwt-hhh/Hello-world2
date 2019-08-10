#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

template<class T>
class Vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin()                      //迭代器
	{
		return _start;
	}
	iterator end()
	{
		return _finsh;
	}

	const_iterator cbegin()                      //迭代器
	{
		return _start;
	}
	const_iterator cend()
	{
		return _finsh;
	}

	size_t Size()
	{
		return _finsh - _start;
	}
	size_t Capacity()
	{
		return _capacity_ptr-_start;
	}

	Vector()                            //无参构造
		:_start(nullptr)
		, _finsh(nullptr)
		, _capacity_ptr(nullptr)
	{}

	Vector(int n, T m)                    //初始化有n个m的构造函数
	{
		Reserve(n);
		while (n--)
		{
			pushback(m);
		}

	}

	Vector(const Vector<T>& v)            //拷贝构造
		:_start(nullptr)
		,_finsh(nullptr)
		, _capacty_ptr(nullptr)
	{
		Reserve(v.capacity());
		iterator it = begin();
		const_iterator vit = v.cbegin();
		while (vit != v.cend())
		{
			*it++ = *vit++;
		}
		_start = it;
		_finsh = it + v.Size();
		_capacity_ptr = it + v.Capacity();

	}

	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = nullptr;
			_finsh = nullptr;
			_capacity_ptr = nullptr;
		}
	}

	T& operator[] (size_t pos)
	{
		assert(pos < Size())
		return _start[pos];
	}

	Vector<T>& operator=(Vector<T> v)
	{
		Swap(v);
		return *this;
	}

	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finsh, v._finsh);
		swap(_capacity_ptr, v._capacity_ptr);
	}

	void pushback(const T& m)              //尾插
	{
		insert(end(), m);
	}

	void insert(iterator pos, const T& x)            //插入
	{
		assert(pos <= _finsh);
		if (_finsh==_capacity_ptr)
		{
			int size = pos-_start;
			int n = Capacity() == 0 ? 1 : 2 * Capacity();
			Reserve(n);
			pos = _start + size;                      //增容之后迭代器会失效，要更新迭代器
		}
		iterator end = _finsh - 1;
		while (pos <=end)
		{
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finsh;
	}

	void erase(iterator pos)              //删除
	{
		assert(pos < _finsh);
		iterator begin = pos +1;
		while (begin != _finsh)
		{
			*(begin - 1) = *begin;
			begin++;
		}
		--_finsh;
	}

	//void pushback(const T& val)       //尾插
	//{
	//	if (_finsh== _capacity_ptr)     //判断是否需要扩容
	//	{
	//		size_t newc = (_start == nullptr ? 1 : 2 * Capacity());
	//		Reserve(newc);
	//	}
	//	*_finsh = val;
	//	++_finsh;
	//}

	void popback()
	{
		--_finsh;
	}

	void Reserve(size_t n)   //扩容
	{
		if (n > Capacity())
		{
			size_t size = Size();
			T* tmp = new T[n];        //申请新的空间
			if (_start)     //判断原有空间是否为空
			{
				for (int i = 0; i < size; i++)  //把原来的内容拷到新的空间，这里要用深拷贝
				{
					tmp[i] = _start[i];
				}
				delete[] _start;            //释放原有空间
			}
			_start = tmp;                   //更新指针
			_finsh = tmp + size;
			_capacity_ptr = _start + n;
		}
	}

	void Resize(T n, const T& value)
	{
		if (n < Size())
		{
			_finsh = _start + n;
			return;
		}
		else if (n>Capacity())
		{
			Reserve(n);
		}
		iterator it = _finsh;
		_finsh = _start + n;
		while (it != _finsh)
		{
			*it++ = value;
		}

	}

private:
	iterator _start;            //第一个元素的起始位置
	iterator _finsh;            //最后一个元素的结束位置
	iterator _capacity_ptr;     //已经分配好空间的结束位置
};

template <class T>
void print( Vector<T>& v)
{
	for (auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector1()
{
	Vector<int> v(5, 100);      //初始化一个存有5个100的 v；
	v.popback();
	print(v);
}

void test_vector2()
{
	Vector<int> v1;
	v1.pushback(8);
	v1.pushback(7);
	v1.pushback(6);
	v1.pushback(5);
	v1.pushback(4);
	v1.pushback(3);
	v1.erase(v1.begin());
	v1.Resize(20, 9);
	print(v1);
}

void test_vector3()
{
	Vector<char> v;
	v.pushback('2');
	print(v);
}

void test_vector4()
{
	Vector<string> v1;
	v1.pushback("123");
	v1.pushback("456");
	v1.pushback("789");
	print(v1);
}

int main()
{
	//test_vector1();
	test_vector2();
	//test_vector3();
	//test_vector4();
	system("pause");
	return 0;
}