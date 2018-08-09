#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>  
using namespace std;
#include"Date.h"
#include<assert.h>
bool Date::Leap()
{
	if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Date::_GetMonthDay(int year, int month)
{
	assert(month > 0 && month <= 12);
	int arr_monthday[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day;
	if ((!Leap()) && month == 2)
	{
		_day = arr_monthday[month - 1] - 1;
	}
	day = arr_monthday[month - 1];
	return day;
}
Date& Date:: operator=(const Date& d)
{
	if (*this != d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}
bool Date::operator == (const Date& d)
{
	return ((_year == d._year) 
		&& (_month == d._month) && (_day == d._day));
}
bool Date::operator!=(const Date& d)
{
	return ((_year != d._year)
		&& (_month != d._month) && (_day != d._day));
}
bool Date::operator>(const Date& d)
{
	return (_year >d._year) //年  
		|| (_year == d._year) && (_month > d._month)// 年-月  
		|| (_year == d._year) && (_month == d._month) && (_day > d._day);
	//年-月-日  
}
bool Date::operator>=(const Date& d)
{
	return ((*this > d) || (*this == d));
}
bool Date::operator<(const Date& d)
{
	return (_year <d._year) //年  
		|| (_year == d._year) && (_month < d._month)// 年-月  
		|| (_year == d._year) && (_month == d._month) && (_day < d._day);
}
bool Date::operator<=(const Date& d)
{
	return ((*this < d) || (*this == d));
}
Date Date::operator+(int days)
{
	Date tmp(*this);
	if (days < 0)
	{
		return tmp - (-days);
	}
	tmp._day += days;
	while (tmp._day>_GetMonthDay(tmp._year, tmp._month))
	{
		tmp._day -= _GetMonthDay(tmp._year, tmp._month);
		if (tmp._month==12)
		{
			tmp._year++;
			tmp._month = 1;
		}
		else
		{
			tmp._month++;
		}
	}
	return tmp;
}
Date& Date:: operator +=(int days)//   +=  
{
	*this = *this + days;
	return *this;   //返回*this,所以用 引用做且返回值  
}

Date Date::operator-(int days)    /***************减天数******************/
{
	Date tmp(*this);
	if (days < 0)
	{
		return  tmp + (-days);
	}
	tmp._day -= days;
	while (tmp._day <= 0)  //注意没有1月0号。。。  
	{
		if (tmp._month == 1)
		{
			tmp._year--;
			tmp._month = 12;
		}//校正月数  
		else
		{
			--tmp._month;
		}
		tmp._day += _GetMonthDay(tmp._year, tmp._month);//上一个月的天数！！！  
	}
	return tmp;
}
Date& Date:: operator-=(int days)  //-=  
{
	*this = *this - days;
	return *this;
}
int Date::operator-(const Date& d)  //两个日期相隔天数  
{//思路：比较两个日期的大小，找出最大的（最小的）  
	//通过最大的--（最小的++），days++  
	//（最大的==最小的）就可以了  
	Date Max(*this);
	Date Min(d);
	int flag = 1;
	if (*this < d)
	{
		//使用库函数    std::swap(Max,Min);  
		Max = d;
		Min = *this;
		flag = -1;
	}
	int days = 0;
	while (Max != Min)
	{
		--Max;
		++days;
	}
	return days*flag;
}
ostream& operator<<(ostream& s, const Date& d)
{
	s << d._year << "-" << d._month << "-" << d._day << endl;
	return s;
}
istream& operator>>(istream& is, Date& d)
{
	cout << "输入日期：";
	is >> d._year;
	is >> d._month;
	is >> d._day;
	return is;
}
Date& Date::operator++()  //自加 天数  //前置++  
{
	//Date tmp(*this);  

	_day++;
	if (_day > _GetMonthDay(_year, _month))
	{
		_day -= _GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}

Date Date::operator++(int)  //后置++  
{
	Date temp(*this);
	_day++;
	if (_day > _GetMonthDay(_year, _month))
	{
		_day = _GetMonthDay(_year, _month) - _day;
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}
	return temp;
}

Date& Date::operator--()  //前置--  
{
	_day--;
	if (_day < 1)
	{
		_month--;
		if (_month < 1)
		{
			_year--;
			_month = 12;
		}
		_day += _GetMonthDay(_year, _month);
	}
	return *this;
}

Date Date::operator--(int)        //后置--  
{
	Date temp(*this);
	_day--;
	if (_day < 1)
	{
		_month--;
		if (_month < 1)
		{
			_year--;
			_month = 12;
		}
		_day += _GetMonthDay(_year, _month);
	}
	return temp;
}
