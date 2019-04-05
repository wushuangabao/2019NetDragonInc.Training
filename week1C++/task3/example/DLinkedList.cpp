#include "DLinkedList.h"
#include <iostream>
using namespace std;

ListNode::ListNode(const int x)
{
	data = x;
	prev = NULL;
	next = NULL;
}


DLinkedList::DLinkedList()
{
	_head = NULL;
	_tail = NULL;
}

DLinkedList::DLinkedList(DLinkedList & s)
{
	/*复制对象为空链表时，创建空链表*/
	if (s._head == NULL)
	{
		_head = NULL;
		_tail = NULL;
		return;
	}
	ListNode* temp = s._head;
	while (temp)
	{
		/*从复制对象的头结点开始到尾节点结束，依次在链表尾部插入复制对象的节点数据*/
		PushNode(temp->data);
		temp = temp->next;
	}
}

DLinkedList::~DLinkedList()
{
	/*遍历链表，释放节点空间*/
	ListNode* begin = _head;
	while (begin != _tail)
	{
		_head = _head->next;
		delete begin;
		begin = _head;
	}
	_head = NULL;
	_head = NULL;
}

/*在尾部插入一个节点*/
void DLinkedList::PushNode(const int x)
{
	if (_head == NULL)  /*若链表是空链表，则为尾部插入的节点是头结点也是尾节点*/
	{
		_head = new ListNode(x);
		_tail = _head;
	}
	else
	{
		_tail->next = new ListNode(x);
		_tail->next->prev = _tail;
		_tail = _tail->next;
	}

}
/*固定位置插入一个节点（需和Find函数搭配使用）*/
void DLinkedList::Insert(ListNode * pos, int data)
{
	if (pos == _tail)
	{
		/*插入位置在尾节点时，直接在尾节点后添加新节点*/
		PushNode(data);
	}
	else
	{
		ListNode* tar = Find(pos->data);
		if (tar != NULL)  /*插入的指定位置是链表中存在的有效节点*/
		{
			ListNode* newNode = new ListNode(data);
			newNode->next = tar->next;
			newNode->prev = tar;
			tar->next = newNode;
			tar->next->prev = newNode;
		}
	}

}
/*删除指定的的节点*/
void DLinkedList::Delete(const int x)
{
	/*链表非空链表时，继续删除操作*/
	if (this->isEmpty() == false)
	{
		ListNode* target = NULL;
		if (_head->data == x)
		{
			/*删除的指定节点为头结点*/
			target = _head;
			_head = _head->next;
			_head->prev = NULL;
			delete target;
		}
		if (_tail->data == x)
		{
			/*删除的指定节点为尾结点*/
			target = _tail;
			_tail = _tail->prev;
			_tail->next = NULL;
			delete target;
		}
		target = Find(x);
		if (target != NULL)
		{
			/*删除的指定节点为链表中存在的有效节点*/
			target->prev->next = target->next;
			target->next->prev = target->prev;
			delete target;
		}
	}

}

/*查找指定的节点*/
ListNode * DLinkedList::Find(const int x)
{
	if (this->isEmpty() == true)
	{
		return NULL;
	}
	else
	{
		ListNode* begin = _head;
		while (begin != NULL)
		{
			if (begin->data == x)
			{
				return begin;
			}
			begin = begin->next;
		}
	}
	return NULL;
}
/*对链表进行冒泡排序（升序）*/
void DLinkedList::AscendingOrder()
{
	ListNode* p;
	ListNode* q;

	for (p = _head; p->next != NULL; p = p->next)
	{
		for (q = p->next; q != NULL; q = q->next)
		{
			if (q->data < p->data)
			{
				int temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
}

bool DLinkedList::isEmpty()
{
	if (_head == NULL)
	{
		cout << "链表为空链表" << endl;
		return true;
	}
	return  false;
}

void DLinkedList::show()
{
	ListNode* begin;
	for (begin = _head; begin != NULL; begin = begin->next)
	{
		cout << begin->data << " ";
	}
	cout << endl;
}


