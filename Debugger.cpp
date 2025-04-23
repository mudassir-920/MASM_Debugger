#include"Debugger.h"
#include<iostream>

#include "Math.h"
using namespace std;
#include "String.h"
#include<iomanip>
#include"Instructions.h"

Debugger::Debugger() : noc(19) {
    opCode = 0;
    const char *name[19] = {
        "assemble   ", "compare   ", "dump      ", "enter     ", "fill      ", "go        ", "hex       ", "input     ",
        "load      ", "move      ", "name      ", "output    ", "proceed   ", "quit      ", "register  ", "search    ",
        "trace     ", "unassemble", "write     "
    };

    for (int i = 0; i < noc; i++) {
        commandName[i] = name[i];
    }

    //now we intialize the Command Symbol
    const char *symbol[19] = {
        "A", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "W"
    };
    for (int i = 0; i < noc; i++) {
        commandSymbol[i] = symbol[i];
    }

    //now we initialize the command
    // using const char bcz hmara string assignment copy constructor nahi bna abhi
    const char *parameter[19] = {
        "[address]", "range address", "[range]", "address [list]", "range list", "[=address] [addresses]",
        "value1 value2", "port", "[loads from memory]", "range address", "[pathname] [arglist]", "port byte",
        "[=address] ", "   ", "[register]", "range list", "[=address] ", "[range]", "[loads from memory]"
    };
    for (int i = 0; i < noc; i++) {
        commandParameter[i] = parameter[i];
    }
}

void Debugger::displayComands() {
    for (int i = 0; i < noc; i++) {
         cout << "\n" << i + 1 << " ";
         getCommandName(i).display();
         cout << "\t";
         getCommandSymbol(i).display();
         cout << " ";
         getCommandParameter(i).display();
    }
}

String Debugger::getCommandName(int index) {
    if (isValidIndex(index)) {
        return commandName[index];
    }
    return String("");
}

String Debugger::getCommandSymbol(int index) {
    if (isValidIndex(index)) {
        return commandSymbol[index];
    }
    return String("");
}

String Debugger::getCommandParameter(int index) {
    if (isValidIndex(index)) {
        return commandParameter[index];
    }
    return String("");
}

bool Debugger::isValidIndex(int index) {
    return (index >= 0 && index < noc);
}

//  following will start the interface with a loop until q : quit is entered in outer loop
void Debugger::startDebug() {
    Instructions ins;
    do {
        opCode = ins.getInstruction();
        switch (opCode) {
            case 1:
            {
                ins.assemble();
                break;
            }
            case 2:
            {
                cout<<"Enter the Range: \n";
                String str;
                str.input();
                str.trimLeft();
                str.makeUpper();

                cout<<"Enter the Address: \n";
                String addr;
                addr.input();
                addr.trimLeft();
                addr.makeUpper();


                ins.compare(str,addr);
                break;
            }
            case 3: {
                ins.dump();
                break;
            }
            case 4: {
                ins.enter();
                break;
            }
            case 5: {
                ins.fill();
                break;
            }
            case 7:
            {
                cout<<"Enter the String: ";
                String input_string;
                input_string.input();
                ins.hex(input_string);
                break;
            }
            case 8: {
                ins.input();
                break;
            }
            case 9: {
                ins.load();
                break;
            }
            case 10:
            {
                String range_string,address_string;
                cout<<"Enter the Range [Block]: ";
                range_string.input();
                range_string.trimLeft();
                range_string.makeUpper();

                cout<<"Enter the Address [Start of Next Block]: ";
                address_string.input();
                address_string.trimLeft();
                address_string.makeUpper();

                ins.move(range_string,address_string);
                break;
            }
            case 11: {
                ins.name();
                break;
            }
            case 12: {
                ins.output();
                break;
            }
            case 14: {
                ins.quit();
                break;
            }
            case 15:
            {
                cout<<"Enter Register Name ";
                String regString;
                regString.input();
                regString.trimLeft();
                regString.makeUpper();
                ins.register1(regString);
                break;
            }
            case 16:
            {
                cout<<"Enter the Address: \n";
                String str;
                str.input();
                str.trimLeft();
                str.makeUpper();
                cout<<"Enter the Value: \n";
                String val;
                val.input();
                val.trimLeft();
                val.makeUpper();
                ins.search(str,Math::convertHexaToInt(val));
                break;
            }
            case 6:
            case 13:
            case 17:
            {
                cout<<"Enter the Address: ";
                String str;
                str.input();
                ins.trace(str);
                break;
            }
            case 18:
            {
                cout<<"Enter the Range: ";
                String input_string;
                input_string.input();
                ins.unassemble(input_string);
                break;
            }
            case 19: {
                ins.write();
                break;
            }
            default: {
                cout << "    ^\n";
                cout << "      Error\n";
                break;
            }
        }
    } while (opCode != 14);
}

void Debugger::showError() {
    cout << "\t^\n";
    cout << "\tError";
}
