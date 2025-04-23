#include "Math.h"
#include<iostream>
using namespace std;
String Math::convertTOHexa(int index)
{
    String str, test;
    while (index)
    {
        int rem = index % 16;
        char sign;
        if (rem > 9)
        {
            sign = 'A' + rem - 10;
        }
        else
        {
            sign = '0' + rem;
        }
        str.push_back(sign);
        index /= 16;
    }
    str.reverse();
    return str;
}
int Math::convertHexaToInt(String& str)
{

    int decimalNumber = 0, digit;
    str.reverse();
    for (int i = 0; i < str.getLength(); i++)
    {
        char ch=str.at(i);
        if ((ch >'F' || ch < 'A') && (ch < '0' || ch > '9'))
        {
            return -1;
        }
        ch = str.at(i);
        digit = convertCharacterHexaToInt(ch);
        decimalNumber += digit * calculatePower(16, i);
    }
    return decimalNumber;
}
int Math::convertCharacterHexaToInt(const char ch)
{
    if (ch >= 48 && ch <= 57)
    {
        return ch - 48;
    }
    if (ch >= 65 && ch <= 70)
    {
        return ch - 55;
    }
    return 0;
}
int Math::calculatePower(int base, int power)
{
    int res = 1;
    for (int i = 1; i <= power; i++)
    {
        res = res * base;
    }
    return res;
}
