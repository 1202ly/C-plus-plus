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
	, _color(RED)//Ĭ�Ͻ��Ϊ��ɫ
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
		if (NULL == _pHead)//���һ��Ϊ��ʱ����һ���ڵ㣬ʹ֮��Ϊ���ڵ㣬��ɫΪ��ɫ
		{
			_pHead = new Node(key, value);
			_pHead->_color = BLACK;
			return true;
		}
		pNode pCur = _pHead;
		pNode pParent = NULL;
		while (pCur)//Ѱ�Ҳ���ڵ��λ��
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
		}//�ҵ�����ڵ��λ��
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
		//���һ������
		if (_pHead == NULL)
		{
			_pHead = pCur;
			pCur->_color = BLACK;
		}
		//�����������ڵ�ĸ��ڵ�Ϊ��ɫ����Υ���κ����ʣ�ֱ�Ӳ���
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
		//�������������ڵ�ĸ��ڵ�Ϊ�죬��Ҫ��һЩ��ɫ��ת����
		//pCurΪ��ǰ�ڵ㣬pParentΪ���ڵ㣬GrandfatherΪ�游�ڵ�
		//uncleΪ����ڵ�
		//�������pCurΪ�죬pParentΪ�죬GrandfatherΪ��ɫ��uncle������Ϊ��
		//�����������p��u��Ϊ��ɫ��g��Ϊ��ɫ����Ȼ���g����pcur���������ϵ���
		while (/*pCur!=_pHead */pParent&&pParent->_color == RED)
		{
			pNode Grandfather = pParent->_pParent;//�游���
			if (pParent == Grandfather->_pLeft)
			{
				pNode uncle = Grandfather->_pRight;//������
				if (uncle&&uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					Grandfather->_color = RED;
					Grandfather = pCur;
					pParent = pCur->_pParent;
				}
				//����壺curΪ�죬pΪ�죬gΪ�ڣ�u�����ڻ���uΪ��
				//pΪg�����ӣ�curΪp���Һ��ӣ�Ҫ��p������
				//pΪg���Һ��ӣ�curΪp�����ӣ����p�ҵ���
				else//curΪ�죬pΪ�죬gΪ�ڣ�u�����ڻ���uΪ��
				{
					if (pCur = pParent->_pRight)
					{
						RotateL(pParent);
						swap(pParent, pCur);
					}//��Ϊ�����
					RotateR(Grandfather);
					Grandfather->_color = RED;
					pParent->_color = BLACK;
					break;
				}
			}
			else if (pParent == Grandfather->_pRight)//pΪg���Һ���
			{
				pNode uncle = Grandfather->_pLeft;//������
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
					//�����
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
			cout << "���ڵ��Ǻ�ɫ��Υ������2" << endl;
			return false;
		}
		//�Ӹ��ڵ㿪ʼͳ�ƺ�ɫ�ڵ�ĸ���
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
			cout << "�������������ĺ�ɫ�ڵ㣬Υ��������3" << endl;
			return false;
		}
		if (pRoot->_pLeft == NULL&&pRoot->_pRight == NULL)
		{
			if (k != BlackCount)
			{
				cout << "��ǰ·���к�ɫ�ڵ�ĸ��������" << endl;
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
		cout << a[i] << "�ڵ��Ƿ���ɫ��������  " << rb.IsCheckRBTree() << endl;
	}
	rb.MidOrder();
	if (rb.IsCheckRBTree())
	{
		cout << "�ڵ���ɫȫ����������" << endl;
	}
	else
	{
		cout << "�ڵ���ɫ����ȫ��������" << endl;
	}
}