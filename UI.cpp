#include "UI.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <cctype>
#include <algorithm>

void UI::showMenu()
{
    system("cls");
    cout << "\n=========================================\n";
    cout << "       VOLE MACHINE SIMULATOR           \n";
    cout << "=========================================\n";
    cout << "1. Load Program from File\n";
    cout << "2. Run Program Continuously\n";
    cout << "3. Execute Single Step\n";
    cout << "4. Show Registers\n";
    cout << "5. Show Memory\n";
    cout << "6. Show Full Machine State\n";
    cout << "7. Modify Register\n";
    cout << "8. Modify Memory\n";
    cout << "9. Reset Machine\n";
    cout << "0. Exit\n";
    cout << "=========================================\n";
}

void UI::takeInput()
{
    int choice = -1;
    while (true) {
        showMenu();
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string fileName;
                string addrInput;
                int startAddr = 0;

                cout << "Enter file name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, fileName);

                cout << "Enter start address in hex (e.g., 00): ";
                cin >> addrInput;

                try {
                    size_t idx = 0;
                    startAddr = stoi(addrInput, &idx, 16);
                    if (idx != addrInput.length() || startAddr < 0 || startAddr > 255 || (startAddr % 2 != 0)) {
                        cout << "Error: Start address must be an even hex value between 00 and FF (0-255).\n";
                        break;
                    }

                    machine.LoadFile(fileName, startAddr);
                    cout << "Program loaded successfully and PC set to start address!\n";
                } catch (const exception& e) {
                    cout << "Error loading file: " << e.what() << "\n";
                }
                break;
            }
            case 2:
                machine.run();
                cout << "Program execution completed.\n";
                showState();
                break;
            case 3:
                if (machine.isHalted()) {
                    cout << "Machine is already halted.\n";
                } else {
                    machine.step();
                    cout << "Executed single step.\n";
                    showState();
                    cout << "Press Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
                break;
            case 4:
                showRegisters();
                break;
            case 5:
                showMemory();
                break;
            case 6:
                showState();
                break;
            case 7:
                modifyRegister();
                break;
            case 8:
                modifyMemory();
                break;
            case 9:
                machine.reset();
                cout << "Machine reset to initial state.\n";
                break;
            case 0:
                cout << "Exiting simulator. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        // pause so the output can be read before the menu is shown again
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPress Enter to return to the menu...";
        cin.get();
    }
}

void UI::showRegisters()
{
    ios_base::fmtflags f(cout.flags());
    char oldFill = cout.fill();

    cout << "\n--- Registers State ---\n";
    Register& reg = machine.getCPU().getRegister();
    for (int i = 0; i < 16; ++i) {
        cout << "R" << hex << uppercase << i << ": "
             << setw(2) << setfill('0') << reg.get(i) << "   ";
        if ((i + 1) % 4 == 0) cout << "\n";
    }

    cout.flags(f);
    cout.fill(oldFill);
}

void UI::showMemory()
{
    ios_base::fmtflags f(cout.flags());
    char oldFill = cout.fill();

    cout << "\n----------------------- Memory State -----------------------\n";
    cout << "     ";
    for (int c = 0; c < 16; ++c) {
        cout << hex << uppercase << setw(2) << setfill('0') << c << " ";
    }
    cout << "\n";

    Memory& mem = machine.getMemory();
    for (int r = 0; r < 16; ++r) {
        cout << hex << uppercase << setw(2) << setfill('0') << (r * 16) << ": ";
        for (int c = 0; c < 16; ++c) {
            int address = r * 16 + c;
            cout << setw(2) << setfill('0') << mem.get(address) << " ";
        }
        cout << "\n";
    }
    cout << "------------------------------------------------------------\n";

    cout.flags(f);
    cout.fill(oldFill);
}

void UI::showState()
{
    ios_base::fmtflags f(cout.flags());
    char oldFill = cout.fill();

    cout << "\n=========================================\n";
    cout << "           MACHINE FULL STATE            \n";
    cout << "=========================================\n";
    cout << "PC: " << hex << uppercase << setw(2) << setfill('0') << machine.getCPU().getPC() << "\n";
    cout << "IR: " << setw(4) << setfill('0') << machine.getCPU().getIR() << "\n";
    cout << "Halted: " << (machine.isHalted() ? "Yes" : "No") << "\n";

    showRegisters();
    showMemory();
    displayScreen();

    cout << "=========================================\n";

    cout.flags(f);
    cout.fill(oldFill);
}

void UI::displayScreen()
{
    vector<string> screen = machine.getScreen();
    if (!screen.empty()) {
        cout << "\n--- Screen Output ---\n";
        for (const string& line : screen) {
            cout << line << "\n";
        }
    }
}

void UI::modifyRegister()
{
    string inputIndex, value;
    cout << "Enter register index (0-F in hex): ";
    cin >> inputIndex;

    int index;
    try {
        size_t idx = 0;
        index = stoi(inputIndex, &idx, 16);
        if (idx != inputIndex.length()) {
            cout << "Invalid register index format!\n";
            return;
        }
    } catch (...) {
        cout << "Invalid register index format!\n";
        return;
    }

    if (index < 0 || index > 15) {
        cout << "Error: Register index must be between 0 and 15 (0-F).\n";
        return;
    }

    cout << "Enter new 2-hex-digit value: ";
    cin >> value;

    if (value.length() != 2 || !isxdigit(static_cast<unsigned char>(value[0])) || !isxdigit(static_cast<unsigned char>(value[1]))) {
        cout << "Error: Value must be exactly 2 valid hex digits (e.g., A5).\n";
        return;
    }

    transform(value.begin(), value.end(), value.begin(), ::toupper);
    machine.getCPU().getRegister().set(index, value);
    cout << "Register updated successfully.\n";
}

void UI::modifyMemory()
{
    string inputAddr, value;
    cout << "Enter memory address in hex (00-FF): ";
    cin >> inputAddr;

    int address;
    try {
        size_t idx = 0;
        address = stoi(inputAddr, &idx, 16);
        if (idx != inputAddr.length()) {
            cout << "Invalid memory address format!\n";
            return;
        }
    } catch (...) {
        cout << "Invalid memory address format!\n";
        return;
    }

    if (address < 0 || address > 255) {
        cout << "Error: Memory address must be between 0 and 255 (00-FF).\n";
        return;
    }

    cout << "Enter new 2-hex-digit value: ";
    cin >> value;

    if (value.length() != 2 || !isxdigit(static_cast<unsigned char>(value[0])) || !isxdigit(static_cast<unsigned char>(value[1]))) {
        cout << "Error: Value must be exactly 2 valid hex digits (e.g., 0F).\n";
        return;
    }

    transform(value.begin(), value.end(), value.begin(), ::toupper);
    machine.getMemory().set(address, value);
    cout << "Memory updated successfully.\n";
}