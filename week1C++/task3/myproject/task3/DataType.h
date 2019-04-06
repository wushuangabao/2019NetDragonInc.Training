#ifndef _DATATYPE_H_
#define _DATATYPE_H_

class DataType
{
public:
	bool b; //是否在链表中
	DataType* pre;
	DataType* next;

	DataType();
	DataType(int i);
	~DataType();

	int getData() { return data; }

	friend bool operator<(DataType& d1, DataType& d2);
	friend bool operator>(DataType& d1, DataType& d2);
	friend bool operator==(DataType& d1, DataType& d2);
private:
	int data;
};

#endif // !_DATATYPE_H_

