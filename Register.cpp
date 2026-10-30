#include "Register.h"

Register::Register()
{
    registers.resize(16, "00");
}

string Register::get(int index)
{
    if (index >= 0 && index < registers.size())
    {
        return registers[index];
    }
    return "00";
}

void Register::set(int index, string value)
{
    if (index >= 0 && index < registers.size())
    {
        registers[index] = value;
    }
}

void Register::clear()
{
    for (int i = 0; i < registers.size(); ++i)
    {
        registers[i] = "00";
    }
}
