#include<iostream>
#include"String.h"
using namespace std;
enum { EQUAL = 0, LESSER = -1, GREATER = 1, NOT_EQUAL = 0, NOT_FOUND = -1 };
String::String()
{
	data = nullptr;
	size = 0;
}
void String::push_back(char ch)
{
	if (data == nullptr)
	{
		int cap = 2;
		data = new char[cap];
		data[0] = ch;
		data[1] = '\0';
		size = cap;
		return;
	}
	if (getLength() + 1 >= getSize())
	{
		reSize(getSize() * 2);
	}
	int length = getLength();
	data[length] = ch;
	data[length+1] = '\0';
}
String::String(const String& str) : String()
{
	if (str.data == nullptr) {
		return;
	}
	data = new char[str.getSize()];  // Allocate new memory
	size = str.size;
	copyString(data, str.data);  // Copy the contents
}
void String::copyStr(String src)
{
	copyString(data, src.data);
	size = src.getSize();
}
String::String(const char ch) :String()
{
	int cap = 2;
	data = new char[cap];
	data[0] = ch;
	data[1] = '\0';
	size = cap;
}
const int String::getLength(const char* str) const
{
	if (str==nullptr) return 0;
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}
String::String(const char* str) : String()
{
	if (str == nullptr)
		return;
	int length = getLength(str);
	char* temp = new char[length + 1];
	int i = 0;
	for (; i < length; i++)
	{
		temp[i] = str[i];
	}
	temp[i] = '\0';
	data = temp;
	size = length + 1;
}
// for now we are making assignment operator copy costructor
String& String::operator=(const String& other) {
	if (this != &other) 
	{  
		delete[] data;

		// Perform deep copy
		if (other.data == nullptr) {
			data = nullptr;
			size = 0;
		}
		else {
			size = other.size;
			data = new char[size];  // Allocate new memory
			copyString(data, other.data);  // Copy the contents
		}
	}
	return *this;  // Return the current object
}
String::~String()
{	
	if (data == nullptr || getSize()==0)
	{
		return;
	}
	delete[] data;
	data = nullptr;
	size = 0;
}
void String::input()
{
	data = new char[1];
	size = 1;
	int count = 0;
	char ch;
	while (cin.get(ch) && ch != '\n')
	{
		data[count] = ch;
		if (count + 1 == size)
		{
			reSize(size * 2);
		}
		count++;
	}
	data[count] = '\0';
}
void String::reSize(int newSize)
{
	if (newSize < 0)
	{
		return;
	}

	if (newSize == 0)
	{
		delete[] data;
		data = nullptr;
		size = 0;
		return;
	}

	char* temp = new char[newSize];

	int i = 0;
	if (data != nullptr)
	{
		while (i < getLength() && i < newSize - 1)
		{
			temp[i] = data[i];
			i++;
		}
	}

	temp[i] = '\0';

	delete[] data;

	data = temp;
	size = newSize;
}

const bool String::isValidIndex(const int index) const
{
	if (index<0 || index > getLength(data))
		return false;
	return true;
}
char& String::at(const int index)
{
	if (isValidIndex(index))
		return data[index];

	cout << "Invalid Request!";
	exit(0);
}
const char& String::at(const int index) const
{
	if (isValidIndex(index))
		return data[index];

	cout << "Invalid Request!";
	exit(0);
}
const char * String::getCharOfString() const
{
	return data;
}
bool String::isEmpty() const
{
	if (size == 0 || getLength() == 0)
		return true;
	return false;
}
int String::getLength()const
{
	if (data == nullptr)
	{
		return 0;
	}
	return getLength(data);
}
int String::getSize() const
{
	return size;
}
void  String::display() const
{
	if (data != nullptr)
		cout << data;
}
int String::compare(const char* str1, const char* str2) const
{
	int length1 = getLength(str1);
	int length2 = getLength(str2);
	for (int i = 0; i < length1; i++)
	{
		if (str1[i] > str2[i])
			return GREATER;
		else if (str1[i] < str2[i])
			return LESSER;
	}
	if (length1 != length2)
	{
		return length1 > length2 ? GREATER : LESSER;
	}
	return EQUAL;
}
void String::deAllocate(char* d) const
{
	delete[]  d;
	d = nullptr;
}
int String::find(const String subStr, const int start) const
{
	if (start > getLength() || start < 0 || subStr.isEmpty() || isEmpty())
		return NOT_FOUND;
	int count = 0;
	int length = subStr.getLength();
	char* temp = new char[length + 1];
	for (int i = start; i + length <= getLength(); i++)
	{
		int j = 0;
		while (j < length)
		{
			temp[j] = data[i + j];
			j++;
		}
		temp[j] = '\0';
		if (compare(subStr.data, temp) == EQUAL)
		{
			return i - start;
		}
	}
	deAllocate(temp);
	return NOT_FOUND;
}
void String::insert(const int index, const String substr)
{
	if (!isValidIndex(index))
	{
		return;
	}
	int length1 = getLength();
	int length2 = getLength(substr.data);
	int length = length1 + length2;
	char* temp = new char[length + 1];
	for (int i = 0, j = 0; i + j < length;)
	{
		if (i < index || j >= length2)
		{
			temp[i + j] = data[i];
			i++;
		}
		else
		{
			temp[i + j] = substr.data[j];
			j++;
		}
	}
	temp[length] = '\0';
	this->~String();
	data = temp;
	size = length + 1;
}
void String::remove(const int index, const int count)
{
	if (!isValidIndex(index))
		return;
	int length = getLength();
	if ((index + count > length))
	{
		return;
	}
	char* temp = new char[length - count + 1];
	int i = 0, j = 0;
	for (; i < size; i++)
	{
		if (i<index || i>index + count)
		{
			temp[j] = data[i];
			j++;
		}
	}
	temp[j] = '\0';
	this->~String();
	data = temp;
	size = j;
}
int String::replace(const String& old, const  String& newSubStr)
{
	if (old.isEmpty() || newSubStr.isEmpty())
		return 0;
	int lengthOfNew = newSubStr.getLength(), lengthOfOld = old.getLength();
	int count = 0;
	char* temp = new char[lengthOfOld + 1];
	for (int i = 0; i < getLength();)
	{
		int j = 0;
		for (; j < lengthOfOld; j++)
		{
			temp[j] = data[i + j];
		}
		temp[j] = '\0';
		if (compare(old.data, temp) == EQUAL)
		{
			remove(i, lengthOfOld - 1);
			insert(i, newSubStr);
			i += lengthOfNew;
			count++;
		}
		else
		{
			i++;
		}
	}
	return count;
}
void String::trimLeft()
{
	bool flag = true;
	int i = 0, count = 0;
	do
	{
		if (data[i] == ' ')
			count++;
		else
			flag = false;
		i++;
	} while (flag);
	remove(0, count - 1);
}
void String::trimRight()
{
	int index = getLength() - 1;
	for (int i = 0; i < getSize(); i++)
	{
		if (data[i] == ' ' && data[i - 1] != ' ')
			index = i;
	}
	remove(index, getLength() - 1 - index);
}
void String::trim()
{
	trimRight();
	trimLeft();
}
void String::makeLower()
{
	int cap = getLength();
	char* temp = new char[cap + 1];
	int i = 0;
	for (; i < cap; i++)
	{
		if (isAlpha(data[i]))
		{
			temp[i] = toLower(data[i]);
		}
		else
		{
			temp[i] = data[i];
		}
	}
	temp[i] = '\0';
	this->~String();
	data = temp;
	size = cap + 1;
}
void String::makeUpper()
{
	int cap = getLength();
	char* temp = new char[cap + 1];
	int i = 0;
	for (; i < cap; i++)
	{
		if (isAlpha(data[i]))
		{
			temp[i] = toUpper(data[i]);
		}
		else
		{
			temp[i] = data[i];
		}
	}
	temp[i] = '\0';
	this->~String();
	data = temp;
	size = cap + 1;
}
void String::reverse()
{
	int index = getLength() - 1;
	int cap = size;
	char* temp = new char[size + 1];
	int i = 0;
	for (; i < getLength(); i++, index--)
	{
		temp[i] = data[index];
	}
	temp[i] = '\0';
	this->~String();
	data = temp;
	size = cap;
}
void String::shrink()
{
	size = getLength();
}
int String::compare(const String str2) const
{
	return compare(data, str2.data);
}
String String::left(const int count)
{
	if (!isValidIndex(count))
	{
		cout << "Invalid Count Entered! ";
		exit(0);
	}
	String temp{ *this };
	int nextAllLength = temp.getLength() - count - 1;
	temp.remove(count, nextAllLength);
	return temp;
}
String String::right(const int count)
{
	if (!isValidIndex(count))
	{
		cout << "Invalid Count Entered! ";
		exit(0);
	}
	String temp{ *this };
	int prevoiusLength = temp.getLength() - count - 1;
	temp.remove(0, prevoiusLength);
	return temp;
}
long long int String::convertToInteger()const
{
	long long int num = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		num = num * 10 + (data[i] - '0');
	}
	return num;
}
float String::convertToFloat() const
{
	float num = 0, decimalPart = 0;;
	int i = 0;
	while (data[i] != '\0' && data[i] != '.')
	{
		num = num * 10 + (data[i] - '0');
		i++;
	}
	if (data[i] == '\0')
		return num;
	i++;
	float part = 10;
	while (data[i] != '\0')
	{
		decimalPart = decimalPart + (data[i] - '0') * 1.0 / part;
		part = part * 10;
		i++;
	}
	num = num + decimalPart;
	return num;
}
String String::concatenate(const String& s2) const
{
	int length = getLength() + s2.getLength();
	char* temp = new char[length + 1];
	copyString(temp, data);
	copyString(temp + getLength(), s2.data);
	return temp;
}
void String::concatEqual(const String& s2)
{
	int index = getLength();
	insert(index, s2);
}
int getLengthOfInteger(long long int num)
{
	int size = 0;
	while (num != 0)
	{
		size++;
		num = num / 10;
	}
	return size;
}
long long int String::reverseInteger(long long int num)
{
	int sum = 0;
	while (num != 0)
	{
		sum = sum * 10 + num % 10;
		num = num / 10;
	}
	return sum;
}
void String::setNumber(const long long int num)
{
	int number = num;
	int length = 0;
	number < 0 ? length++ : 0;
	number = number < 0 ? -number : number;
	length = length + getLengthOfInteger(num);
	char* arr = new char[length + 1];
	int index = 0;
	if (num < 0)
	{
		arr[0] = '-';
		index++;
	}
	number = reverseInteger(number);
	while (number != 0)
	{
		arr[index] = number % 10 + '0';
		number = number / 10;
		index++;
	}
	arr[index] = '\0';
	data = arr;
	size = length;
}

bool String::isAlpha() 
{
	for (int i = 0; i < this->getLength(); i++)
	{
		if(!isAlpha(this->at(i)))
			return false;
	}
	return true;
}
bool String::isAlpha(char ch)
{
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
	{
		return true;
	}
	return false;
}
bool String::isNum() const 
{
	for (int i = 0; i < this->getLength(); i++)
	{
		if (data[i] > '9' && data[i] < '0')
		{
			return false;
		}
	}
	return true;
}
char String::toUpper(char ch)
{
	if (!isAlpha(ch))
		return ch;
	if (ch >= 'a')
		return ch - 32;
	else
		return ch;
}
char String::toLower(char ch)
{
	if (!isAlpha(ch))
		return ch;
	if (ch <= 'Z')
		return ch + 32;
	else
		return ch;
}
void String::copyString(char* dest, const char* src) const
{
	if (src == nullptr ||dest==nullptr)
		return;
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}