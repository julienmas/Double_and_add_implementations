//#pragma once
#include <iostream>
#include <cstring>

using namespace std;

const int N_BITS = 4; //8;
const int DIGIT_MAX = 16; // 2⁸ = 256
const int BIGINT_LENGTH = 448/N_BITS; // 56*8 = 448 bits

class BigInt
{
    
public:
    BigInt();
    //BigInt(unsigned char m[BIGINT_LENGTH]){ memcpy(n,m, sizeof(m));}
    BigInt(string &);

    void printBigInt(int) const;

    friend BigInt &operator+=(BigInt &, const BigInt &); // & to do not copy the object
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);

private:
    unsigned char n[BIGINT_LENGTH]; // unsigned char : 2 bytes (0 to 255 possible)
};


BigInt::BigInt()
{
    unsigned char m[BIGINT_LENGTH]={};
    memcpy(n,m,sizeof(m));
}


BigInt::BigInt(string & s)
{
    for (int i=0; i<BIGINT_LENGTH; i++)
    {
        switch (s[i])
        {
        case '0':
            n[i] = 0;
            break;
        case '1':
            n[i] = 1;
            break;
        case '2':
            n[i] = 2;
            break;
        case '3':
            n[i] = 3;
            break;
        case '4':
            n[i] = 4;
            break;
        case '5':
            n[i] = 5;
            break;
        case '6':
            n[i] = 6;
            break;
        case '7':
            n[i] = 7;
            break;
        case '8':
            n[i] = 8;
            break;
        case '9':
            n[i] = 9;
            break;
        case 'a':
            n[i] = 10;
            break;
        case 'b':
            n[i] = 11;
            break;
        case 'c':
            n[i] = 12;
            break;
        case 'd':
            n[i] = 13;
            break;
        case 'e':
            n[i] = 14;
            break;
        case 'f':
            n[i] = 15;
            break;
        default:
            break;
        }
    
    }
}

void BigInt::printBigInt(int base=16) const
{
    for (int i = 0; i< BIGINT_LENGTH; i++)
    {
        switch (n[i])
        {
        case 0:
            cout<<'0';
            break;
        case 1:
            cout<<'1';
            break;
        case 2:
            cout<<'2';
            break;
        case 3:
            cout<<'3';
            break;
        case 4:
            cout<<'4';
            break;
        case 5:
            cout<<'5';
            break;
        case 6:
            cout<<'6';
            break;
        case 7:
            cout<<'7';
            break;
        case 8:
            cout<<'8';
            break;
        case 9:
            cout<<'9';
            break;
        case 10:
            cout<<'a';
            break;
        case 11:
            cout<<'b';
            break;
        case 12:
            cout<<'c';
            break;
        case 13:
            cout<<'d';
            break;
        case 14:
            cout<<'e';
            break;
        case 15:
            cout<<'f';
            break;
        default:
            break;
        }
    }
}

BigInt &operator+=(BigInt &a,const BigInt& b)
{
    unsigned char carry = 0;
    for (int i = BIGINT_LENGTH-1; i>= 0; i--)
    {
        a.n[i] += b.n[i]+carry;
        carry = 0;
        if (a.n[i] > DIGIT_MAX)
        {
            a.n[i] -= DIGIT_MAX;
            carry = 1;
        }
    }
    return a;
}


BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

BigInt &operator-=(BigInt &a, const BigInt &b)
{
    unsigned char carry = 0;
    for (int i = BIGINT_LENGTH-1; i>= 0; i--)
    {
        if (a.n[i] >= b.n[i]+carry)
        {
            a.n[i] -= b.n[i]+carry;
            carry = 0;
        }
        else
        {
            a.n[i] = DIGIT_MAX - (b.n[i]+carry - a.n[i]);
            carry = -1;
        }
    }
    return a;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}


BigInt &operator*=(BigInt &a, const BigInt &b)
{
    unsigned char carry = 0;
    for (int i = BIGINT_LENGTH-1; i>= 0; i--)
    {
        a.n[i] += b.n[i]+carry;
        carry = 0;
        if (a.n[i] > DIGIT_MAX)
        {
            a.n[i] -= DIGIT_MAX;
            carry = 1;
        }
    }
    return a;
}


BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}

int main()
{
    string x = "0D9029AD2C7E5CF4340823B2A87DC68C9E4CE3174C1E6EFDEE12C07D";
    string y = "58AA56F772C0726F24C6B89E4ECDAC24354B9E99CAA3F6D3761402CD";


    BigInt a(x);
    BigInt b(y);

    BigInt c = a + a; // DOES NOT WORK

    c.printBigInt();

    return 0;
}