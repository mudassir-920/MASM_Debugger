#include"Memory.h"
#include "String.h"
#include "Math.h"
#include<iostream>
using namespace std;
Memory::Memory()
{
    memoryPointer = 256;
}
Memory::Memory(const int size):Memory()
{
    memContent = new short[size]();
    memSize = size;
    memoryPointer = 256;
    uinstr = new String *[size];
    for (int i=0;i<size;i++) {
        uinstr[i] = new String();
    }
}
void Memory::saveInstructionInMemory(String * instr , const int index)
{
    (*uinstr)[index] = *instr;
}
String * Memory::extract_instr_string(int index) const
{
    return &(*uinstr)[index];
}
Memory::~Memory()
{
    delete[] memContent;
    memContent = nullptr;
    memSize = 0;
    memoryPointer = 0100;
    for (int i=0;i<memSize-1;i++)
    {
        delete (uinstr)[i];
    }
    delete [] uinstr;
}
// following incrememts the pointer pointing psudeo memory inc after a instructoin by default two due ax al concept
void Memory::incMemoryPointer(int index )
{
    memoryPointer+=index;
}
// check is valid memory is entered
bool Memory::isValidMemory(const int index)
{
    if (index >= 0 && index < 65500)
    {
        return true;
    }
    return false;
}

// following sets custom index to pointer of user will
void Memory::setMemoryPointer(const int index)
{
    if (isValidMemory(index))
    {
        memoryPointer = index;
    }
}
int Memory::getMemoryPointer()
{
    return memoryPointer;
}
void Memory::printMemoryLocation(const int addr)
{
    cout << "0920 : ";
    if (addr==-1)
       Math::convertTOHexa(memoryPointer).display();
    else
        Math::convertTOHexa(addr).display();
}
short& Memory::getMemContent(const int index)
{
    if (index > memSize)
    {
        cout << "Invalid Memory Accessed Exiting !\n";
        exit(0);
    }
    return memContent[index];
}