//# C-plus-plus
#include<iostream>
using namespace std;
#include<assert.h>
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
//链表的合并
//class Solution {
//public:
//	typedef int DataType;
//	void Push(ListNode** pplist, DataType data)
//	{
//		assert(pplist);
//		ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
//		if (newNode == NULL)
//		{
//			perror("newNode");
//			exit(EXIT_FAILURE);
//		}
//		newNode->val = data;
//		newNode->next = NULL;
//		newNode->next = *pplist;
//		*pplist = newNode;
//	}
//	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
//	{
//		ListNode* head = NULL;
//		ListNode* cur = NULL;
//		if (pHead1 == NULL&&pHead2 == NULL)
//		{
//			return NULL;
//		}
//		if (pHead1 == NULL)
//		{
//			return pHead2;
//		}
//		if (pHead2 == NULL)
//		{
//			return pHead1;
//		}
//		if ((pHead1->val) < (pHead2->val))
//		{
//			head = pHead1;
//			cur = head;
//			pHead1 = pHead1->next;
//		}
//		else
//		{
//			head = pHead2;
//			cur = head;
//			pHead2 = pHead2->next;
//		}
//		while (pHead1 != NULL&&pHead2 != NULL)
//		{
//			if ((pHead1->val)< (pHead2->val))
//			{
//				cur->next=pHead1;
//				pHead1 = pHead1->next;
//				cur = cur->next;
//			}
//			else
//			{
//				cur->next = pHead2;
//				pHead2 = pHead2->next;
//				cur = cur->next;
//			}
//		}
//		if (pHead1 != NULL)
//		{
//			cur->next= pHead1;
//		}
//		if (pHead2 != NULL)
//		{
//			cur->next = pHead2;
//		}
//		return head;
//	}
//	void display(ListNode* pHead)
//	{
//		ListNode* pCur = pHead;
//		while (pCur)
//		{
//			cout << pCur->val << " ";
//			pCur = pCur->next;
//		}
//		cout << endl;
//	}
//};
//链表的逆置
//class Solution {
//public:
//	typedef int DataType;
//	void Push(ListNode** pplist, DataType data)
//	{
//		assert(pplist);
//		ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
//		if (newNode == NULL)
//		{
//			perror("newNode");
//			exit(EXIT_FAILURE);
//		}
//		newNode->val = data;
//		newNode->next = NULL;
//		newNode->next = *pplist;
//		*pplist = newNode;
//	}
//	ListNode* ReverseList(ListNode* pHead) {
//		ListNode* NewList = NULL;
//		ListNode* cur = pHead;
//		while (cur)
//		{
//			//1.摘结点
//			ListNode* ptr = cur;
//			cur = cur->next;
//			//头插
//			ptr->next = NewList;
//			NewList = ptr;
//		}
//		return NewList;
//	}
//	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
//		if (pHead1 == NULL||pHead2 == NULL)
//		{
//			return NULL;
//		}
//		if (pHead1->val == pHead2->val)
//		{
//			return pHead1;
//		}
//		ListNode* cur = NULL;
//		while (pHead1 != NULL&&pHead1 != NULL)
//		{
//			if (pHead1->val == pHead2->val)
//			{
//				cur = pHead1;
//				return cur;
//			}
//			pHead1 = pHead1->next;
//			pHead2 = pHead2->next;
//		}
//		return cur;
//	}
//	void display(ListNode* pHead)
//	{
//		ListNode* pCur = pHead;
//		while (pCur)
//		{
//			cout << pCur->val << " ";
//			pCur = pCur->next;
//		}
//		cout << endl;
//	}
//};
//int main()
//{
//	Solution s;
//	ListNode* pl1=NULL;
//	ListNode* pl2=NULL;
//	s.Push(&pl1, 5);
//	s.Push(&pl1, 3);
//	s.Push(&pl1, 1);
//	s.display(pl1);
//	s.Push(&pl2, 7);
//	s.Push(&pl2, 3);
//	s.Push(&pl2, 2);
//	s.display(pl2);
//	ListNode* pl3 = NULL;
//	pl3 = s.ReverseList(pl1);
//	s.display(pl3);
//	system("pause");
//	return 0;
//}

//day11
class Solution {
public:
	// Parameters:
	//        numbers:     an array of integers
	//        length:      the length of array numbers
	//        duplication: (Output) the duplicated number in the array number
	// Return value:       true if the input is valid, and there are some duplications in the array number
	//                     otherwise false
	bool duplicate(int numbers[], int length, int* duplication) {
		if (length <= 0 || numbers == NULL)
			return false;
		for (int i = 0; i < length; i++)
		{
			if (numbers[i]<0 || numbers[i]>length - 1)
			{
				return false;
			}
			while (numbers[i] != i)
			{
				if (numbers[i] == numbers[numbers[i]])
				{
					*duplication = numbers[i];
					return true;
				}
				//交换numbers[i]和numbers[numbers[i]]
				int tmp = numbers[i];
				numbers[i] = numbers[tmp];
				numbers[tmp] = tmp;
			}
		}
		return false;
	}
};
int main()
{
	int arr[] = { 6, 2, 3, 1, 0, 2, 5, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	int dup = 0;
	Solution s;
	s.duplicate(arr, len, &dup);
	cout << "重复的数字是: " << dup << endl;
	system("pause");
	return 0;
}
