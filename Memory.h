#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

class Memory {
private:
    vector<string> memory;

public:
    Memory();
    string get(int address);
    void set(int address, string value);
    void clear();
};

#endif