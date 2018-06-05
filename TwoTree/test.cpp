#include<iostream>
#include<queue>
#include<stack>
#include<string.h>
using namespace std;
//孩子表示法
template<class T>
struct BinTreeNode
{

	BinTreeNode<T>* _lChild;//左孩子
	BinTreeNode<T>* _rChild;//右孩子
	T _data;//结点数据
	BinTreeNode(const T& data)
		:_lChild(NULL)
		, _rChild(NULL)
		, _data(data)
	{}
};
template<class T>
class BinTree
{

public:
	typedef BinTreeNode<T> Node;
	typedef BinTreeNode<T>* pNode;
	BinTree()//构造函数
		:_pRoot(NULL)
	{}
	BinTree(const T* array, size_t size, const T& invalid)
	{
		size_t index = 0;
		CreateBinTree(_pRoot, array, size, index, invalid);//创建树
	}
	BinTree(const BinTree<T>& bt)//拷贝构造函数
	{
		_pRoot = CopyBinTree(bt._pRoot);
	}
	BinTree<T>& operator=(const BinTree<T>& bt)//赋值运算符重载
	{
		if (this != &bt)
		{
			DestroyBinTree(_pRoot);
			_pRoot = CopyBinTree(bt._pRoot);
		}
		return *this;
	}
	~BinTree()//析构函数
	{
		DestroyBinTree(_pRoot);
	}
	void PreOrder()//递归前序遍历
	{
		cout << "PreOrder: ";
		_PreOrder(_pRoot);
		cout << endl;
	}
	void PreOrder_Nor1()//非递归前序遍历1
	{
		cout << "PreOrder_Nor1: ";
		_PreOrder_Nor1(_pRoot);
		cout << endl;
	}
	void PreOrder_Nor2()//非递归前序遍历2
	{
		cout << "PreOrder_Nor2: ";
		_PreOrder_Nor2(_pRoot);
		cout << endl;
	}
	void MidOrder()//递归中序遍历
	{
		cout << "MidOrder: ";
		_MidOrder(_pRoot);
		cout << endl;
	}
	void MidOrder_Nor()//非递归中序遍历
	{
		cout << "MidOrder_Nor: ";
		_MidOrder_Nor(_pRoot);
		cout << endl;
	}
	void PostOrder()//递归后序遍历
	{
		cout << "PostOrder: ";
		_PostOrder(_pRoot);
		cout << endl;
	}
	void PostOrder_Nor()//非递归后序遍历
	{
		cout << "PostOrder_Nor: ";
		_PostOrder_Nor(_pRoot);
		cout << endl;
	}
	void LevelOrder()//层序遍历
	{
		cout << "LevelOrder: " ;
		_LevelOrder(_pRoot);
		cout << endl;
	}
	size_t Size()//节点的个数
	{
		return _Size(_pRoot);
	}
	size_t LeefSize()//求叶节点的个数
	{
		return _LeefSize(_pRoot);
	}
	size_t Height()	//树的高度
	{
		return _Height(_pRoot);
	}
	pNode Find(const T&data)//查找树的某个节点
	{
		return _Find(_pRoot,data);
	}
	pNode Parent(pNode node)//找节点的双亲
	{
		return _Parent(_pRoot,node);
	}
	pNode lChild(pNode node)//找节点的左孩子
	{
		return (node == NULL) ? NULL : node->_lChild;
	}
	pNode rChild(pNode node)//找节点的右孩子
	{
		return (node == NULL) ? NULL : node->_rChild;
	}
	size_t GetKChild(size_t K)//树的第K层有多少节点
	{
		return _GetKChild(_pRoot, K);
	}
	void MirrorBinTree()//二叉树的镜像
	{
		cout << "MirrorBinTree: ";
		return _MirrorBinTree(_pRoot);
		cout << endl;
	}
	//判断二叉树是否为满树
	bool IsComBinTree()
	{
		return _IsComBinTree(_pRoot);
	}
private:
	void CreateBinTree(pNode& pRoot, const T* array,
		size_t size, size_t& index, const T& invalid)
	{
		if (index < size&&'#' != array[index])
		{
			//创建根节点
			pRoot = new Node(array[index]);
			//创建左子树
			CreateBinTree(pRoot->_lChild, array, size, ++index, invalid);
			//创建右子树
			CreateBinTree(pRoot->_rChild, array, size, ++index, invalid);
		}
	}
	pNode CopyBinTree(pNode pRoot)
	{
		pNode pNewRoot = NULL;
		if (pRoot)
		{
			//拷贝根节点
			pNewRoot = new Node(pRoot->_data);
			//拷贝根节点的左子树
			if (pRoot->_lChild)
				pNewRoot->_lChild = CopyBinTree(pRoot->_lChild);
			//拷贝根节点的右子树
			if (pRoot->_rChild)
				pNewRoot->_rChild = CopyBinTree(pRoot->_rChild);
		}
		return pNewRoot;
	}
	void DestroyBinTree(pNode pRoot)
	{
		if (pRoot)
		{
			DestroyBinTree(pRoot->_lChild);
			DestroyBinTree(pRoot->_rChild);
			delete pRoot;
			pRoot = NULL;
		}
	}
	//前序遍历(根+左子树+右子树)-->递归实现
	void _PreOrder(pNode& pRoot)
	{
		if (pRoot)
		{
			cout << pRoot->_data << " ";
			_PreOrder(pRoot->_lChild);
			_PreOrder(pRoot->_rChild);
		}
	}
	//前序遍历-->非递归实现1
	//将左右子树都压进栈中,先压右栈，再压左栈
	void _PreOrder_Nor1(pNode pRoot)
	{
		if (pRoot == NULL)
		{
			return;
		}
		stack<pNode> s;
		pNode cur = pRoot;
		s.push(cur);
		while (!s.empty())
		{
			cur = s.top();
			cout << cur->_data << " ";
			s.pop();
			if (cur->_rChild&&cur->_rChild->_data != '#')
			{
				s.push(cur->_rChild);
			}
			if (cur->_lChild&&cur->_lChild ->_data!= '#')
			{
				s.push(cur->_lChild);
			}
		}
	}
	//前序遍历-->非递归实现2
	//只将左子树压进栈中
	void _PreOrder_Nor2(pNode pRoot)
	{
		stack<pNode> s;
		s.push(pRoot);
		while (!s.empty())
		{
			pNode cur = s.top();
			s.pop();
			while (cur)
			{
				cout << cur->_data << " ";
				if (cur->_rChild)
					s.push(cur->_rChild);
				cur = cur->_lChild;
			}
		}
	}
	//中序遍历（左子树+根+右子树）--->递归实现
	void _MidOrder(pNode& pRoot)
	{
		if (pRoot)
		{
			_MidOrder(pRoot ->_lChild);
			cout << pRoot->_data << " ";
			_MidOrder(pRoot->_rChild);
		}
	}
	//中序遍历-->非递归实现
	void _MidOrder_Nor(pNode pRoot)
	{
		stack<pNode>s;
		pNode cur = pRoot;
		while (cur||!s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur=cur->_lChild;
			}
			cur = s.top();
			s.pop();
			cout << cur->_data <<" ";
			if (cur->_rChild)
			{
				cur = cur->_rChild;
			}
			else
			{
				cur = NULL;
			}
		}
	}
	//后序遍历（左子树+右子树+根）-->递归实现
	void _PostOrder(pNode& pRoot)
	{
		if (pRoot)
		{
			_PostOrder(pRoot->_lChild);
			_PostOrder(pRoot->_rChild);
			cout << pRoot->_data << " ";
		}
	}
	//后序遍历-->非递归实现
	void _PostOrder_Nor(pNode& pRoot)
	{
		stack<pNode> s;
		pNode cur = pRoot;
		pNode pPre = NULL;
		while (cur || !s.empty())
		{
			while (cur&&cur != pPre)
			{
				s.push(cur);
				cur = cur->_lChild;
			}
			if (s.empty())
				return;
			cur = s.top();
			if (cur->_rChild != NULL&&cur->_rChild != pPre)
			{
				cur = cur->_rChild;
			}
			else
			{
				cout << cur->_data << " ";
				s.pop();
				pPre = cur;
			}
		}
	}
	//层序遍历
	void _LevelOrder(pNode pRoot)
	{
		if (NULL == pRoot)//空树
			return;
		queue<pNode> qu;
		qu.push(pRoot);
		while (!qu.empty())
		{
			pNode pCur = qu.front();
			cout << pCur->_data << " ";
			if (pCur->_lChild)
				qu.push(pCur->_lChild);
			if (pCur->_rChild)
				qu.push(pCur->_rChild);
			qu.pop();
		}
		cout << endl;
	}
	//节点的个数
	size_t _Size(pNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		else
		{
			return _Size(pRoot->_lChild) + _Size(pRoot->_rChild) + 1;
		}
	}
	//叶节点的个数
	size_t _LeefSize(pNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		else if (NULL == pRoot->_lChild && NULL == pRoot->_rChild)
		{
			return 1;
		}
		else
			return _LeefSize(pRoot->_lChild) + _LeefSize(pRoot->_rChild);
	}
	size_t _Height(pNode pRoot)
	{
		if (NULL == pRoot)
			return 0;
		else if (NULL == pRoot->_lChild&&NULL == pRoot->_rChild)
			return 1;
		else
			return _Height(pRoot->_lChild) > _Height(pRoot->_rChild) ? 
			_Height(pRoot->_lChild) + 1: _Height(pRoot->_rChild) + 1;
	}
	pNode _Find(pNode pRoot, const T&data)//注意递归出口
	{
		pNode ret = NULL;
		if (NULL == pRoot)
			return NULL;
		else if (data == pRoot->_data)
			return pRoot;
		ret =  _Find(pRoot->_lChild, data);
		if (ret==NULL)
		    ret =  _Find(pRoot->_rChild, data);
		return ret;
	}
	pNode _Parent(pNode pRoot, pNode node)//注意递归出口
	{
		pNode ret = NULL;
		if (NULL == pRoot || NULL == node || node == pRoot)
			return NULL;
		//验证根节点是不是双亲
	    if (pRoot->_lChild == node || pRoot->_rChild == node)
			return pRoot;
		ret= _Parent(pRoot->_lChild, node);
		if (ret == NULL)
			ret= _Parent(pRoot->_rChild, node);
		return ret;
     }
	size_t _GetKChild(pNode pRoot, size_t K)
	{
		if (pRoot == NULL || K < 0)
			return 0;
		if (K == 1)
			return 1;
		return _GetKChild(pRoot->_lChild, K - 1) + _GetKChild(pRoot->_rChild, K - 1);
	}
	void _MirrorBinTree(pNode pRoot)
	{
		if (NULL == pRoot)
			return;
		if (pRoot)
		{
			swap(pRoot->_lChild, pRoot->_rChild);
			cout << pRoot->_data << " ";
		}
		_MirrorBinTree(pRoot->_lChild);
		_MirrorBinTree(pRoot->_rChild);
	}
	//方法一：把每棵树补成满二叉树，根据是否遍历到空洞，
	//整个树的遍历是否结束来判断是否是完全的二叉树。
	bool _IsComBinTree(pNode pRoot)
	{
		if (pRoot == NULL)
			return true;
		Node* pCur = NULL;
		queue<Node*> q;
		q.push(pRoot);
		while (pCur = q.front())
		{
			q.push(pCur->_lChild);
			q.push(pCur->_rChild);
			q.pop();
		}
		while (!q.empty())
		{
			pCur = q.front();
			if (pCur != NULL)
				return false;
			q.pop();
		}
		return true;
	}
	//方法二
	//bool _IsComBinTree(pNode pRoot)
	//{
	//	//空树或者只有根节点
	//	if ((NULL == pRoot)||(pRoot->_lChild==NULL&&pRoot->_rChild==NULL))
	//	{
	//		return true;
	//	}
	//	bool flag = false;//设置标记（标记是否找到临界点）
	//	pNode pCur = NULL;
	//	queue<pNode> q;
	//	q.push(pRoot);//将根节点压入队列中
	//	while (!q.empty())
	//	{
	//		pCur = q.front();
	//		if (flag)
	//		{
	//			//如果临界点存在孩子，那么一定不是完全二叉树
	//			if (pCur->_lChild || pCur->_rChild)
	//				return false;
	//		}
	//		//找第一个不饱和结点
	//		if (pCur->_lChild&&pCur->_rChild)
	//		{
	//			q.push(pCur->_lChild);
	//			q.push(pCur->_rChild);
	//		}
	//		else if (pCur->_lChild)
	//		{
	//			//pCur是不饱和点
	//			q.push(pCur->_lChild);
	//			flag = true;
	//		}
	//		else if (pCur->_rChild)
	//		{
	//			//没有左子树，肯定不是完全二叉树
	//			return false;
	//		}
	//		else
	//		{
	//			//pCur是不饱和点
	//			flag = true;
	//		}
	//		q.pop();
	//	}
	//	return true;
	//}
private:
	pNode _pRoot;//节点类型的指针
};
void Test()
{
	char* pStr = "ABD###C#G";
	BinTree<char> bt1(pStr, strlen(pStr), '#');
	BinTree<char> bt2(bt1);
	bt2.PreOrder();
	bt2.PreOrder_Nor1();
    bt2.PreOrder_Nor2();
	bt2.MidOrder();
	bt2.MidOrder_Nor();
	bt2.PostOrder();
	bt2.PostOrder_Nor();
	bt2.LevelOrder();
	cout<<"Size= "<<bt2.Size()<<endl;
	cout << "LeefSize= " << bt2.LeefSize() << endl;
	cout << "Height= " << bt2.Height() << endl;
	cout << "Find= "<<(bt2.Find('D'))->_data << endl;
	cout << "Parent= " << bt2.Parent(bt2.Find('G'))->_data << endl;
	cout << "lChild= " << bt2.lChild(bt2.Find('B'))->_data << endl;
	cout << "rChild= " << bt2.rChild(bt2.Find('C'))->_data << endl;
	cout << "GetKChild= " << bt2.GetKChild(3) << endl;
	bt2.MirrorBinTree();
	cout << endl;

	char* pStr1 = "ABD##H##CF##G";
	BinTree<char> bt3(pStr1, strlen(pStr1), '#');
	if (bt3.IsComBinTree())
	{
		cout << "是完全二叉树" << endl;
	}
	else
	{
		cout << "不是完全二叉树" << endl;
	}
}
int main()
{
	Test();
	system("pause");
	return 0;
}