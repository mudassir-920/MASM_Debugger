#ifndef MATH_H
#define MATH_H
#include "String.h"
class Math
{
    static int convertCharacterHexaToInt(const char ch);
public:
    static String convertTOHexa(int index);
    static int convertHexaToInt(String& str);
    static int calculatePower(int base, int power);
};
#endif