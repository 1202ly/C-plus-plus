#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<string.h>
//读入一个字符串str，输出字符串str中的连续最长的数字串
//string strnum(string& str)
//{
//	int sz = str.size();
//	if (sz == 0)
//	{
//		return "";
//	}
//	string tmp;
//	string result;
//	for (int i = 0; i < sz; i++)
//	{
//		while (str[i] >= '0'&&str[i] <= '9')
//		{
//			tmp.push_back(str[i]);
//			i++;
//		}
//		int len1 = tmp.length();
//		int len2 = result.length();
//		if (len2 < len1)
//		{
//			result = tmp;
//		}
//		tmp = "";
//	}
//	return result;
//}
//
//int main()
//{
//	string str1 = "abcd12345ed125ss123456789"; 
//	string res;
//	res = strnum(str1);
//	for (int i = 0; i < res.size(); i++)
//	{
//		cout << res[i];
//	}
//	system("pause");
//	return 0;
//}

//2.给定一个有n个正整数的数组A和一个整数sum,求选择数组A中部分数字和为sum的方案数。
//输入5 15     5 5 10 2 3
//输出 4   5+5+2+3 10+2+3 5+10 5+10
//通过百分之80-*
#include<vector>
#include<iostream>
using namespace std;
int main() {
	int n, sum;
	cin >> n >> sum;
	vector<int> result(sum+1);
	vector<int> b(n);
	for (int i = 0; i<n; i++)
		cin >> b[i];
	result[0] = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = sum; j >= b[i]; j--)
			result[j] += result[j - b[i]];
	}
	cout << result[sum] << endl;
	system("pause");
	return 0;

}
