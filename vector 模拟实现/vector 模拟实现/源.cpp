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
	iterator begin()                      //������
	{
		return _start;
	}
	iterator end()
	{
		return _finsh;
	}

	const_iterator cbegin()                      //������
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

	Vector()                            //�޲ι���
		:_start(nullptr)
		, _finsh(nullptr)
		, _capacity_ptr(nullptr)
	{}

	Vector(int n, T m)                    //��ʼ����n��m�Ĺ��캯��
	{
		Reserve(n);
		while (n--)
		{
			pushback(m);
		}

	}

	Vector(const Vector<T>& v)            //��������
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

	void pushback(const T& m)              //β��
	{
		insert(end(), m);
	}

	void insert(iterator pos, const T& x)            //����
	{
		assert(pos <= _finsh);
		if (_finsh==_capacity_ptr)
		{
			int size = pos-_start;
			int n = Capacity() == 0 ? 1 : 2 * Capacity();
			Reserve(n);
			pos = _start + size;                      //����֮���������ʧЧ��Ҫ���µ�����
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

	void erase(iterator pos)              //ɾ��
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

	//void pushback(const T& val)       //β��
	//{
	//	if (_finsh== _capacity_ptr)     //�ж��Ƿ���Ҫ����
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

	void Reserve(size_t n)   //����
	{
		if (n > Capacity())
		{
			size_t size = Size();
			T* tmp = new T[n];        //�����µĿռ�
			if (_start)     //�ж�ԭ�пռ��Ƿ�Ϊ��
			{
				for (int i = 0; i < size; i++)  //��ԭ�������ݿ����µĿռ䣬����Ҫ�����
				{
					tmp[i] = _start[i];
				}
				delete[] _start;            //�ͷ�ԭ�пռ�
			}
			_start = tmp;                   //����ָ��
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
	iterator _start;            //��һ��Ԫ�ص���ʼλ��
	iterator _finsh;            //���һ��Ԫ�صĽ���λ��
	iterator _capacity_ptr;     //�Ѿ�����ÿռ�Ľ���λ��
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
	Vector<int> v(5, 100);      //��ʼ��һ������5��100�� v��
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