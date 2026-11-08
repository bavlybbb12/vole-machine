#include "Memory.h"

#include <cctype>
#include <stdexcept>

Memory::Memory() : memory(SIZE, "00") {}

std::string Memory::get(int address) const {
    if (address < 0 || address >= SIZE)
        throw std::out_of_range("Memory address out of range: " + std::to_string(address));
    return memory[address];
}

void Memory::set(int address, const std::string& value) {
    if (address < 0 || address >= SIZE)
        throw std::out_of_range("Memory address out of range: " + std::to_string(address));

    if (value.size() != 2 ||
        !std::isxdigit(static_cast<unsigned char>(value[0])) ||
        !std::isxdigit(static_cast<unsigned char>(value[1])))
        throw std::invalid_argument("Memory value must be 2 hex digits: " + value);

    std::string v = value;
    for (char& c : v) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    memory[address] = v;
}

void Memory::clear() {
    memory.assign(SIZE, "00");
}
