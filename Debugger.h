#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "String.h"
#include "Instructions.h"
class Debugger
{
    const int noc;  // number of commands
    int opCode;
    String commandName[19];
    String commandSymbol[19];
    String commandParameter[19];
    bool isValidIndex(int index);
public:
    Debugger();
    void displayComands();
    String getCommandSymbol(int index);
    String getCommandName(int index);
    String getCommandParameter(int index);
    void startDebug();
    void showError();
};
#endif