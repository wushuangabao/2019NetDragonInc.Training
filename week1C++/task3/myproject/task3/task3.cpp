#include "DataType.h"
#include "List.h"
#include <iostream>

using namespace std;

int main()
{
	DataType* datas = new DataType[20];  //数据数组
	List list1;

	cout << "Start to push datas to list1..." << endl << endl;
	for (int i = 0; i < 20; i++)
	{
		DataType data(100 - i);
		*(datas + i) = data;
		list1.add(*(datas + i));
	}

	cout << "Start to create list2 based on list1..." << endl << endl;
	List list2 = list1;

	cout << "Get the second data of list1: ";
	DataType* dataa = list1.findByNum(2); //取第2个元素，同时list.p也指向了该元素
	int d = list1.p->getData();
	cout << d << endl << endl;

	cout << "Output all datas in list1:" << endl;
	for (int i = 1; i < 21; i++)
	{
		dataa = list1.findByNum(i);
		d = (*dataa).getData();  //或者d = list1.p->getData();
		cout << d << "  ";
	}
	cout << endl << endl;

	cout << "Start to sort list1..." << endl;
	list1.sortRise();
	for (int i = 1; i < 21; i++)
	{
		dataa = list1.findByNum(i);
		d = list1.p->getData();
		cout << d << "  ";
	}
	cout << endl << endl;

	cout << "Find the location of data 187...(0 means not find)" << endl;
	int loc = list1.findTheNum(187);
	cout << loc << endl;
	cout << "Find the location of data 87...(0 means not find)" << endl;
	loc = list1.findTheNum(87);
	cout << loc << endl << endl;

	cout << "Delete the first data..." << endl;
	list1.del(1);
	cout << "Delete the second data..." << endl;
	list1.del(2);
	cout << "Delete the data 90..." << endl;
	list1.del(*(datas + 10));
	cout << "Now the list1 includes:" << endl;
	for (int i = 1; i < 18; i++)
	{
		dataa = list1.findByNum(i);
		d = list1.p->getData();
		cout << d << "  ";
	}
	cout << endl << endl;

	int in;
	cout << "Input any integer to quit." << endl;
	cin >> in;
	delete[] datas;
	return 0;
}