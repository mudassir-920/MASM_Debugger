#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include"Debugger.h"
#include "Memory.h"
#include "String.h"
#include "Register.h"
#include <fstream>
class Instructions
{
    String _file_name;
    std::fstream  saverFile;
    int opCode;
    Memory mem;
    String inputStr;
    // following are being made to store something
    Register reg;
    short insCode;
    short regCode;
    int number;

    // below variables will be used for dump so we want start and end
    int start;
    int end;

    // below will store the index of addrss
    int address;


    int getOpCode(char& ins, char* arr);
    bool decodeAssembleSt(String str);
    void decodeDump(String& str);
    bool decodeEnter(String& str);
    bool decodeRange(String & str);

    bool isLower(char ch);
    void showError();
    void showFeatureUnavailable();
    bool decode_Reg(String & str);
    bool assembleFlag;
public:
    Instructions();
    int getInstruction();
    void assemble();
    void compare(String range ,String addr);
    void dump();
    void enter();
    void fill();
    void go();
    void hex(String &);
    void input();
    void load();
    void move(String &,String &);
    void name();
    void output();
    void proceed();
    void quit();
    void register1(String &);
    void search(String str, int val);
    void trace(String &str);
    void unassemble(String & );
    void write();
    void _mov(Memory& mem,int index, int val);
};
#endif