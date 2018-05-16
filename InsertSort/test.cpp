
#include"InsertSort.cpp"
void test()
{
	int array[] = { 2, 3, 4, 5, 7, 8, 0, 6 };
	InsertPrint(array, sizeof(array) / sizeof(array[0]));
	//InsertSort(array, sizeof(array) / sizeof(array[0]));
	//InsertPrint(array, sizeof(array) / sizeof(array[0]));
	//InsertSort2(array, sizeof(array) / sizeof(array[0]));
	//InsertPrint(array, sizeof(array) / sizeof(array[0]));
	//ShellSort1(array, sizeof(array) / sizeof(array[0]));
	//InsertPrint(array, sizeof(array) / sizeof(array[0]));
	ShellSort2(array, sizeof(array) / sizeof(array[0]));
	InsertPrint(array, sizeof(array) / sizeof(array[0]));
}
int main()
{
	test();
	system("pause");
	return 0;
}