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

float ALU::hexToFloat(string hex) {
    int v = hexToDec(hex) & 0xFF; // maximum 255 

    if (v == 0) return 0.0f;

    int sign     = (v >> 7) & 1;
    int exponent = (v >> 4) & 0x7;
    int mantissa = v & 0xF;

    float fraction = mantissa / 16.0f;
    float value = fraction * pow(2, exponent - 4);

    return sign ? -value : value;
}

string ALU::floatToHex(float value) {
    if (value == 0) return "00";

    int sign = 0;
    if (value < 0) {
        sign = 1;
        value = -value;
    }

    if (value > 7.5f || value < 1.0f / 32) //exp to 7 , fraction 0.5 to 1 -> min =0.03125 , max = 7.5
        throw runtime_error("Floating point overflow/underflow");

    
    int e = -4; // bias
    while (value / pow(2, e) >= 1)
        e++;

    float fraction = value / pow(2, e);
    int mantissa = (int)(fraction * 16);

    int result = (sign << 7) | ((e + 4) << 4) | mantissa;
    return decToHex(result);
}

string ALU::addTwosComplement(string a, string b)
{
    int ca = hexToDec(a) , cb = hexToDec(b);
    return decToHex((ca+cb)&0xFF);
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
