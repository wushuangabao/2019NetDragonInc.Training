#ifndef _LIST_H_
#define _LIST_H_

#define MAX 999999  //链表的最大长度

class DataType;

////////////////////////////////////////////////////////////////
// 双向链表类，该类有默认构造函数、类的拷贝函数、类的析构函数，
// 实现链表添加数据、升序排序、查找链表中某个节点及删除链表中某
// 个节点的操作。
////////////////////////////////////////////////////////////////
class List
{
public:
	DataType* p;  //指向当前数据的指针
	List(void);
	List(List& b);
	~List();
	List& add(DataType& d, const int i);//在指定位置添加数据，添在头部对应的数字是1，尾部对应len+1
	List& add(DataType& d); //在尾部添加数据。
	List& sortRise();  //升序排序
	DataType* findByNum(const int i); //通过位置寻找data，以指针形式返回
	int findTheNum(const int data); //通过数据的内容（DataType的私有成员data的值),查找该数据的位置，若找不到返回0
	List& del(const int i);  //删除第i个数据，删除后p指向下一个数据
	List& del(DataType& data); //删除数据内容为data的数据（若有超过一个，删除全部）
private:
	DataType* head;
	DataType* tail;
	int len;  //元素的总个数
	void QSortRise(DataType* i, DataType* j);//对i到j的数据进行快速排序
};

#endif // !_LIST_H_