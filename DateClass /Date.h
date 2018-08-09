#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>  
using namespace std;
class Date
{
public:
	Date(int year = 2000, int month = 12, int day = 2)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		if ((year >= 2000) && (month >= 1 && month <= 12) 
			&& (day >= 1 && day <= _GetMonthDay(year, month)))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "日期非法" << endl;
			_year = 2000;
			_month = 12;
			_day = 2;
		}
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	~Date()
	{
		cout << "~Date()" << endl;
	}
	Date& operator=(const Date& d);
	bool operator == (const Date& d);
	bool operator!=(const Date& d);   //!=  
	bool operator>(const Date& d); // >  
	bool operator>=(const Date& d);  // >=  
	bool operator<(const Date& d);  // <  
	bool operator<=(const Date& d);   //<=  
	Date operator+(int days);  // 加天数  
	Date& operator+=(int days);//   +=  
	Date operator-(int days);  //减天数  
	int operator-(const Date& d);  // 两个日期相隔天数  
	Date& operator-=(int days);  //-=  
	Date& operator++();  //自加 天数  //前置++  
	Date operator++(int); //后置++  
	Date& operator--(); //前置--  
	Date operator--(int);  //后置  
	bool Leap();//判断闰年?  
	int _GetMonthDay(int year, int month);  //一个月有多少天  
	friend ostream& operator<<(ostream& s, const Date& d);    //输出  
	friend istream& operator>>(istream& is, Date& d);
private:
	int _year;
	int _month;
	int _day;
};
