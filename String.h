#pragma once
#ifndef STRING_H
#define STRING_H
class String
{
    char* data;
    int size;
    const int getLength(const char* str) const;
    const bool isValidIndex(const int index) const;
    bool isAlpha(char ch);
    char toUpper(char ch);
    char toLower(char ch);
    int compare(const char* str1, const char* str2) const;
    void deAllocate(char* d) const;
    void copyString(char* dest, const char* src) const;
    long long int reverseInteger(long long int num);
public:
    void push_back(char ch);
    String(const String&);
    String();
    String(char ch);
    String(const char* str);
    String& operator=(const String& other);
    ~String();
    void copyStr(String src);
    void input();
    char& at(int index);
    const char& at(const int index)const;
    const char * getCharOfString() const;
    bool isEmpty() const;
    int getLength() const;
    int getSize() const;
    void display() const;
    void reSize(int newSize);
    int  find(const String subStr, const int start = 0) const;
    void insert(const int index, const String substr);
    void remove(const int index, const int count = 1);
    int replace(const String& old, const String& newSubStr);
    void trimLeft();
    void trimRight();
    void trim();
    void makeLower();
    void makeUpper();
    void reverse();
    void shrink();
    int compare(const String str2) const;
    String left(const int count);
    String right(const int count);
    long long int convertToInteger() const;
    float convertToFloat() const;
    String concatenate(const String& s2) const;
    void concatEqual(const String& s2);
    void setNumber(const long long int num);
    bool isAlpha();
    bool isNum() const;
};
#endif
