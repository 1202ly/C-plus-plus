#include<iostream>
using namespace std;
#include<vector>
template<class T>
class UFSets
{
public:
	UFSets(size_t size)
		:_array(size,-1)
	{
		//_array.resize(size, -1);//利用vector函数
		//_array._assign(size, -1);
	}
	void Union(int data1, int data2)
	{
		int root1 = FindRoot(data1);
		int root2 = FindRoot(data2);
		if (root1 != root2)
		{
			_array[root1] += _array[root2];
			_array[root2] = root1;
		}
	}
	int FindRoot(int data)
	{
		while (_array[data] >= 0)
		{
			data = _array[data];
		}
		return data;
	}
	size_t Size()
	{
		size_t n = 0;
		for (size_t i = 0; i < _array.size(); i++)
		{
			if (_array[i] < 0)
			{
				n++;
			}
		}
		return n;
	}
private:
	vector<int> _array;
};
int main()
{
	UFSets<int> un(6);
	un.Union(1,2);
	un.Union(2,3);
	un.Union(4,5);
	printf("一共有%d个集合\n", un.Size()-1);
	//因为0号位置虽然初始化了，但是没有数字集合在该集合中，所以减去1
	system("pause");
	return 0;
}