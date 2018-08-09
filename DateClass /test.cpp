#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>  
using namespace std;
#include"Date.h"
#include<assert.h>
int main()
{
	Date d1(2017, 6, 30);
	Date  d2(2017, 7, 1);
	cout << d1;
	int ret = d2 - d1;
	Date  d3 = d2 + 1;
	Date d4(d2);
	Date d5 = d1 - 1;
	Date d6 = d1++;
	Date d8;
	d8 = d1 + 360;
	Date d7;
	cin >> d7;
	cout << d7;
	d1 += 1;
	Date d9(2016,12,1);
	if (d9 == d1)
	{
		printf("相等");
	}
	else
	{
		printf("不相等");
	}
	return 0;
}
