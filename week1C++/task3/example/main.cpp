#include <iostream>
#include "DLinkedList.h"
#include "main.h"
using namespace std;

int main()
{
	DLinkedList* list1 = new DLinkedList();
	list1->PushNode(99);
	list1->Insert(new ListNode(99), 100);

	DLinkedList* list2 = new DLinkedList(*list1);
	list2->PushNode(12);
	cout << "list2:  ";
	list2->show();
	list2->AscendingOrder();
	cout << "After Ascending Order, list2:  ";
	list2->show();
	
	return 0;
}