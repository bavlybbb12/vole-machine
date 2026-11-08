#include "VoleMachine.h"

#include <cctype>
#include <fstream>
#include <stdexcept>

namespace {
    const long INSTRUCTION_LIMIT = 100000;   // stops an infinite loop in run()

    std::string trim(const std::string& s) {
        size_t first = 0;
        while (first < s.size() && std::isspace(static_cast<unsigned char>(s[first]))) first++;
        size_t last = s.size();
        while (last > first && std::isspace(static_cast<unsigned char>(s[last - 1]))) last--;
        return s.substr(first, last - first);
    }

    bool isHex(char c) {
        return std::isxdigit(static_cast<unsigned char>(c)) != 0;
    }
}

VoleMachine::VoleMachine() {}

void VoleMachine::LoadFile(const std::string& fileName, int startAddress) {
    if (startAddress < 0 || startAddress >= Memory::SIZE)
        throw std::out_of_range("Start address is outside memory.");
    if (startAddress % 2 != 0)
        throw std::invalid_argument("Start address must be even.");

    std::ifstream in(fileName);
    if (!in) throw std::runtime_error("Cannot open file: " + fileName);

    // Pass 1: read and validate every instruction before touching the machine.
    std::vector<std::string> instructions;
    std::string line;
    int lineNumber = 0;
    while (std::getline(in, line)) {
        lineNumber++;
        size_t comment = line.find(';');
        if (comment != std::string::npos) line = line.substr(0, comment);
        line = trim(line);
        if (line.empty()) continue;

        std::string where = "Line " + std::to_string(lineNumber) + ": ";
        if (line.size() < 4)
            throw std::invalid_argument(where + "an instruction needs 4 hex digits.");

        std::string instruction = line.substr(0, 4);
        for (char& c : instruction) {
            if (!isHex(c))
                throw std::invalid_argument(where + "'" + instruction + "' is not hexadecimal.");
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        if (!cpu.isValidInstruction(instruction))
            throw std::invalid_argument(where + "invalid instruction " + instruction + ".");

        instructions.push_back(instruction);
    }

    if (instructions.empty())
        throw std::invalid_argument("The file contains no instructions.");
    if (startAddress + static_cast<int>(instructions.size()) * 2 > Memory::SIZE)
        throw std::out_of_range("The program does not fit in memory.");

    // Pass 2: everything is valid, so now change the machine.
    mem.clear();
    cpu.reset();
    int address = startAddress;
    for (const std::string& ins : instructions) {
        mem.set(address, ins.substr(0, 2));
        mem.set(address + 1, ins.substr(2, 2));
        address += 2;
    }
    cpu.setPC(startAddress);
}

void VoleMachine::step() {
    if (cpu.isHalted()) return;
    cpu.Fetch(mem);
    cpu.Execute(mem);
}

void VoleMachine::run() {
    long count = 0;
    while (!cpu.isHalted()) {
        if (count++ >= INSTRUCTION_LIMIT)
            throw std::runtime_error("Instruction limit reached (possible infinite loop).");
        step();
    }
}

bool VoleMachine::isHalted() {
    return cpu.isHalted();
}

void VoleMachine::reset() {
    cpu.reset();
    mem.clear();
}

std::vector<std::string> VoleMachine::getScreen() {
    return cpu.getScreen();
}
