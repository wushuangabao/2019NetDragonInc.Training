#include "DataType.h"
#include <iostream>


DataType::DataType()
{
	data = 0; pre = NULL; next = NULL; b = false;
}

DataType::DataType(int i)
{
	data = i; pre = NULL; next = NULL; b = false;
}

DataType::~DataType()
{
	data = 0; pre = NULL; next = NULL; b = NULL;
}

bool operator<(DataType& d1, DataType& d2)
{
	if (d1.data < d2.data) return true;
	else return false;
}

bool operator>(DataType& d1, DataType& d2)
{
	if (d1.data > d2.data) return true;
	else return false;
}

bool operator==(DataType& d1, DataType& d2)
{
	if (d1.data == d2.data) return true;
	else return false;
}

