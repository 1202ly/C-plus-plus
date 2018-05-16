#include"InsertSort.hpp"
void InsertSort(int *array, size_t size)
{
	for (size_t i = 0; i < size; i++)//排序趟数  
	{
		int key = array[i];//key保存当前要插入的元素,以防前面元素后移时把它覆盖  
		int end = i - 1;
		while (end >= 0 && key < array[end])//当前元素与他之前的元素比大小，然后从后向前一次比较寻找插入位置  
		{
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;//插入元素  
	}
}
//插入排序的优化版本--->折半插入排序
void InsertSort2(int *array, size_t size)
{
	for (size_t i = 1; i < size; i++)
	{
		//已序序列中找插入元素的位置  
		int key = array[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)//利用二分查找思想查找插入位置  
		{
			int mid = left + ((right - left) >> 1);//取中点  
			if (key < array[mid])//插入值小于中点值  
			{
				right = mid - 1;//向左缩小区间  
			}
			else
			{
				left = mid + 1;//否则，向右缩小区间  
			}
		}//至此，找到插入位置  
		int end = i - 1;
		while (end >= left)//搬移元素，成块移动，空出插入位置  
		{
			array[end + 1] = array[end];
			end--;
		}
		array[left] = key;//插入元素  
	}
}
//希尔排序
void ShellSort1(int *array, size_t size)
{
	int gap = 3;//也可以取素数//也可以gap/2  
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
//下面这种增量gap取的是 gap = gap / 3 + 1  
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