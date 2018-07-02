#include<iostream>
using namespace std;
#include<assert.h>
#include<math.h>

////寻找两个链表的第一个公共结点
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
class Solution {
public:
	typedef int DataType;
	void Push(ListNode** pplist, DataType data)
	{
		assert(pplist);
		ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
		if (newNode == NULL)
		{
			perror("newNode");
			exit(EXIT_FAILURE);
		}
		newNode->val = data;
		newNode->next = NULL;
		newNode->next = *pplist;
		*pplist = newNode;
	}
//	方法一
	//ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
	//	if (pHead1 == NULL || pHead2 == NULL)
	//	{
	//		return NULL;
	//	}
	//	if (pHead1->val == pHead2->val)
	//	{
	//		return pHead1;
	//	}
	//	int len1 = 0;
	//	int len2 = 0;
	//	ListNode* cur = pHead1;
	//	ListNode* ptr = pHead2;
	//	while (cur)
	//	{
	//		len1++;
	//		cur = cur->next;
	//	}
	//	while (ptr)
	//	{
	//		len2++;
	//		ptr = ptr->next;
	//	}//统计两个链表的长度
	//	int len = abs(len1 - len2);
	//	if (len1 > len2)
	//	{
	//		while (len--)
	//		{
	//			pHead1 = pHead1->next;
	//		}
	//	}
	//	else
	//	{
	//		while (len--)
	//		{
	//			pHead2 = pHead2->next;
	//		}
	//	}
	//	while (pHead1 != NULL&&pHead2 != NULL&&pHead1!=pHead2)
	//	{
	//		pHead1 = pHead1->next;
	//		pHead2 = pHead2->next;
	//	}
	//	return pHead1;
	//}
	//方法二(代码有问题)
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		ListNode* cur = pHead1;
		ListNode* ptr = pHead2;
		while (cur!= ptr)
		{
			cur = (cur == NULL ? pHead2 : cur->next);
			ptr = (ptr == NULL ? pHead1 : ptr->next);
		}
		return cur;
	}
	void display(ListNode* pHead)
	{
		ListNode* pCur = pHead;
		while (pCur)
		{
			cout << pCur->val << " ";
			pCur = pCur->next;
		}
		cout << endl;
	}
};
int main()
{
	Solution s;
	ListNode* pl1 = new ListNode(0);
	ListNode* pl2 = new ListNode(-1);
	ListNode*node1 = new ListNode(1);
	ListNode*node2= new ListNode(2);
	ListNode*node3 = new ListNode(3);
	ListNode*node4 = new ListNode(4);
	ListNode*node5 = new ListNode(5);
	ListNode*node6 = new ListNode(6);
	ListNode*node7 = new ListNode(7);
	ListNode*node11 = new ListNode(11);
	ListNode*node12 = new ListNode(12);
	ListNode*node13 = new ListNode(13);

	pl2->next = node11;
	node11->next = node12;
	node12->next = node13;
	node13->next = node4;
	ListNode* pl3 = NULL;
	pl1->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
    pl3 = s.FindFirstCommonNode(pl1, pl2);
	cout << pl3->val << endl;
	//s.display(pl3);
	system("pause");
	return 0;
}

//找数组中第一个重复的数字
//class Solution {
//public:
//	// Parameters:
//	//        numbers:     an array of integers
//	//        length:      the length of array numbers
//	//        duplication: (Output) the duplicated number in the array number
//	// Return value:       true if the input is valid, and there are some duplications in the array number
//	//                     otherwise false
//	bool duplicate(int numbers[], int length, int* duplication) {
//		if (length <= 0||numbers==NULL)
//			return false;
//		for (int i = 0; i < length; i++)
//		{
//			if (numbers[i]<0 || numbers[i]>length - 1)
//			{
//				return false;
//			}
//			while (numbers[i] != i)
//			{
//				if (numbers[i] == numbers[numbers[i]])
//				{
//					*duplication = numbers[i];
//					return true;
//				}
//				//交换numbers[i]和numbers[numbers[i]]
//				int tmp = numbers[i];
//				numbers[i] = numbers[tmp];
//				numbers[tmp] = tmp;
//			}
//		}
//		return false;
//	}
//};
//int main()
//{
//	int arr[] = { 2,3,1,0,2,5,3};
//	int len = sizeof(arr) / sizeof(arr[0]);
//	int dup = 0;
//	Solution s;
//	s.duplicate(arr, len, &dup);
//	cout << "重复的数字是: " << dup << endl;
//	system("pause");
//	return 0;
//}
