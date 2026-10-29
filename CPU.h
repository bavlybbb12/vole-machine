#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>


using namespace std;


#include "Register.h"
#include "ALU.h"
#include "Memory.h"

class CPU {
private:
    Register reg;
    ALU alu;
    int pc;
    string IR;
    bool halted;
    vector<string> screen;

public:
    CPU();
    void Fetch(Memory& mem);
    void Execute(Memory& mem);
    void reset();
    bool isValidInstruction(string instruction);
    bool isHalted();
    int getPC();
    void setPC(int address);
    string getIR();
    Register& getRegister();
    vector<string> getScreen();
};

#endif
