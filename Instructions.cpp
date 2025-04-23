#include<iostream>
#include<iomanip>
#include"Instructions.h"
#include"Debugger.h"
#include "Memory.h"
#include "String.h"
#include"Math.h"
#include "Array.h"
#include <fstream>
using namespace std;
enum DecodedOperand {MOV=1,ADD,SUB, INC,DEC,  INVALID_OPERAND};
enum { EQUAL = 0, LESSER = -1, GREATER = 1, NOT_EQUAL = 0, NOT_FOUND = -1 };
Instructions::Instructions():mem(65535)
{
	opCode = 0;
	insCode = 0;
	regCode = 0;
	assembleFlag = false;
	_file_name.concatEqual("Memory.txt");;
}
bool Instructions::isLower(char ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		return true;
	}
	return false;
}
int Instructions::getInstruction()
{
	Debugger dbg;
	char arr[38] = { 'A','C','D','E','F','G','H','I','L','M','N','O','P','Q','R','S','T','U','W' };
	char ins;
	do
	{
		cout << "\n_";
		cin.get(ins);
		if (isLower(ins))
		{
			ins-= 32;
		}
		cin.ignore(100, '\n');
		opCode = getOpCode(ins, arr);
		if (opCode == NOT_FOUND)
		{
			showError();
		}
	} while (opCode == NOT_FOUND);   // invalid again input
	return opCode;
}
int Instructions::getOpCode(char& ins, char* arr)
{
	for (int i = 0; i < 38; i++)
	{
		if (arr[i] == ins)
		{
			return (i + 1);
		}
	}
	return NOT_FOUND;
}
// following will decode the string entered from assemble

bool Instructions::decodeAssembleSt(String str)
{
	bool flag = true;

	//str.display();
	String s;
	int i = 0;
	for (; i < 3; )
	{
		s.push_back(str.at(i));
		i++; 
	}
	if (s.compare("MOV") == EQUAL || s.compare("ADD") == EQUAL || s.compare("SUB") == EQUAL || s.compare("INC") == EQUAL || s.compare("DEC") == EQUAL)
	{
		if (s.compare("MOV") == EQUAL)
		{
			insCode = 1;
		}
		else if (s.compare("ADD") == EQUAL)
		{
			insCode = 2;
		}
		else if (s.compare("SUB") == EQUAL)
		{
			insCode = 3;
		}
		else if (s.compare("INC") == EQUAL)
		{
			insCode = 4;
		}
		else
		{
			insCode = 5;
		}
		flag = true;
	}
	else
	{
		return false;
	}

	if (str.at(i) != ' ')
	{
		return false;
	}
	else
	{
		i++;
	}
	s.reSize(0);
	for (int j = 0; j < 2; j++)
	{
		s.push_back(str.at(i));
		i++;
	}
	if (s.compare("AX") == EQUAL || s.compare("BX") == EQUAL || s.compare("CX") == EQUAL || s.compare("DX") == EQUAL)
	{
		if (s.compare("AX") == EQUAL)
		{
			regCode = 1;
		}
		else if (s.compare("BX") == EQUAL)
		{
			regCode = 2;
		}
		else  if (s.compare("CX") == EQUAL)
		{
			regCode = 3;
		}
		else
		{
			regCode = 4;
		}
		if (insCode ==4 || insCode == 5)
			return true;
	}
	else
	{
		showError();
		return false;
	}
	if (str.at(i) != ',')
	{
		showError();
		return false;
	}
	else
	{
		i++;
	}
	s.reSize(0);
	// for m=now we are only able to do mov ax,20 only 
	while (str.at(i) != '\0')
	{
		s.push_back(str.at(i));
		i++;
	}
	if (s.isAlpha())
	{
		showFeatureUnavailable();
		return false;
			// get the name of the register whose value is to be determined ?
	}
	else if(s.isNum())
	{
		int num = Math::convertHexaToInt(s);
			//wanna convert the recieved  string number to actual number to store in it Instruction member
		number = num;
	}
	
	return true;
}

// following will change the code into psuedo assembly 
void Instructions::assemble()
{
	String str;
	cout << "\nPress Enter If Want to start from current memory Pointer else:  ";
	cout << "\nEnter the Address: ";
	str.input();
	int location = Math::convertHexaToInt(str);
	if (location > 65535)
	{
		showError();
		return;
	}
	if (location == 0)
		mem.setMemoryPointer(mem.getMemoryPointer());
	else
		mem.setMemoryPointer(location);
	
	do
	{
		mem.printMemoryLocation();
		inputStr.input();
		inputStr.makeUpper();
		// trim right is buggy why?
		inputStr.trimLeft();
		if (inputStr.isEmpty())
			return;
		if (decodeAssembleSt(inputStr))
		{
			mem.saveInstructionInMemory(&inputStr, mem.getMemoryPointer());
			if (insCode == MOV)
			{

				_mov(reg.getMemory(), regCode, number);

				// actual moving data to mem with his memory pointer at default then incrementing it
				_mov(mem, mem.getMemoryPointer(), number);
				mem.incMemoryPointer();

				// register me value store krwani hoti hai memory nbhi 
			}
			else if (insCode == ADD)
			{
				// following will get the current value of ax,bx or any U want
				int temp=reg.getMemory().getMemContent(regCode);
				int sum=temp+number;

				_mov(reg.getMemory(), regCode, sum);

				// actual moving data to mem with his memory pointer at default then incrementing it
				_mov(mem, mem.getMemoryPointer(), sum);
				mem.incMemoryPointer();
			}
			else if (insCode == SUB)
			{
				// following will get the current value of ax,bx or any U want
				int temp=reg.getMemory().getMemContent(regCode);
				int  diff=temp-number;

				_mov(reg.getMemory(), regCode,  diff);

				// actual moving data to mem with his memory pointer at default then incrementing it
				_mov(mem, mem.getMemoryPointer(),  diff);
				mem.incMemoryPointer();
			}
			else if (insCode == INC)
			{
				// following will get the current value of ax,bx or any U want
				int temp=reg.getMemory().getMemContent(regCode);
				int sum=temp+1;

				_mov(reg.getMemory(), regCode, sum);

				// actual moving data to mem with his memory pointer at default then incrementing it
				_mov(mem, mem.getMemoryPointer(), sum);
				mem.incMemoryPointer();

			}
			else if (insCode == DEC)
			{
				// following will get the current value of ax,bx or any U want
				int temp=reg.getMemory().getMemContent(regCode);
				int  diff=temp-1;
				_mov(reg.getMemory(), regCode,  diff);
				// actual moving data to mem with his memory pointer at default then incrementing it
				_mov(mem, mem.getMemoryPointer(),  diff);
				mem.incMemoryPointer();
			}
			else
			{
				showError();
			}
		}
	} while (true);
}
void Instructions::compare(String range ,String addr)
{
	decodeRange(range);
	address=Math::convertHexaToInt(addr);
	const int add1=start;
	const int add2=address;
	for (int i=start;i<=end;i++)
	{
		if (mem.getMemContent(add1) != mem.getMemContent(add2))
		{
			mem.printMemoryLocation(add1);
			cout<<"\t";
			cout<<mem.getMemContent(add1);
			cout<<"\t";
			cout<<mem.getMemContent(add2);
			cout<<"\t";
			mem.printMemoryLocation(add2);
			cout<<"\n";
		}
	}
}
void Instructions::decodeDump(String& str)
{
	// wanana decode ager or space all hoto agr koi invalid char ho to ?
	if (str.isEmpty())
	{
		start = mem.getMemoryPointer();
		end = start + 160;
		return;
	}

	int i = 0;
	String test;
	int startTemp = 0, endTemp = 0;
	for (; str.at(i) != ' ' && str.at(i) != '\0'; i++)
	{

		test.push_back(str.at(i));
	}
	startTemp = Math::convertHexaToInt(test);
	// this means that keh abhi string nahi milo to ham remove krte hai 
    // ya ham nexr number ke start pata krte hain 

	if (str.at(i) != '\0')
	{
		while (str.at(i) == ' ')
			i++;
	}
	test.reSize(0);
	for (; str.at(i) != ' ' && str.at(i) != '\0'; i++)
	{
		test.push_back(str.at(i));
	}
	endTemp = Math::convertHexaToInt(test);
	if (endTemp == 0)
	{
		endTemp = startTemp + 160;
	}
	if (endTemp < startTemp)
	{
		showError();
		return;
	}
	// dimag thah   what to do 
	start = startTemp;
	end = endTemp;
}
void Instructions::dump()
{
	String test;
	Array arr(16);
	cout << "\nPress Enter If Want to start from current memory Pointer else:  ";
	cout << "\nEnter the range: ";
	test.input();
	cout<<"\n";
	test.makeUpper();
	decodeDump(test);
	int i = start;
	int beforeMemory = mem.getMemoryPointer();
	mem.setMemoryPointer(start);
	for ( ; i+16 <= end;)
	{
		mem.printMemoryLocation();
		cout << "    ";
		for (int j = 0; j < 16; j++, i++)
		{
			cout << "  " << setw(2) << setfill('0') <<(mem.getMemContent(i));
			arr.getSet(j) = mem.getMemContent(i);
			mem.incMemoryPointer();
		}
		cout << "\t";
		for (int j = 0; j < 16; j++)
		{
			int content=arr.getSet(j);
			if (content > 31 && content < 127)
				cout << (char)arr.getSet(j)<<" ";
			else
				cout << ". ";
		}
		cout << "\n";

	}
	if (i < end)
	{
		mem.printMemoryLocation();
		cout << "    ";
		int j = 0;
		for (;i<= end; j++,i++)
		{
			arr.getSet(j) = mem.getMemContent(i);
			cout << "  " << setw(2) << setfill('0') << mem.getMemContent(i);
			mem.incMemoryPointer();
		}
		for (int k = 0; k < j; k++)
		{
			cout << (char)arr.getSet(k);
		}
	}
	mem.setMemoryPointer(beforeMemory);
}
bool Instructions::decodeEnter(String& str)
{
	String test;
	int i = 0;
	while (i < 4)
	{
		test.push_back(str.at(i));
		i++;
	}
	// now to find that address
	address = Math::convertHexaToInt(test);
	if (address >= 0 && address <= 65535)
		return true;
	return false;
}
void Instructions::enter()
{
	String test;
	Array arr(16);
	cout << "\nEnter the Address: ";
	test.input();
	test.makeUpper();
	test.trimLeft();
	if (!decodeEnter(test))
	{
		showError();
		return;
	}
	int temp=mem.getMemoryPointer();
	mem.setMemoryPointer(address);
	mem.printMemoryLocation();
	cout<<"\t";
	cout<<mem.getMemContent(temp)<<'.';
	// following will enter the temp new data to fill
	String te;
	te.input();
	te.makeUpper();
	const short num=Math::convertHexaToInt(te);
	mem.getMemContent(address)=num;
	mem.setMemoryPointer(temp);
	cin.ignore();
}
bool Instructions::decodeRange(String & str)
{
	if (str.getLength()<9)
		return false;
	String test;
	int i=0;
	for (;i<4;i++)
	{
		test.push_back(str.at(i));
	}
	start=Math::convertHexaToInt(test);
	test.reSize(0);
	for (;str.at(i)!='\0';i++)
	{
		test.push_back(str.at(i));
	}
	test.makeUpper();
	test.trimLeft();
	end=Math::convertHexaToInt(test);
	mem.setMemoryPointer(start);
	return start<end?true:false;
}
void Instructions::fill()
{
	cout<<"\nEnter the Range:";
	String test;
	test.input();
	test.makeUpper();
	test.trimLeft();
	if (!decodeRange(test))
		return;
	cout<<"Enter the Value you Want to Fill : ";
	test.reSize(0);
	test.input();
	number=Math::convertHexaToInt(test);
	if (number>0 && number<=256)
	{
		for (int j = start; j <=end ; j++)
		{
			_mov(mem,j,number);

		}
	}
}
void Instructions::go()
{
	// trace function will be called
}
void Instructions::hex(String & str)
{
	decodeRange(str);
	int sum=start+end;
	int diff=start-end;
	const int MAX_HEXA=Math::convertHexaToInt(str);
	diff=abs(diff);
	Math::convertTOHexa(sum).display();
	cout<<" ";
	Math::convertTOHexa(diff).display();
	cout<<"\n";
}
void Instructions::input()
{
	// as making pseudo debugger so this functionality of communicating with hardware isn't supported yet
	cout << "\nData received from Specified port successfully.\n";
}
void Instructions::load()
{
	// what we want to do here ?
	// loading the file from memory  before this save krany ka method?
	saverFile.open(_file_name.getCharOfString(),ios::in);
	int val;
	for (int i = 0; i < 65535; i++)
	{
			saverFile >> val;
	}
	saverFile.close();
}
void Instructions::move(String & range_string,String & address_string)
{
	decodeRange(range_string);
	int start_temp=Math::convertHexaToInt(address_string);
	for (int i =start,j=0; i <end ; i++,j++)
	{
		mem.getMemContent(start_temp+j)=mem.getMemContent(i);
	}
	mem.setMemoryPointer(end);
}
void Instructions::name()
{
	cout<<"Enter the File name: ";
	_file_name.input();
	_file_name.trimLeft();
	_file_name.concatEqual(".txt");
}
void Instructions::output()
{
	// as making pseudo debugger so this functionality of communicating with hardware isn't supported yet
	cout << "\nData sent to Specified port successfully.\n";
}
void Instructions::proceed()
{
	// for now proceed and trace will work as same
}
void Instructions::quit()
{
	cout<<"\nExisting the Program...";
	exit(0);
}
bool Instructions::decode_Reg(String & str) {
	String s;
	for (int j = 0; j < 2; j++)
	{
		s.push_back(str.at(j));
	}
	if (s.compare("AX") == EQUAL || s.compare("BX") == EQUAL || s.compare("CX") == EQUAL || s.compare("DX") == EQUAL|| s.compare("IP") == EQUAL)
	{
		if (s.compare("AX") == EQUAL)
		{
			regCode = 1;
		}
		else if (s.compare("BX") == EQUAL)
		{
			regCode = 2;
		}
		else  if (s.compare("CX") == EQUAL)
		{
			regCode = 3;
		}
		else if (s.compare("DX") == EQUAL)
		{
			regCode = 4;
		}
		else if (s.compare("IP") == EQUAL) {
			regCode = 5;
		}
	}
	else {
		cout<<"Currently Not Available \n";
		return false;
	}
	return true;
}
void Instructions::register1(String & str)
{
	if(!str.isEmpty() && !decode_Reg(str) )
		return;
	String test;
	if (str.isEmpty()) {
		int current_Ip = mem.getMemContent(start);
		test=Math::convertTOHexa(current_Ip);
		trace(test);
	}
	if (regCode==1) {
		cout<<"AX: \n";
		test.input();
		test.makeUpper();
		test.trimLeft();
		const int num=Math::convertHexaToInt(test);
		_mov(reg.getMemory(),regCode-1,num);
	}
	else if (regCode==2) {
		cout<<"BX: \n";
		test.input();
		test.makeUpper();
		test.trimLeft();
		int num=Math::convertHexaToInt(test);
		_mov(reg.getMemory(),regCode-1,num);	}
	else if (regCode==3) {
		cout<<"CX: \n";
		test.input();
		test.makeUpper();
		test.trimLeft();
		int num=Math::convertHexaToInt(test);
		_mov(reg.getMemory(),regCode-1,num);
	}
	else if (regCode==4) {
		cout<<"DX: \n";
		test.input();
		test.makeUpper();
		test.trimLeft();
		int num=Math::convertHexaToInt(test);
		_mov(reg.getMemory(),regCode-1,num);
	} else if (regCode==5) {
		cout<<"IP: \n";
		test.input();
		test.makeUpper();
		test.trimLeft();
		int num=Math::convertHexaToInt(test);
		_mov(reg.getMemory(),regCode-1,num);
	}
}
void Instructions::search(String range, int val)
{
	// what does this command do
	// If found, DEBUG displays the matching address(es).
	decodeRange(range);
	// just want to print  the addresses with the same content
	const int tempMemPtr=mem.getMemoryPointer();
	mem.setMemoryPointer(start);
	for (int i=start; i<end; i++)
	{
		if (mem.getMemContent(i)==val)
		{
			mem.printMemoryLocation();
			cout<<"\n";
		}
		mem.incMemoryPointer();
	}
	mem.setMemoryPointer(tempMemPtr);
}
void Instructions::trace(String & index_string)
{
	index_string.trimLeft();
	index_string.makeUpper();
	address=Math::convertHexaToInt(index_string);
	if (!index_string.isEmpty())
		mem.setMemoryPointer(address);
	// register showing may not be correct as it will require tokenization

	// now printing registers
	number=mem.getMemContent(address);

	reg.setRegister(1,number);
	reg.setRegister(2,number);
	reg.setRegister(3,number);
	reg.setRegister(4,number);
	cout<<"Ax= ";
	Math::convertTOHexa(reg.getAx()).display();
	cout<<"  "<<"BX: ";
	Math::convertTOHexa(reg.getBx()).display();
	cout<<"  "<<"CX: ";
	Math::convertTOHexa(reg.getCx()).display();
	cout<<"  DX: ";
	Math::convertTOHexa(reg.getDx()).display();
	cout<<"  SP: 00FD  BP: 0000 SI:0000 DI:0000 \n";
	cout<<"IP: ";
	Math::convertTOHexa(mem.getMemoryPointer()).display();
	cout<<"\n";
	mem.printMemoryLocation(mem.getMemoryPointer());
	cout<<"\t";
	(*mem.extract_instr_string(address)).display();
	cout<<"\n";
	mem.incMemoryPointer();
}
void Instructions::unassemble(String & str)
{
	// this function firstly decodes the string for extracting range then it will get the instruction string from memory and print respectively
	str.trimLeft();
	str.makeUpper();
	decodeRange(str);
	for (int i=start; i<end; i++)
	{
		mem.printMemoryLocation(i);
		cout<<"\t";
		(*mem.extract_instr_string(i)).display();
		cout<<"\n";
	}
}
void Instructions::write()
{
	// it will write the memory diagram full heap arrays which are required to be saved
	// now for jst Mem array
	// following opens the file in that output mode
	saverFile.open(_file_name.getCharOfString(),ios::out);
	for (int i = 0; i< 65535; i++)
	{
		saverFile<<mem.getMemContent(i);
		saverFile<<" ";
	}
	saverFile.close();
}
void Instructions::showError()
{
	cout << "\t\t^\n";
	cout << "\t\tError\n";
}
void Instructions::showFeatureUnavailable()
{
	cout << "\t\t^\n";
	cout << "\t\tThis feature is UNAVAILABLE\n";
}
void Instructions::_mov(Memory& me,int index, int val)
{
	me.getMemContent(index) = val;
}