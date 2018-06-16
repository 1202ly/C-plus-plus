#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
typedef int DataType;
struct Node
{
	Node(const DataType& data)
	:_pNext(NULL)
	, _pPre(NULL)
	, _data(data)
	{}

		Node* _pNext;
		Node* _pPre;
		DataType _data;
};
class List
{
public:
	List()//构造函数//初始化
		:_pHead(NULL)
	{}
	List(DataType* array, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			PushBack(array[i]);
		}
	}
	void PushBack(const DataType data)
	{
		Node* pTail = _pHead;
		Node* newNode = new Node(data);
		if (_pHead == NULL)
		{
			_pHead = newNode;
			newNode->_pPre = pTail;
		}
		else
		{
			while (pTail->_pNext)
				pTail = pTail->_pNext;
			pTail->_pNext = newNode;
			newNode->_pPre = pTail;
		}
		newNode->_data = data;
		newNode->_pNext = NULL;
	}
	void PopBack()
	{
		Node* pTail = _pHead;
		if (pTail == NULL)
		{
			return;
		}
		else if (_pHead->_pNext = _pHead)
		{
			delete pTail;
		}
		else
		{
			while (pTail->_pNext)
			{
				pTail = pTail->_pNext;
			}
			pTail->_pPre->_pNext = NULL;
			delete pTail;
		}
	}
	~List()
	{
		Node* pTail = _pHead;
		while ((_pHead) && (_pHead->_pNext))
		{
			pTail = _pHead;
			_pHead = _pHead->_pNext;
			delete pTail;
		}
		delete _pHead;
	}

private:
	Node* _pHead;
};
void FunTest()
{
	int array[] = { 1, 2, 3, 4, 5, 6 ,7};
	List list(array, sizeof(array) / sizeof(array[0]));
	list.PushBack(8);
}
int main()
{
	FunTest();
	system("pause");
	return 0;
}