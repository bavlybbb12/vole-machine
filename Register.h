#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

class Register {
private:
    vector<string> registers;

public:
    Register();
    string get(int index);
    void set(int index, string value);
    void clear();
};

#endif
