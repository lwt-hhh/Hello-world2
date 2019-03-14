
#include<iostream>
#include<windows.h>
using namespace std;
class Date
{
public:
	Date(int year=1990, int month=1,int day=1)
	{
		if (year <= 0 || month <= 0 || month > 12 || day <= 0 || day > yearmonthday(year, month))
		{
			cout << "输入日期有误" << endl;
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			_year = year;
			_month = month;
			_day = day;
		}
		
	}
	Date(const Date& d)
	{
		this->_year = d._year;
		this->_month = d._month;
		this->_day = d._day;
	}

	int yearmonthday(int year, int month)
	{
		static int arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			if (2 == month)
			{
				arr[month-1] += 1;
			}
		}
		int day = arr[month - 1];
		return day;
	}
	
	Date& operator+=(int day)
	{
		if (day<0)
		{
			return *this -= -day;
		}
		_day += day;
		//考虑是否需要进位
		while(_day > yearmonthday(_year, _month))
		{
			_day -= yearmonthday(_year, _month);
			_month++;
			//判断月份是否合理
			if (_month == 13)
			{
				_month = 1;
				++_year;
			}
		}
		return *this;
	}
	Date& operator-=(int day)
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_month = 12;
				--_year;
			}
			_day += yearmonthday(_year, _month);
		}
		return *this;
	}
	Date operator+(int days)
	{
		Date ret(*this);
		ret += days;
		return ret;
	}
	Date operator-(int days)
	{
		Date ret(*this);
		ret -= days;
		return ret;
	}
	/*前置++*/
	Date& operator++()
	{
		return *this += 1;   //先自加，再返回
	}
	//后置++
	Date operator++(int)
	{
		Date ret(*this);     //先返回自加之前的值，再返回
		*this+= 1;
		return ret;
	}
	Date operator--(int)      //后置--
	{
		Date ret(*this);
		*this-= 1;
		return ret;
	}
	Date& operator--()      //前置--
	{
		*this -= 1;
		return *this;
	}
	bool operator==(const Date& d) const
	{
		return this->_year == d._year&&this->_month == d._month&&this->_day == d._day;
	}
	bool operator>(const Date& d) const
	{
		if (this->_year > d._year)
		{
			return true;
		}
		else if ((this->_year == d._year) && (this->_month > d._month))
		{
			return true;
		}
		else if ((this->_year == d._year) && (this->_month >= d._month) && this->_day > d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>=(const Date& d) const
	{
		return !(*this < d );
	}
	bool operator<(const Date& d) const
	{
		return ((*this >d)||(*this==d));
	}
	bool operator<=(const Date& d) const
	{
		return !(*this>d);
	}
	bool operator!=(const Date& d) const
	{
		return !(*this==d);
	}
	int operator-(const Date& d)
	{
		Date ret(*this);
		int flag = 1;
		if (ret < d)
		{
			flag = -1;
		}
		int day = 0;
		if (ret < d)
		{
			while (ret < d)
			{
				++ret;
				++day;
			}
		}
		else
		{
			while (ret>d)
			{
				--ret;
				--day;
			}
		}
		return day*flag;
	}
	void display()
	{
		cout << _year<<"." << _month <<"."<< _day;
	}

private:
		int _year;
		int _month;
		int _day;
};


int main()
{
	Date d1(2019, 3,1);
	Date d2(2020, 1,1);
	cout<< "d1:" << endl;
	d1.display();
	cout <<endl<<"d2:"<< endl;
	d2.display();
	cout << endl;
	cout << "d1==d2     " << (d1 == d2) << endl;
	cout << "d1!=d2     " << (d1 != d2) << endl;
	cout << "d1>=d2     " << (d1 >= d2) << endl;
	cout << "d1<=d2     " << (d1 <= d2) << endl;
	cout << "d1>d2     " << (d1 > d2) << endl;
	cout << "d1<d2     " << (d1 < d2) << endl;
	++d1;
	++d2;
	cout << "++d1:" << endl;
	d1.display();
	cout <<endl<< "++d2:" << endl;
	d2.display();
	Date d3=d2 + 365;
	cout << endl << "d2+365" << endl;
	d3.display();
	Date d4 = d2 - 365;
	cout <<endl <<"d2-365" << endl;
	d4.display();

	system("pause");
	return 0;
}




























