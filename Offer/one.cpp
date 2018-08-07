#include<iostream>
using namespace std;

////1、赋值运算符函数
//class A
//{
//public:
//	A(char* a = NULL);
//	A(const A& str);
//	A& operator=(const A& str);
//	~A();
//private:
//	char* _a;
//};
//A::A(char* a)
//{
//	cout << "A(char* a)" << endl;
//}
//A::A(const A& str)
//{
//	cout << "A(const A& str)" << endl;
//}
//A::~A()
//{
//	cout << "~A()" << endl;
//}
//A& A::operator=(const A& str)
//{
//	cout << "A::operator=(const A& str)" << endl;
//	if (this != &str)
//	{
//		A ret(str);
//		char* tmp = ret._a;
//		ret._a = _a;
//		_a = tmp;
//	}
//	return *this;
//}
////测试
//int main()
//{
//	A a("abc");
//	A b;
//	A c;
//	//赋值给不同于自己的实例
//	b = a;
//	//赋值给自己
//	a = a;
//	//连续赋值
//	c = b = a;
//	system("pause");
//	return 0;
//}
//02设计一个类，只能生成该类的一个实例
//饿汉单例：在类装载时完成了初始化，静态成员对象初始化成功
//类加载速度相比懒汉慢，但获取对象的速度快，是一种典型的以时间换取空间的做法
//优点：线程安全
//缺点：不管你用不用这个对象，他都会先创建出来，会造成浪费内存空间
//class Singleon
//{
//private:
//	Singleon()
//	{
//		cout << "Singleon()" << endl;
//	}
//	static Singleon* instance;
//public:
//	static Singleon* GetSingleon()
//	{
//		return instance;
//	}
//	static Singleon* Destroy()
//	{
//		delete instance;
//		instance = NULL;
//	}
//};
//Singleon* Singleon::instance = new Singleon();
//int main()
//{
//	Singleon* sl1 = Singleon::GetSingleon();
//	Singleon* sl2 = Singleon::GetSingleon();
//	Singleon* sl3 = Singleon::GetSingleon();
//	cout << sl1 << endl;
//	cout << sl2 << endl;
//	cout << sl2 << endl;
//	system("pause");
//	return 0;
//}
//懒汉模式：在类装载时不会创建对象的实例，而是尽可能晚的创建实例，，加载速度很快，但运行时获取对象会稍微慢点，是一种典型的一时间会空间的做法
class Singleon
{
private:
	Singleon()
	{
		cout << "Singleon()" << endl;
	}
	static Singleon* instrance;
public:
	static Singleon* GetSingleon()
	{
		if (NULL == instrance)
		{
			instrance = new Singleon();
			cout << "对象创建成功" << endl;
		}
		else
		{
			cout << "对象已经创建成功，无须再建" << endl;
		}
		return instrance;
	}
	static Singleon* Destroy()
	{
		delete instrance;
		instrance = NULL;
	}
};
Singleon* Singleon::instrance =  NULL;
int main()
{
	Singleon* sl1 = Singleon::GetSingleon();
	Singleon* sl2 = Singleon::GetSingleon();
	Singleon* sl3 = Singleon::GetSingleon();
	cout << sl1 << endl;
	cout << sl2 << endl;
	cout << sl2 << endl;
	system("pause");
	return 0;
}
