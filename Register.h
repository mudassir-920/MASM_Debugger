#ifndef REGISTER_H
#define REGISTER_H
#include "Memory.h"
class Register
{
    Memory mem;
    short ax,bx,cx,dx;

public:
    Register();
    void setRegister(int regCode,int val);
    short getAx();
    short getBx();
    short getCx();
    short getDx();
    Memory& getMemory();
};

#endif