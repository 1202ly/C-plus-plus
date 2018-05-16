#include"InsertSort.hpp"
void InsertSort(int *array, size_t size)
{
	for (size_t i = 0; i < size; i++)//��������  
	{
		int key = array[i];//key���浱ǰҪ�����Ԫ��,�Է�ǰ��Ԫ�غ���ʱ��������  
		int end = i - 1;
		while (end >= 0 && key < array[end])//��ǰԪ������֮ǰ��Ԫ�رȴ�С��Ȼ��Ӻ���ǰһ�αȽ�Ѱ�Ҳ���λ��  
		{
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;//����Ԫ��  
	}
}
//����������Ż��汾--->�۰��������
void InsertSort2(int *array, size_t size)
{
	for (size_t i = 1; i < size; i++)
	{
		//�����������Ҳ���Ԫ�ص�λ��  
		int key = array[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)//���ö��ֲ���˼����Ҳ���λ��  
		{
			int mid = left + ((right - left) >> 1);//ȡ�е�  
			if (key < array[mid])//����ֵС���е�ֵ  
			{
				right = mid - 1;//������С����  
			}
			else
			{
				left = mid + 1;//����������С����  
			}
		}//���ˣ��ҵ�����λ��  
		int end = i - 1;
		while (end >= left)//����Ԫ�أ��ɿ��ƶ����ճ�����λ��  
		{
			array[end + 1] = array[end];
			end--;
		}
		array[left] = key;//����Ԫ��  
	}
}
//ϣ������
void ShellSort1(int *array, size_t size)
{
	int gap = 3;//Ҳ����ȡ����//Ҳ����gap/2  
	while (gap)
	{
		for (size_t i = gap; i < size; i++)
		{
			int key = array[i];
			int end = i - gap;
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
		gap--;
	}
}
//������������gapȡ���� gap = gap / 3 + 1  
void ShellSort2(int *array, size_t n)
{
	int gap = n;
	while (gap>1)
	{
		gap = gap / 3 + 1;
		for (size_t i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = array[end + gap];
			while (end >= 0 && array[end]>tmp)
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = tmp;
		}
	}
}
void InsertPrint(int *array, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}