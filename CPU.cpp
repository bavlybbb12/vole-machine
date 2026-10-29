#include "CPU.h"
using namespace std;

CPU::CPU() {}

void CPU::Fetch(Memory& mem) {}

void CPU::Execute(Memory& mem) {}

void CPU::reset() {}

bool CPU::isValidInstruction(std::string instruction) {}

bool CPU::isHalted() {}

int CPU::getPC() {}

void CPU::setPC(int address) {}

string CPU::getIR() {}

Register& CPU::getRegister() {}
    
vector<string> CPU::getScreen() {}