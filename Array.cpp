#include<iostream>
#include "stdarg.h"
#include"Array.h"
using namespace std;
Array::Array(int cap, ...)
{
	capacity = 0;
	data = nullptr;
	if (cap <= 0)
		return;
	capacity = cap;
	data = new int[cap];
	va_list vList;
	va_start(vList, cap);
	for (int i = 0; i < cap; i++)
	{
		data[i] = va_arg(vList, int);
	}
	va_end(vList);
}
Array::Array(const Array& ref)
{
	if (ref.data == nullptr)
		return;
	int tempCap = ref.getCapacity();
	data = new int[tempCap + 1];
	capacity = tempCap;
	for (int i = 0; i < tempCap; i++)
	{
		data[i] = ref.data[i];
	}
	capacity = ref.capacity;
}
Array::~Array()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	capacity = 0;
}
bool Array::isValidIndex(const int index) const
{
	if (index >= 0 && index < capacity)
	{
		return true;
	}
	return false;
}
int& Array::getSet(int index)  // Agr class non-const hogi to ese preference mile gi why  ?
{
	if (isValidIndex(index))
		return data[index];

	cout << "Invalid Index Requested\n";
	exit(0);
}
const int& Array::getSet(const int index) const
{
	if (isValidIndex(index))
		return data[index];

	cout << "Invalid Index Requested\n";
	exit(0);
}
int Array::getCapacity() const
{
	return capacity;
}
void Array::resize(const int newCapacity)
{
	int* temp = new int[newCapacity];
	for (int i = 0; i < newCapacity && i < capacity; i++)
	{
		temp[i] = data[i];
	}
	this->~Array();
	data = temp;
	capacity = newCapacity;
}