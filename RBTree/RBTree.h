#pragma once

#include<iostream>
using namespace std;
#include <stdlib.h>
enum COLOR{ RED, BLACK };
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode(const K& k, const V& v)
	:_pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _key(k)
	, _value(v)
	, _color(RED)//默认结点为红色
	{}
	RBTreeNode<K, V>* _pLeft;
	RBTreeNode<K, V>* _pRight;
	RBTreeNode<K, V>* _pParent;
	K _key;
	V _value;
	COLOR _color;
};
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
	typedef RBTreeNode<K, V>* pNode;
public:
	RBTree()
		:_pHead(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (NULL == _pHead)//情况一：为空时创建一个节点，使之成为根节点，颜色为黑色
		{
			_pHead = new Node(key, value);
			_pHead->_color = BLACK;
			return true;
		}
		pNode pCur = _pHead;
		pNode pParent = NULL;
		while (pCur)//寻找插入节点的位置
		{
			if (pCur->_key > key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (pCur->_key < key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}//找到插入节点的位置
		pCur = new Node(key, value);
		if (pParent->_key > key)
		{
			pParent->_pLeft = pCur;
			pCur->_pParent = pParent;
		}
		else
		{
			pParent->_pRight = pCur;
			pCur->_pParent = pParent;
		}
		//情况一：空树
		if (_pHead == NULL)
		{
			_pHead = pCur;
			pCur->_color = BLACK;
		}
		//情况二：插入节点的父节点为黑色，不违反任何性质，直接插入
		if (pParent->_color == BLACK)
		{
			if (key < pParent->_key)
			{
				pParent->_pLeft = pCur;
			}
			if (key>pParent->_key)
			{
				pParent->_pRight = pCur;
			}
		}
		//以下情况：插入节点的父节点为红，需要做一些变色旋转处理
		//pCur为当前节点，pParent为父节点，Grandfather为祖父节点
		//uncle为叔叔节点
		//情况三：pCur为红，pParent为红，Grandfather为黑色，uncle存在且为红
		//解决方法：将p，u改为黑色，g改为红色，，然后把g当成pcur，继续向上调整
		while (/*pCur!=_pHead */pParent&&pParent->_color == RED)
		{
			pNode Grandfather = pParent->_pParent;//祖父结点
			if (pParent == Grandfather->_pLeft)
			{
				pNode uncle = Grandfather->_pRight;//叔叔结点
				if (uncle&&uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					Grandfather->_color = RED;
					Grandfather = pCur;
					pParent = pCur->_pParent;
				}
				//情况五：cur为红，p为红，g为黑，u不存在或者u为黑
				//p为g的左孩子，cur为p的右孩子，要对p左单旋，
				//p为g的右孩子，cur为p的左孩子，则对p右单旋
				else//cur为红，p为红，g为黑，u不存在或者u为黑
				{
					if (pCur = pParent->_pRight)
					{
						RotateL(pParent);
						swap(pParent, pCur);
					}//变为情况四
					RotateR(Grandfather);
					Grandfather->_color = RED;
					pParent->_color = BLACK;
					break;
				}
			}
			else if (pParent == Grandfather->_pRight)//p为g的右孩子
			{
				pNode uncle = Grandfather->_pLeft;//叔叔结点
				if (uncle&&uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					Grandfather->_color = RED;
					Grandfather = pCur;
					pParent = pCur->_pParent;
				}
				else
				{
					if (pCur = pParent->_pLeft)
					{
						RotateR(pParent);
						swap(pParent, pCur);
					}
					//情况四
					RotateL(Grandfather);
					Grandfather->_color = RED;
					pParent->_color = BLACK;
					break;
				}
			}
		}
		_pHead->_color = BLACK;
		return true;
	}
	void RotateL(pNode pParent)
	{
		pNode pSubR = pParent->_pRight;
		pNode pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		pNode pPParent = pParent->_pParent;
		pSubR->_pLeft = pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;
		if (pParent == _pHead)
		{
			_pHead = pSubR;
		}
		else if (pPParent->_pLeft == pParent)
		{
			pPParent->_pLeft = pSubR;
		}
		else
			pPParent->_pRight = pSubR;
	}
	void RotateR(pNode pParent)
	{
		pNode pSubL = pParent->_pLeft;
		pNode pSubLR = pSubL->_pRight;
		pParent->_pLeft = pSubLR;
		if (pSubLR)
		{
			pSubLR->_pParent = pParent;
		}
		pNode pPParent = pParent->_pParent;
		pSubL->_pParent = pPParent;
		pSubL->_pRight = pParent;
		pParent->_pParent = pSubL;
		if (pParent == _pHead)
		{
			_pHead = pSubL;
		}
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
			pSubL->_pParent = pPParent;
		}
	}
	bool  IsCheckRBTree()
	{
		if (NULL == _pHead)
			return true;
		else if (_pHead->_color == RED)
		{
			cout << "根节点是红色，违反性质2" << endl;
			return false;
		}
		//从根节点开始统计黑色节点的个数
		int BlackCount = 0;
		pNode pCur = _pHead;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				BlackCount++;
			pCur = pCur->_pLeft;
		}
		int k = 0;
		return _IsCheckRBTree(_pHead, k, BlackCount);
	}
	bool _IsCheckRBTree(pNode pRoot, int k, int BlackCount)
	{
		if (NULL == pRoot)
		{
			return true;
		}
		if (pRoot->_color == BLACK)
		{
			k++;
		}
		pNode pParent = pRoot->_pParent;
		if (pParent&&pRoot->_color == RED&&pParent->_color == RED)
		{
			cout << "存在两个连续的红色节点，违反了性质3" << endl;
			return false;
		}
		if (pRoot->_pLeft == NULL&&pRoot->_pRight == NULL)
		{
			if (k != BlackCount)
			{
				cout << "当前路径中黑色节点的个数不相等" << endl;
				return false;
			}
		}
		return _IsCheckRBTree(pRoot->_pLeft, k, BlackCount)
			&& _IsCheckRBTree(pRoot->_pRight, k, BlackCount);
	}
	void MidOrder()
	{
		_MidOrder(_pHead);
	}
	void _MidOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_MidOrder(pRoot->_pLeft);
			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
			_MidOrder(pRoot->_pRight);
		}
	}
private:
	pNode _pHead;
};
void RBTest()
{
	RBTree<int, int> rb;
	int a[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		rb.Insert(a[i], i);
		cout << a[i] << "节点是否颜色符合性质  " << rb.IsCheckRBTree() << endl;
	}
	rb.MidOrder();
	if (rb.IsCheckRBTree())
	{
		cout << "节点颜色全部符合性质" << endl;
	}
	else
	{
		cout << "节点颜色不完全符合性质" << endl;
	}
}