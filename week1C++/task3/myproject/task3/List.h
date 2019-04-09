#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <iostream>
using namespace std;

////////////////////////////////////
// 链表元素类
////////////////////////////////////
template <typename T>
class DataType
{
public:
	bool b; //是否在链表中
	DataType* pre;
	DataType* next;

	DataType() {
		data = T(); pre = NULL; next = NULL; b = false;
	};
	DataType(T i) {
		data = i; pre = NULL; next = NULL; b = false;
	};
	~DataType() {
		data = NULL; pre = NULL; next = NULL; b = NULL;
	};

	T getData() { return data; }

	friend bool operator<(DataType& d1, DataType& d2) {
		if (d1.data < d2.data) return true;
		else return false;
	};
	friend bool operator>(DataType& d1, DataType& d2) {
		if (d1.data > d2.data) return true;
		else return false;
	};
	friend bool operator==(DataType& d1, DataType& d2) {
		if (d1.data == d2.data) return true;
		else return false;
	};
private:
	T data;
};

////////////////////////////////////////////////////////////////
// 双向链表类，该类有默认构造函数、类的拷贝函数、类的析构函数，
// 实现链表添加数据、升序排序、查找链表中某个节点及删除链表中某
// 个节点的操作。
////////////////////////////////////////////////////////////////
template <typename T>
class List
{
public:
	DataType<T>* p;  //指向当前数据的指针
	List() {
		p = NULL; head = NULL; tail = NULL; len = 0;
	};
	List(List<T>& b) {
		p = b.p; head = b.head; tail = b.tail; len = b.len;
	};
	~List() {
		p = NULL; head = NULL; tail = NULL;
		len = 0;
	};
	List& add(DataType<T>& d, const int i);//在指定位置添加数据，添在头部对应的数字是1，尾部对应len+1
	List& add(DataType<T>& d); //在尾部添加数据。
	List& sortRise();  //升序排序
	DataType<T>* findByNum(const int i); //通过位置寻找data，以指针形式返回
	int findTheNum(const T data); //通过数据的内容（DataType的私有成员data的值),查找该数据的位置，若找不到返回0
	List& del(const int i);  //删除第i个数据，删除后p指向下一个数据
	List& del(DataType<T>& data); //删除数据内容为data的数据（若有超过一个，删除全部）
private:
	DataType<T>* head;
	DataType<T>* tail;
	int len;  //元素的总个数
	void QSortRise(DataType<T>* i, DataType<T>* j);//对i到j的数据进行快速排序
};

/////////////////////////////
// 链表类的成员方法定义
/////////////////////////////
template <typename T>
List<T>& List<T>::sortRise()
{
	QSortRise(head, tail);
	return *this;
}

// 对i到j的数据进行快速排序
template <typename T>
void List<T>::QSortRise(DataType<T>* fst, DataType<T>* lst)
{
	DataType<T>* p = fst->next;
	if (!p) {
		cout << "Error" << endl;
		return;
	}
	p = fst;
	if (p == lst)  return;

	// 开始快速排序：
	DataType<T> *i, *j;
	i = fst; j = lst;
	while (true) {
		if (i == j)
			break;
		while (true) {
			if (*j < *p) {
				// 将i,j所指数据在链表中的位置交换，接着交换i与j指针
				// 注意是否要处理头尾指针及fst\lst指针
				if (i == head) {
					head = j;
					fst = j;
				}
				else {
					if (i == fst) fst = j;
					i->pre->next = j;
				}
				if (j == tail) {
					tail = i; lst = i;
				}
				else {
					if (lst == j) lst = i;
					j->next->pre = i;
				}
				if (i->next == j) {
					i->next = j->next; j->next = i;
					j->pre = i->pre; i->pre = j;
				}
				else {
					i->next->pre = j;
					j->pre->next = i;
					DataType<T>* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType<T>* t;
				t = i;  i = j;	j = t;
				break;  //跳出j的循环，开始i的循环
			}
			else {
				j = j->pre;
				if (i == j) break;  //跳出j的循环，然后完成这一趟快排
			}
		}
		while (true) {
			if (i == j)  break;
			if (*i > *p) {
				if (i == head) {
					head = j;
					fst = j;
				}
				else {
					if (i == fst) fst = j;
					i->pre->next = j;
				}
				if (j == tail) {
					tail = i; lst = i;
				}
				else {
					if (lst == j)  lst = i;
					j->next->pre = i;
				}
				if (i->next == j) {
					i->next = j->next; j->next = i;
					j->pre = i->pre; i->pre = j;
				}
				else {
					i->next->pre = j;
					j->pre->next = i;
					DataType<T>* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType<T>* t;
				t = i;  i = j;	j = t;
				break;  //跳出i的循环，开始j的循环
			}
			else {
				i = i->next;
				if (i == j)	break;
			}
		}
	}
	// 一趟快排结束，开始对p指针前后的链表进行快排
	if (p != lst && p->next != NULL)
		this->QSortRise(p->next, lst);
	if (p != fst && p->pre != NULL)
		this->QSortRise(fst, p->pre);
}

template <typename T>
DataType<T>* List<T>::findByNum(const int i)
{
	// 位置i超出范围
	if (i > len || i < 1) {
		cout << i << " is too big or too small." << endl;
		return NULL;
	}
	// 从前往后找
	if (i < len / 2) {
		p = head;
		for (int j = 1; j < i; j++)
		{
			if (i == j)  return p;
			p = p->next;
		}
	}
	// 从后往前找
	else {
		p = tail;
		for (int j = len; j > 0; j--)
		{
			if (i == j)  return p;
			p = p->pre;
		}
	}
	return p;
}

template <typename T>
int List<T>::findTheNum(const T da)
{
	p = head;
	int i = 1;
	while (p)
		if (p->getData() == da)
			return i;
		else
			if (p != tail) {
				p = p->next;
				i++;
			}
			else	return 0; //找不到，返回值为0
}

template <typename T>
List<T>& List<T>::add(DataType<T>& data, int index)
{
	if (index > len + 1) {
		cout << "Error! The index number is too big." << endl;
		return *this;
	}
	else if (index < 1) {
		cout << "Error! The index number cna't bee negative." << endl;
		return *this;
	}
	// 如果链表为空
	if (len == 0) {
		head = &data;
		tail = &data;
		p = &data;
		len++;
		data.b = true;
		return *this;
	}
	// 检查data是否已经添加进链表了
	else if (data.b == true) {
		cout << "This data has aleady in the List." << endl;
		return *this;
	}
	// 在最末尾插入data
	if (index == len + 1) {
		tail->next = &data;
		data.pre = tail;
		data.next = NULL;
		tail = &data;
		len++;
		data.b = true;
		return *this;
	}
	// 在第index个数据前面插入data
	else
	{
		int half = len / 2;
		if (index <= half) {
			p = head;
			for (int j = 1; j <= half; j++) {
				if (index == j) break;
				p = p->next;
			}
		}
		else {
			p = tail;
			for (int j = len; j > half; j--) {
				if (index == j)  break;
				p = p->pre;
			}
		}
		if (index != 1) {
			data.pre = p->pre;
			p->pre->next = &data;
		}
		else { //当添加在最前面时
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

template <typename T>
List<T>& List<T>::add(DataType<T>& data)
{
	return this->add(data, len + 1);
}

template <typename T>
List<T>& List<T>::del(int i)
{
	findByNum(i); //让p指向第i个数据
	DataType<T>* pp = p;
	len--;
	if (len == 0) {
		head = NULL; tail = NULL; p = NULL;
		pp->~DataType<T>();
		return *this;
	}
	if (p == head) {
		head = p->next;
		p = head; p->pre = NULL;
		pp->~DataType<T>();
	}
	else if (p == tail) {
		tail = p->pre;
		p = tail; p->next = NULL;
		pp->~DataType<T>();
	}
	else {
		p = p->next;  //删除后，p指向下一个数据
		p->pre = pp->pre;
		pp->pre->next = p;
		pp->~DataType<T>();
	}
	return *this;
}

template <typename T>
List<T>& List<T>::del(DataType<T>& dt)
{
	T d = dt.getData();
	int i = findTheNum(d);
	while (i != 0) {
		del(i);
		i = findTheNum(d);
	}
	return *this;
}


#endif