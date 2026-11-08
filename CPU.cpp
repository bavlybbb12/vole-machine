#include "CPU.h"
using namespace std;

CPU::CPU() { reset(); }

void CPU::Fetch(Memory& mem) {

    if (pc < 0 || pc + 1 > 255) {
        throw std::out_of_range("PC out of bounds");
    }

    IR = mem.get(pc);
    IR += mem.get(pc + 1);

    pc += 2;

}

void CPU::Execute(Memory& mem) {

    if ( isValidInstruction(IR) == false ) throw std::invalid_argument("Invalid instruction");

    switch (IR[0]) {

        case '1': {
            
            int registerIndex = IR[1] - '0';
            if (registerIndex > 9) registerIndex = IR[1] - 'A' + 10;
            string address = IR.substr(2, 2);
            reg.set(registerIndex, mem.get(alu.hexToDec(address)));
            break;
        
        }

        case '2': {
        
            int registerIndex = IR[1] - '0';
            if (registerIndex > 9) registerIndex = IR[1] - 'A' + 10;
            reg.set(registerIndex, IR.substr(2, 2));
            break;
        
        }

        case '3': {
        
            int registerIndex = IR[1] - '0';
            if (registerIndex > 9) registerIndex = IR[1] - 'A' + 10;
            string address = IR.substr(2, 2);
            int addressValue = alu.hexToDec(address);
            string value = reg.get(registerIndex);
            mem.set(addressValue, value);
            if (addressValue == 255) 
            {
                string line = "Hex: " + value + " , Dec: " + to_string(alu.hexToDec(value));
                screen.push_back(line);
            }
            break;
        
        }

        case '4': {
        
            int destinationIndex = IR[3] - '0';
            int sourceIndex = IR[2] - '0';
            if (destinationIndex > 9)
                destinationIndex = IR[3] - 'A' + 10;
            if (sourceIndex > 9)
                sourceIndex = IR[2] - 'A' + 10;
            reg.set(destinationIndex, reg.get(sourceIndex));
            break;
        
        }

        case '5': {
        
            int destinationIndex = IR[1] - '0';
            int firstIndex = IR[2] - '0';
            int secondIndex = IR[3] - '0';
            if (destinationIndex > 9) destinationIndex = IR[1] - 'A' + 10;
            if (firstIndex > 9) firstIndex = IR[2] - 'A' + 10;
            if (secondIndex > 9) secondIndex = IR[3] - 'A' + 10;
            reg.set(destinationIndex, alu.addTwosComplement(reg.get(firstIndex), reg.get(secondIndex)));
            break;
        
        }

        case '6': {
        
            int destinationIndex = IR[1] - '0';
            int firstIndex = IR[2] - '0';
            int secondIndex = IR[3] - '0';
            if (destinationIndex > 9) destinationIndex = IR[1] - 'A' + 10;
            if (firstIndex > 9) firstIndex = IR[2] - 'A' + 10;
            if (secondIndex > 9) secondIndex = IR[3] - 'A' + 10;
            reg.set(destinationIndex, alu.addFloating(reg.get(firstIndex), reg.get(secondIndex)));
            break;
        
        }

        case '7': {
        
            int destinationIndex = IR[1] - '0';
            int firstIndex = IR[2] - '0';
            int secondIndex = IR[3] - '0';
            if (destinationIndex > 9) destinationIndex = IR[1] - 'A' + 10;
            if (firstIndex > 9) firstIndex = IR[2] - 'A' + 10;
            if (secondIndex > 9) secondIndex = IR[3] - 'A' + 10;
            reg.set(destinationIndex, alu.bitOr(reg.get(firstIndex), reg.get(secondIndex)));
            break;
        
        }

        case '8': {
        
            int destinationIndex = IR[1] - '0';
            int firstIndex = IR[2] - '0';
            int secondIndex = IR[3] - '0';
            if (destinationIndex > 9) destinationIndex = IR[1] - 'A' + 10;
            if (firstIndex > 9) firstIndex = IR[2] - 'A' + 10;
            if (secondIndex > 9) secondIndex = IR[3] - 'A' + 10;
            reg.set(destinationIndex, alu.bitAnd(reg.get(firstIndex), reg.get(secondIndex)));
            break;
        
        }

        case '9': {
        
            int destinationIndex = IR[1] - '0';
            int firstIndex = IR[2] - '0';
            int secondIndex = IR[3] - '0';
            if (destinationIndex > 9) destinationIndex = IR[1] - 'A' + 10;
            if (firstIndex > 9) firstIndex = IR[2] - 'A' + 10;
            if (secondIndex > 9) secondIndex = IR[3] - 'A' + 10;
            reg.set(destinationIndex, alu.bitXor(reg.get(firstIndex), reg.get(secondIndex)));
            break;
        
        }

        case 'A': {
        
            int registerIndex = IR[1] - '0';
            if (registerIndex > 9)
                registerIndex = IR[1] - 'A' + 10;
            reg.set(registerIndex, alu.rotateRight(reg.get(registerIndex), alu.hexToDec(IR.substr(3, 1))));
            break;
        
        }

        case 'B': {
        
            int registerIndex = IR[1] - '0';
            if (registerIndex > 9)
                registerIndex = IR[1] - 'A' + 10;
            if (reg.get(registerIndex) == reg.get(0))
                pc = alu.hexToDec(IR.substr(2, 2));
        
                break;
        
            }

        case 'C': {
        
            halted = true;
            break;
        }

        default:
            throw std::invalid_argument("Invalid opcode");

    } 

}

void CPU::reset() {

    pc = 0;
    IR = "0000";
    halted = false;
    screen.clear();
    reg.clear();

}

bool CPU::isValidInstruction(std::string instruction) {

    if (instruction.length() != 4 ||
    instruction.find_first_not_of("0123456789ABCDEF")
    != std::string::npos) return false;

    char op = instruction[0];

    if (!alu.validOP(std::string(1, op))) return false;

    if (op == '4' && instruction[1] != '0') return false;
    if (op == 'A' && instruction[2] != '0') return false;
    if (op == 'C' && instruction != "C000") return false;

    return true;

}

bool CPU::isHalted() { return halted; }

int CPU::getPC() { return pc; }

void CPU::setPC(int address) { pc = address; }

string CPU::getIR() { return IR; }

Register& CPU::getRegister() { return reg; }
    
vector<string> CPU::getScreen() { return screen; }