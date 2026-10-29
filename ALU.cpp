#include "ALU.h"

ALU::ALU()
{
    opCodes = {"1", "2", "3", "4", "5", "6", "B", "C"};
}

int ALU::hexToDec(string hex)
{
    int ans = 0;
    int exp = 0;
    for(int i= hex.size()-1;i>=0;i--)
    {
        int n= 0;
        if(isdigit(hex[i]))
            n=hex[i]-'0';
        else
            n = 10 + (hex[i]-'A');
        int twoExp = exp*4; //16 = 2^4
        ans+=((1<<twoExp)*n);
        exp++;
    }
    return ans;
}

string ALU::decToHex(int dec)
{
    if(dec == 0)
        return "00";

    string ans = "";
    int temp = dec;

    while(temp)
    {
        int dig = temp % 16;

        if(dig < 10)
            ans += (dig + '0');
        else
            ans += char(dig - 10 + 'A');

        temp /= 16;
    }

    reverse(ans.begin(), ans.end());

    if(ans.size() == 1)
        ans = '0' + ans;

    return ans;
}

bool ALU::validOP(string op)
{
    return opCodes.count(op);
}

string ALU::bitOr(string a, string b)
{
    int res = hexToDec(a)|hexToDec(b);
    return decToHex(res);
}

string ALU::bitAnd(string a, string b)
{
    int res = hexToDec(a)&hexToDec(b);
    return decToHex(res);
}

string ALU::bitXor(string a, string b)
{
    int res = hexToDec(a)^hexToDec(b);
    return decToHex(res);
}

string ALU::rotateRight(string value, int count)
{
    int res = hexToDec(value)>>count;
    return decToHex(res);
}
