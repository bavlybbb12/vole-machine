#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

// Vole machine memory: 256 cells (addresses 00 - FF), each holding an 8-bit
// value stored as two uppercase hexadecimal digits (e.g. "3A").
// Plain storage only: it knows nothing about the screen.
class Memory {
public:
    static const int SIZE = 256;

    Memory();

    // Throw std::out_of_range if the address is outside 0..255.
    std::string get(int address) const;
    // Also throws std::invalid_argument if value is not exactly 2 hex digits.
    void set(int address, const std::string& value);
    void clear();   // every cell back to "00"

private:
    std::vector<std::string> memory;
};

#endif
