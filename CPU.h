#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include "Register.h"
#include "ALU.h"
#include "Memory.h"

class CPU {
private:
    
    Register reg;
    ALU alu;
    int pc;
    std::string IR;
    bool halted;
    std::vector<std::string> screen;


public:
    
    CPU() ;
    
    void Fetch(Memory& mem) ;
    
    void Execute(Memory& mem);
    
    void reset();
    
    bool isValidInstruction(std::string instruction);
    
    bool isHalted();

    int getPC();

    void setPC(int address);
    
    std::string getIR();

    Register& getRegister();
    
    std::vector<std::string> getScreen();

};

#endif