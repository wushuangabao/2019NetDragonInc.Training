// task3.cpp: 定义控制台应用程序的入口点。
// 注释：Ctrl+K Ctrl+C
// 取消注释：Ctrl+K Ctrl+U

#include "stdafx.h"
#include "iostream"
#define MAX 999999  //链表的最大len

using namespace std;

///////////////////////////////////////////////////////////////
//数据类，只是用来模拟可能遇到的任一种封装好的数据           //
///////////////////////////////////////////////////////////////
class DataType
{
public:
	bool b;
	DataType* pre;
	DataType* next;
	DataType() { data = 0;pre = NULL;next = NULL;b = false; }
	DataType(int i) { data = i;pre = NULL;next = NULL;b = false; }
	//~DataType() { data = NULL;pre = NULL;next = NULL;b = NULL;	}
	int getData() { return data; }
	friend bool operator<( DataType& d1, DataType& d2);
	friend bool operator>( DataType& d1, DataType& d2);
	friend bool operator==( DataType& d1, DataType& d2);
private:
	int data;
};

bool operator<( DataType& d1,  DataType& d2)
{
	if (d1.data < d2.data) return true;
	else return false;
}

bool operator>( DataType& d1,  DataType& d2)
{
	if (d1.data > d2.data) return true;
	else return false;
}

bool operator==( DataType& d1,  DataType& d2)
{
	if (d1.data == d2.data) return true;
	else return false;
}

////////////////////////////////////////////////////////////////
//双向链表类，该类有默认构造函数、类的拷贝函数、类的析构函数，//
//实现链表添加数据、升序排序、查找链表中某个节点及删除链表中某//
//个节点的操作。                                              //
////////////////////////////////////////////////////////////////
class LianBiao
{
public:
	DataType* p;  //指向当前数据的指针
	LianBiao(void);
	LianBiao(LianBiao& b);
	~LianBiao();
	LianBiao& add(DataType& d, int i);//在指定位置添加数据，添在头部对应的数字是1，尾部对应len+1（因为len对应原本的尾部数据的前面）
	LianBiao& add(DataType& d); //在尾部添加数据。
	LianBiao& sortRise();  //升序排序
	DataType* findByNum(int i); //通过位置寻找data，以指针形式返回
	int findTheNum(const int data); //通过数据的内容（本示例中DataType的私有成员data的值),查找该数据的位置，若找不到返回0
	LianBiao& del(int i);  //删除第i个数据，删除后p指向下一个数据
	LianBiao& del(DataType& data); //删除数据内容为data的数据（若有超过一个，删除全部）
private:
	DataType* head;
	DataType* tail;
	int len;  //元素的总个数
	void QSortRise(DataType* i, DataType* j);//对i到j的数据进行快速排序
};

LianBiao::LianBiao()
{
	p = 0;head = 0;tail = 0;len = 0;
}

LianBiao::LianBiao(LianBiao& b)
{
	p = b.p;head = b.head;tail = b.tail;len = b.len;
}

LianBiao::~LianBiao()
{
	//这里是否要删除所有数据，即手动析构所有该链表中DataType类型的数据？
	p = NULL;head = NULL;tail = NULL;
	len = 0;
}

LianBiao& LianBiao::sortRise()
{
	QSortRise(head,tail);
	return *this;
}

void LianBiao::QSortRise(DataType* fst,DataType* lst)
{
	DataType* p = fst->next;
	if(p == NULL || p==0)
	{
		cout << "Error" << endl;
		return;
	}
	p = fst;
	if (p == lst) { return; }
	//开始快速排序：
	DataType *i, *j;
	i = fst;j = lst;
	while (1)
	{
		if (i == j)
		{
			break;
		}
		while (1)
		{
			if (*j < *p)  //将i,j所指数据在链表中的位置交换，接着交换i与j指针。注意是否要处理头尾指针及fst\lst指针。
			{
				if (i == head) { 
					head = j;
					fst = j;
				}
				else {
					if (i == fst) { fst = j; }
					i->pre->next = j;
				}
				if (j == tail) { 
					tail = i;
					lst = i;
				}
				else {
					if (lst == j) { lst = i; }
					j->next->pre = i;
				}
				if (i->next == j) {
					//这种情况有可能吗？
					i->next = j->next;j->next = i;
					j->pre = i->pre;i->pre = j;
				}
				else {
					i->next->pre = j;
					j->pre->next = i;
					DataType* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType* t;
				t = i;  i = j;	j = t;
				break;  //跳出j的循环，开始i的循环
			}
			else
			{
				j = j->pre;
				if (i == j)
				{
					break;  //跳出j的循环，然后完成这一趟快排
				}
			}
		}
		while (1)
		{
			if (i == j) { break; }
			if (*i > *p)
			{
				if (i == head) {
					head = j;
					fst = j;
				}
				else {
					if (i == fst) { fst = j; }
					i->pre->next = j;
				}
				if (j == tail) {
					tail = i;
					lst = i;
				}
				else {
					if (lst == j) { lst = i; }
					j->next->pre = i;
				}
				if (i->next == j) {
					//这种情况有可能吗？
					i->next = j->next;j->next = i;
					j->pre = i->pre;i->pre = j;
				}
				else {
					i->next->pre = j;
					j->pre->next = i;
					DataType* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType* t;
				t = i;  i = j;	j = t;
				break;  //跳出i的循环，开始j的循环
			}
			else
			{
				i = i->next;
				if (i == j)
				{
					break;
				}
			}
		}
	}  //一趟快排结束，开始对p指针前后的链表进行快排……
	if (p != lst && p->next != NULL) {
		this->QSortRise(p->next, lst);
	}
	if (p != fst && p->pre != NULL) {
		this->QSortRise(fst, p->pre);
	}
}

DataType* LianBiao::findByNum(int i)
{
	if (i > len || i < 1)  //位置i超出范围
	{
		cout << i << " is too big or too small." << endl;
		return NULL;
	}
	if (i < len / 2 )  //从前往后找
	{
		p = head;
		for (int j = 1;j < i;j++)
		{
			if (i == j) { return p; }
			p = p->next; 
		}
	}
	else  //从后往前找
	{
		p = tail;
		for (int j = len;j > 0;j--)
		{
			if (i == j) { return p; }
			p = p->pre;
		}
	}
}

int LianBiao::findTheNum(const int da)
{
	p = head;
	int i=1;
	while (p)
	{
		
		if ( p->getData() == da) {
			return i;
		}
		else {
			if (p != tail) {
				p = p->next;
				i++;
			}
			else {  //找不到，返回值为0
				return 0;
			}
		}
	}
}

LianBiao& LianBiao::add(DataType& data, int index)
{
	if (index > len + 1)
	{
		cout << "Error! The index number is too big." << endl;
		return *this;
	}
	else if (index < 1)
	{
		cout << "Error! The index number cna't bee negative." << endl;
		return *this;
	}
	if (len == 0) { //如果链表为空
		head = &data;
		tail = &data;
		p = &data;
		len++;
		data.b = true;
		return *this;
	}
	else if (data.b == true)//否则检查dat是否已经添加进链表了
	{
		cout << "This data has aleady in the LianBiao." << endl;
		return *this;
	}
	if (index == len + 1) //如果插入位置在最末尾
	{
		tail->next = &data;
		data.pre = tail;
		data.next = NULL;
		tail = &data;
		len++;
		data.b = true;
		return *this;
	}
	else //否则在第index个数据前面插入data
	{
		int half = len / 2;
		if (index <= half)
		{
			p = head;
			for (int j = 1;j <=half;j++)
			{
				if (index == j) { break;}
				p = p->next;
			}
		}
		else
		{
			p = tail;
			for (int j = len;j > half;j--)
			{
				if (index == j) { break; }
				p = p->pre;
			}
		}
		if (index!=1) { 
			data.pre = p->pre;
			p->pre->next = &data;
		}
		else {//当添加在最前面时
			head = &data;
			data.pre = NULL;
		}
		p->pre = &data;
		data.next = p;
		len++;
		data.b = true;
		return *this;
	}
}

LianBiao& LianBiao::add(DataType& data)
{
	return this->add(data, len + 1);
}

LianBiao& LianBiao::del(int i)
{
	findByNum(i);//作用是让p指向第i个数据
	DataType* pp = p;
	len--;
	if (len == 0)
	{
		head = NULL;tail = NULL;p = NULL;
		pp->~DataType();
		return *this;
	}
	if (p == head)
	{
		head = p->next;
		p = head;p->pre = NULL;
		pp->~DataType();
	}
	else if (p == tail)
	{
		tail = p->pre;
		p = tail;p->next = NULL;
		pp->~DataType();
	}
	else
	{
		p = p->next;  //删除后，p指向下一个数据
		p->pre = pp->pre;
		pp->pre->next = p;
		pp->~DataType();
	}
	return *this;
}

LianBiao& LianBiao::del(DataType& dt)
{
	int d = dt.getData();
	int i = findTheNum(d);
	while (i != 0)
	{
		del(i);
		i = findTheNum(d);
	}
	return *this;
}


////////////////////////////////////
//  用例：                        //
////////////////////////////////////
int main()
{
	DataType* datas;
	datas = new DataType[20];  //数据数组
	LianBiao lianbiao1;
	cout << "Start to add datas to lianbiao1..." << endl;
	for(int i=0;i < 20;i++)
	{
		DataType data(100 - i);
		*(datas + i) = data;
		lianbiao1.add(*(datas + i));
	}	
	cout << endl;

	cout << "Start to create lianbiao2 based on lianbiao1..." << endl;
	LianBiao lianbiao2=lianbiao1;
	cout << endl;
	cout << "Start to get data from lianbiao1:" << endl;
	DataType* dataa=lianbiao1.findByNum(2);//取第2个元素，同时lianbiao.p也指向了该元素
	int d = lianbiao1.p->getData();
	cout << d << endl;
	cout << endl;

	cout << "Putout all datas in lianbiao1:" << endl;
	for (int i = 1;i < 21;i++)
	{
		dataa = lianbiao1.findByNum(i);
		d = lianbiao1.p->getData();
		cout << d << "  ";
	}
	cout << endl;
	//d = (*dataa).getData();cout << d << endl;//错误？！不能用此方法获取data的数据，why?
	cout << endl;

	cout << "Start to sort lianbiao1..." << endl;
	lianbiao1.sortRise();
	for (int i = 1;i < 21;i++)
	{
		dataa=lianbiao1.findByNum(i);
		d = lianbiao1.p->getData();
		cout << d << "  ";
	}
	cout << endl << endl;

	cout << "Find the location of data 187...(0 means cannot find)" << endl;
	int loc = lianbiao1.findTheNum(187);
	cout << loc << endl;
	cout << "Find the location of data 87...(0 means cannot find)" << endl;
	loc = lianbiao1.findTheNum(87);
	cout << loc << endl << endl;

	cout << "Start to delete the first data..." << endl;
	lianbiao1.del(1);
	cout << "Start to delete the second data..." << endl;
	lianbiao1.del(2);
	cout << "Start to delete the data 90..." << endl;
	lianbiao1.del(*(datas + 10));
	cout << "Now the lianbiao1 includes:" << endl;
	for (int i = 1;i < 18;i++)
	{
		dataa = lianbiao1.findByNum(i);
		d = lianbiao1.p->getData();
		cout << d << "  ";
	}
	cout << endl << endl;

	int in;
	cout << "Input any integer to quit." << endl;
	cin >> in;
	delete[] datas;
	return 0;
}