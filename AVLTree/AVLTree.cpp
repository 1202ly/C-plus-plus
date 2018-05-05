#pragma once
#include <iostream>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
	: _pRight(NULL)
	, _pLeft(NULL)
	, _pParent(NULL)
	, _key(key)
	, _value(value)
	, _bf(0)
	{}
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pLeft;
	AVLTreeNode<K, V>* _pParent;
	K _key;
	V _value;
	int _bf;//当前节点的平衡因子
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
	typedef Node* pNode;
public:
	AVLTree()
		:_pRoot(NULL)
	{}
	void PerInoder()
	{
		_PerInoder(_pRoot);
		cout << endl;
	}
	void _PerInoder(pNode pRoot)
	{
		if (pRoot)
		{
			cout << pRoot->_key << " ";
			_PerInoder(pRoot->_pLeft);
			_PerInoder(pRoot->_pRight);
		}
	}
	bool Insert(const K& key, const V& value)
	{
		//空树
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
			return true;
		}
		//不为空，1 找插入位置
		pNode pCur = _pRoot;//从根的位置开始找
		pNode pParent = NULL;//刚开始根节点无双亲节点
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (key>pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}
		//插入节点
		pCur = new Node(key, value);
		if (key < pParent->_key)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;
		//更新平衡因子
		while (pParent)
		{
			//插入分情况
			if (pParent->_pLeft == pCur)
				pParent->_bf--;
			else
				pParent->_bf++;
			//更新完成以后需要平衡（分情况）
			if (0 == pParent->_bf)
				break;
			else if (pParent->_bf == 1 || pParent->_bf == -1)
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else//2或者-2 //需要单旋或者双旋完成平衡
			{
				if (pParent->_bf == 2)
				{
					if (pCur->_bf == 1)//左旋
						RoteteL(pParent);
					else
						RoteteRL(pParent);//右左旋
				}
				else
				{
					if (pCur->_bf == -1)
						RoteteR(pParent);
					else
						RoteteLR(pParent);
				}
				break;//不再向上调整
			}
		}
		return true;
	}
	//bool Delete(pNode pParent)
	//{
	//	pNode pCur = pParent;
	//	pNode pSubR = pParent->_pRight;
	//	pNode pSubRL = pSubR->_pLeft;
	//	while (pParent)
	//	{
	//		if (pSubR)
	//			pParent->_bf--;
	//		else
	//			pParent->_bf++;
	//		if (pParent->_bf == 1 || pParent->_bf == -1)//删除之前平衡因子为0
	//			break;
	//		else if (pParent->_bf == 0)//删除之前平衡因子为-1或1
	//		{
	//			pCur = pParent;
	//			pParent = pCur->_pParent;
	//		}
	//		else
	//		{
	//			if (pParent->_bf == 2)
	//			{
	//				if (pCur->_bf == 1)//左旋
	//					RoteteL(pParent);
	//				else
	//					RoteteRL(pParent);//右左旋
	//			}
	//			else
	//			{
	//				if (pCur->_bf == -1)
	//					RoteteR(pParent);
	//				else
	//					RoteteLR(pParent);
	//			}
	//			break;//不再向上调整
	//		}
	//	}
	//	return true;
	//}
	void RoteteL(pNode pParent)
	{
		pNode pSubR = pParent->_pRight;
		pNode pSubRL = pSubR->_pLeft;
		//提升因子
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		pNode PParent = pParent->_pParent;
		pSubR->_pLeft = pParent;
		pSubR->_pParent = PParent;
		pParent->_pParent = pSubR;
		//pParent有三种情况（根/位于父亲的左，父亲的右）
		if (pParent == _pRoot)
			_pRoot = pSubR;
		if (PParent)
		{
			if (pParent == PParent->_pLeft)
				PParent->_pLeft = pSubR;
			else
				PParent->_pRight = pSubR;
		}
		//更新平衡因子
		pParent->_bf = 0;
		pSubR->_bf = 0;
	}
	void RoteteR(pNode pParent)
	{
		pNode pSubL = pParent->_pLeft;
		pNode pSubLR = pSubL->_pRight;
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;
		pNode PParent = pParent->_pParent;
		pSubL->_pRight = pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = PParent;
		if (pParent == _pRoot)
			_pRoot = pSubL;
		if (PParent)
		{
			if (pParent == PParent->_pLeft)
				PParent->_pLeft = pSubL;
			else
				PParent->_pRight = pSubL;
		}
		pParent->_bf = 0;
		pSubL->_bf = 0;
	}
	void RoteteLR(pNode pParent)
	{
		int bf = pParent->_pLeft->_pRight->_bf;
		RoteteL(pParent->_pLeft);
		RoteteR(pParent);
		//更新平衡因子
		if (bf == 1)
		{
			pParent->_bf = 0;
			pParent->_pLeft->_bf = -1;
			pParent->_pLeft->_pRight->_bf = 0;
		}
		else if (bf == -1)
		{
			pParent->_bf = 1;
			pParent->_pLeft->_bf = 0;
			pParent->_pLeft->_pRight->_bf = 0;
		}
	}
	void RoteteRL(pNode pParent)
	{
		pNode pSubR = pParent->_pRight;
		pNode pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;
		RoteteR(pSubR);
		RoteteL(pParent);
		//更新平衡因子
		if (bf == -1)
		{
			pSubR->_bf = 1;
		}
		else if (bf == 1)
		{
			pParent->_bf = -1;
		}
	}
	void MidOrder()
	{
		cout << "MidOrder: ";
		_MidOrder(_pRoot);
		cout << endl;
	}
	bool _Isblance()
	{
		return Isblance(_pRoot);
	}
	bool Isblance(pNode pRoot)
	{
		if (pRoot == NULL)
			return true;
		size_t LeftHeight = Height(pRoot->_pLeft);
		size_t RightHeight = Height(pRoot->_pRight);
		int height = RightHeight - LeftHeight;
		return ((abs(height)<2) && Isblance(pRoot->_pLeft) && Isblance(pRoot->_pRight));
	}
	size_t Height(pNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		else if (NULL == pRoot->_pLeft&&NULL == pRoot->_pRight)
			return 1;
		else
			return Height(pRoot->_pLeft) > Height(pRoot->_pRight) ?
			Height(pRoot->_pLeft) + 1 : Height(pRoot->_pRight) + 1;
	}
private:
	pNode _pRoot;
	void _MidOrder(pNode& pRoot)
	{
		if (pRoot)
		{
			_MidOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_MidOrder(pRoot->_pRight);
		}
	}
};

int main()
{
	int arr[] = {16,3,7,11,9,26,18,14,15};
	AVLTree<int, int> avl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		avl.Insert(arr[i], arr[i]);
	}
	if (avl._Isblance())
	{
		cout << "blance\n" << endl;
	}
	else
	{
		cout << "noblance\n" << endl;
	}
	avl.MidOrder();
	avl.PerInoder();
	getchar();
	return 0;
}