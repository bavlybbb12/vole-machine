#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include<algorithm>
#include <stdexcept>
using namespace std;

class ALU {
private:
    set<string> opCodes;

public:
    ALU();
    int hexToDec(string hex);
    string decToHex(int dec);
    bool validOP(string op);
    float hexToFloat(string hex);
    string floatToHex(float value);
    string addTwosComplement(string a, string b);
    string addFloating(string a, string b);
    string bitOr(string a, string b);
    string bitAnd(string a, string b);
    string bitXor(string a, string b);
    string rotateRight(string value, int count);
};

#endif