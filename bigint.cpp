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
    unsigned char d[BIGINT_LENGTH]; // digits. unsigned char : 2 bytes (0 to 255 possible)

    BigInt();
    BigInt(unsigned char m[BIGINT_LENGTH]){ memcpy(d,m, sizeof(d));}
    BigInt(string &);

    //unsigned char * getn() const {   return d;}
    void printBigInt(void) const;
    void shift(int n); // décalage vers la gauche (*base^n)

    friend BigInt &operator+=(BigInt &, const BigInt &); // & to do not copy the object
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend BigInt operator%(const BigInt &a, const BigInt &b);
    friend BigInt mod_add(const BigInt &, const BigInt &, const BigInt &); // modular addtion
    friend BigInt mod_sub(const BigInt &, const BigInt &, const BigInt &); // modular substraction

//private:
};


BigInt::BigInt()
{
    unsigned char m[BIGINT_LENGTH]={};
    memcpy(d,m,sizeof(m));
}


BigInt::BigInt(string & s)
{
    int l = s.length();
    for (int i=0; i<BIGINT_LENGTH; i++)
    {
        d[i]=0;
    }
    for (int i=BIGINT_LENGTH-l; i<BIGINT_LENGTH; i++)
    {
        switch (s[i-BIGINT_LENGTH+l])
        {
        case '0':
            d[i] = 0;
            break;
        case '1':
            d[i] = 1;
            break;
        case '2':
            d[i] = 2;
            break;
        case '3':
            d[i] = 3;
            break;
        case '4':
            d[i] = 4;
            break;
        case '5':
            d[i] = 5;
            break;
        case '6':
            d[i] = 6;
            break;
        case '7':
            d[i] = 7;
            break;
        case '8':
            d[i] = 8;
            break;
        case '9':
            d[i] = 9;
            break;
        case 'a':
        case 'A':
            d[i] = 10;
            break;
        case 'b':
        case 'B':
            d[i] = 11;
            break;
        case 'c':
        case 'C':
            d[i] = 12;
            break;
        case 'd':
        case 'D':
            d[i] = 13;
            break;
        case 'e':
        case 'E':
            d[i] = 14;
            break;
        case 'f':
        case 'F':
            d[i] = 15;
            break;
        default:
            cout << "Error in BigInt init\n";
            break;
        }
    }
}

void BigInt::printBigInt(void) const
{
    int j = 0;
    bool flag = false;
    while(not(flag))
    {
        if (d[j] != 0)
        {
            flag = true;
            j --; 
        }
        j++;
    }
    for (int i = j; i< BIGINT_LENGTH; i++)
    {
        switch (d[i])
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
    cout << "\n";
}

BigInt &operator+=(BigInt &a,const BigInt& b)
{
    unsigned char carry = 0;
    for (int i = BIGINT_LENGTH-1; i>= 0; i--)
    {
        a.d[i] += b.d[i]+carry;
        carry = 0;
        if (a.d[i] >= DIGIT_MAX)
        {
            a.d[i] &= DIGIT_MAX - 1; // masque bit à bit plus opti que la soustraction
            //a.d[i] -= DIGIT_MAX;
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
    memcpy(m, b.d, sizeof(b.d));
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
        if (a.d[i] >= b.d[i]+carry)
        {
            a.d[i] -= b.d[i]+carry;
            carry = 0;
        }
        else
        {
            a.d[i] += DIGIT_MAX;
            a.d[i] -= b.d[i]+carry;
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


void BigInt::shift(int n)
{
    unsigned char temp[BIGINT_LENGTH];
    for (int i=0; i<BIGINT_LENGTH-n; i++)
    {
        temp[n+i] = d[i];
    }
    memcpy(d,temp,sizeof(d));
}


BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt product[BIGINT_LENGTH];
    
    for (int bi = BIGINT_LENGTH; bi > 0; bi--)
    {
        int carry = 0;
        //unsigned char temp[BIGINT_LENGTH] = {};
        BigInt temp;
        for (int ai = BIGINT_LENGTH-1; ai > 0; ai--)
        {
            temp.d[ai] = b.d[bi]*a.d[ai] + carry;
            carry = temp.d[ai]/DIGIT_MAX;
            temp.d[ai] = temp.d[ai]%DIGIT_MAX;
        }
        temp.shift(BIGINT_LENGTH-bi);
        product += temp;
    }
    
    return product;
}

EN LITTLE ENDIAN:   
multiply(a[1..p], b[1..q], base)                            // Operands containing rightmost digits at index 1
  product = [1..p+q]                                        // Allocate space for result
  for b_i = 1 to q                                          // for all digits in b
    carry = 0
    for a_i = 1 to p                                        // for all digits in a
      product[a_i + b_i - 1] += carry + a[a_i] * b[b_i]
      carry = product[a_i + b_i - 1] / base
      product[a_i + b_i - 1] = product[a_i + b_i - 1] mod base
    product[b_i + p] = carry                               // last digit comes from final carry
  return product


/*// For each digit of b
for (var i = 0; i < b.digits.length; i++) {
    // For each digit of a
    for (var j = i; j < a.digits.length + i; j++) {
        // Multiply the digits, and add them to the current partial product, along with any carry
        digit = partial.digits[j] + (b.digits[i] * a.digits[j - i]) + carry;
        carry = Math.floor(digit / 10); // New carry
        partial.digits[j] = digit % 10; // Put the result back into the partial product
    }
    // Don't forget the final carry (if necessary)!
    if (carry) {
        digit = partial.digits[j] + carry;
        carry = Math.floor(digit / 10);
        partial.digits[j] = digit % 10;
    }
}

// That's it!
return partial;
*/


bool operator<(const BigInt &a, const BigInt &b)
{
    for (int i = 0; i<BIGINT_LENGTH; i++)
    {
        if (a.d[i] > b.d[i])
            return false;
        else if (a.d[i] < b.d[i])
            return true; 
    }
    return false; // a == b
}


BigInt operator%(const BigInt &a, const BigInt &b)
{
    BigInt temp = a;
    while (not(temp < b))
    {
        temp -= b;
    }
    while (temp < 0)
    {
        temp += b;
    }

    return temp;
}


BigInt mod_add(const BigInt &a, const BigInt &b, const BigInt &p)
{
    BigInt temp;
    temp = a+b;
    while (not(temp < p))
    {
        temp -= p;
    }
    return temp;
}


// modular substraction
BigInt mod_sub(const BigInt &a, const BigInt &b, const BigInt &p)
{
    BigInt temp;

    temp = a-b;
    while (not(temp < p))
    {
        temp -= p;
    }
    while (temp < 0)
    {
        temp += p;
    }

    return temp;
}


int main()
{
    string x = "0D9029AD2C7E5CF4340823B2A87DC68C9E4CE3174C1E6EFDEE12C07D";
    string y = "58AA56F772C0726F24C6B89E4ECDAC24354B9E99CAA3F6D3761402CD";
    string z = "04444458";
    string u = "d";
    string t = "0ffffffffffffffffffffffffffffffffffffffffffffffffffffeff";
    string v = "DEE12C07D";

    BigInt a(x);
    //a.printBigInt();

    BigInt b(y);

    BigInt c;
    BigInt d(v);
    BigInt e(z);
    //c = b-a;
    //c = a+b;
    //c.printBigInt();
    //c = mod_add(d,d,e);
    //c.printBigInt();
    c = d*e;
    d.printBigInt();
    e.printBigInt();
    c.printBigInt();


    //faire le add avec les overflow : convertir les types ne coute rien
    // soustraction utilisant -b = b barre +1 :~b= b barre
    // coder operateur modulo

    /*unsigned char h = 255;
    unsigned char j = 2;
    unsigned char k = 255+2;
    cout << (int) h << "\t"<< (int) j << "\t"<< (int) k;*/
    
    return 0;
}