#ifndef UI_H
#define UI_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <cmath>


using namespace std;

#include "VoleMachine.h"

class UI {
private:
    VoleMachine machine;

public:
    void showMenu();
    void takeInput();
    void showMemory();
    void showRegisters();
    void showState();
    void displayScreen();
    void modifyRegister();
    void modifyMemory();
};

#endif
