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
    unsigned char n[BIGINT_LENGTH]; // unsigned char : 2 bytes (0 to 255 possible)

    BigInt();
    BigInt(unsigned char m[BIGINT_LENGTH]){ memcpy(n,m, sizeof(n));}
    BigInt(string &);

    //unsigned char * getn() const {   return n;}
    void printBigInt(int) const;

    friend BigInt &operator+=(BigInt &, const BigInt &); // & to do not copy the object
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);

//private:
};


BigInt::BigInt()
{
    unsigned char m[BIGINT_LENGTH]={};
    memcpy(n,m,sizeof(m));
}


BigInt::BigInt(string & s)
{
    int l = s.length();
    for (int i=0; i<BIGINT_LENGTH; i++)
    {
        n[i]=0;
    }
    for (int i=BIGINT_LENGTH-l; i<BIGINT_LENGTH; i++)
    {
        switch (s[i-BIGINT_LENGTH+l])
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
        case 'A':
            n[i] = 10;
            break;
        case 'b':
        case 'B':
            n[i] = 11;
            break;
        case 'c':
        case 'C':
            n[i] = 12;
            break;
        case 'd':
        case 'D':
            n[i] = 13;
            break;
        case 'e':
        case 'E':
            n[i] = 14;
            break;
        case 'f':
        case 'F':
            n[i] = 15;
            break;
        default:
            cout << "Error in BigInt init\n";
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
        if (a.n[i] >= DIGIT_MAX)
        {
            a.n[i] &= DIGIT_MAX - 1; // masque bit à bit plus opti que la soustraction
            //a.n[i] -= DIGIT_MAX;
            carry = 1;
        }
    }
    return a;
}


BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt temp = a;
    temp += b;
    return temp;
}

BigInt &operator-=(BigInt &a, BigInt const &b)
{
    /*unsigned char m[BIGINT_LENGTH];
    
    //memcpy(m, b.getn(), sizeof(m));
    memcpy(m, b.n, sizeof(b.n));
    for (int i=0; i< BIGINT_LENGTH; i++)
    {
        m[i] = ~m[i];
    }
    BigInt bCompl(m);
    string o = "1";
    BigInt one(o);
    BigInt r;
    r = a + bCompl + one;
    return r;*/

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
            a.n[i] += DIGIT_MAX;
            a.n[i] -= b.n[i]+carry;
            carry = 1;
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
    string z = "58";
    string u = "d";
    string t = "fffffffffffffffffffffffffffffffffffffffffffffffffffffeff";

    BigInt a(x);
    //a.printBigInt();
    cout << "\n";

    BigInt b(y);

    BigInt c;
    BigInt d(z);
    BigInt e(u);
    c = b-a;
    c.printBigInt();

    //faire le add avec les overflow : convertir les types ne coute rien
    // soustraction utilisant -b = b barre +1 :~b= b barre


    cout << "\n";
    return 0;
}