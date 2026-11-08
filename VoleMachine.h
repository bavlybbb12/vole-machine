#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include <string>
#include <vector>

#include "CPU.h"
#include "Memory.h"

// Owns the CPU and Memory, loads programs and controls execution.
// Errors are reported by throwing std::exception subclasses; the UI catches them.
//
// Needs these from the CPU class (see the final design):
//   void Fetch(Memory&), void Execute(Memory&), void reset(), void setPC(int),
//   bool isValidInstruction(const std::string&), bool isHalted() const,
//   std::vector<std::string> getScreen() const
class VoleMachine {
public:
    VoleMachine();

    // Validates the whole file first; only if everything is valid is memory
    // cleared, the CPU reset, the program written and the PC set.
    void LoadFile(const std::string& fileName, int startAddress = 0);

    void run();        // step() until the machine halts
    void step();       // one fetch + execute (does nothing if already halted)
    bool isHalted();
    void reset();      // cpu.reset() and mem.clear()

    CPU& getCPU() { return cpu; }
    Memory& getMemory() { return mem; }
    std::vector<std::string> getScreen();

private:
    CPU cpu;
    Memory mem;
};

#endif
