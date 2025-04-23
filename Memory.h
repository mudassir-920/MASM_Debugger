#ifndef MEMORY_H
#define MEMORY_H
#include "String.h"
class Memory
{
    short  * memContent;
    int memSize;
    char* memInsRecord;
    int memoryPointer;
    static bool isValidMemory(int index);
    String ** uinstr ;
public:
    Memory();
    Memory(int size);
    ~Memory();
    void incMemoryPointer(int index=1);
    void setMemoryPointer(int index);
    int getMemoryPointer();
    void printMemoryLocation(int addr=-1);
    short& getMemContent(int index);
    void saveInstructionInMemory(String * instr ,int index);
    String * extract_instr_string(int index) const;
};
#endif