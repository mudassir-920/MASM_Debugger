#include "Register.h"
#include<iostream>
using namespace std;
Register::Register() :mem(4)
{
    ax = bx = cx = dx = 0;

}
void Register::setRegister(int regCode,int val)
{
    if (regCode > 4)
    {
        cout << "\nInvalid Register ERROR!\n";
        return;
    }
    mem.getMemContent(regCode - 1) = val;
 }
short Register::getAx()
{
    return mem.getMemContent(0);
}
short Register::getBx()
{
    return mem.getMemContent(1);
}
short Register::getCx()
{
    return mem.getMemContent(2);
}
short Register::getDx()
{
    return mem.getMemContent(3);
}
Memory& Register::getMemory()
{
    return mem;
}