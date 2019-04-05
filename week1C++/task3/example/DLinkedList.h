#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

struct ListNode
{
	ListNode(const int x);
	int data;      /*节点的数据*/
	ListNode* prev;		/*节点的前驱指针*/
	ListNode* next;		/*节点的后继指针*/
};

class DLinkedList
{
private:
	ListNode* _head;	/*指向链表的头节点*/
	ListNode* _tail;	/*指向链表的尾节点*/
public:
	DLinkedList();					/*类的构造函数*/
	DLinkedList(DLinkedList& s);	/*类的拷贝函数*/
	~DLinkedList();					/*类的析构函数*/

public:
	/*在尾部插入一个节点*/
	void PushNode(const int x);

	/*固定位置插入一个节点*/
	void Insert(ListNode* pos, int data);

	/*删除指定的的节点*/
	void Delete(const int x);

	/*查找指定的节点*/
	ListNode* Find(const int x);

	/*对链表进行排序（升序）*/
	void AscendingOrder();

	/*判定列表是否为空*/
	bool isEmpty();

	void show(); /*打印列表数据*/

};


#endif
