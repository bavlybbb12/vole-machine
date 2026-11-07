#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H




#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <stdexcept>

using namespace std;
#include "CPU.h"
#include "Memory.h"

class VoleMachine {
private:
    CPU cpu;
    Memory mem;

public:
    void LoadFile(string fileName, int startAddress = 0);
    void run();
    void step();
    bool isHalted();
    void reset();
    CPU& getCPU();
    Memory& getMemory();
    vector<string> getScreen();
};

#endif