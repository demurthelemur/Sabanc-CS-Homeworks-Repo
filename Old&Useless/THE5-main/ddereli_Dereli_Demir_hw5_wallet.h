#ifndef WALLET
#define WALLET
#include <iostream>
#include <string>

using namespace std;

struct Money{
    string currency;
    double amount;
};

class Wallet{
    private:
        //initilization of size and dynamic array
        int size;
        Money *array;
    public:
        Wallet();       //default constructor
        ~Wallet();      //destructor
        Wallet(const Wallet &copy);   //copy constructor
        int getSize() const;    //getter function for size
        string getName(int i) const;    //getter function for currency name
        double getAmount(int i) const;    //getter function for currency amount
        void setSize(int newSize);      //setter function for array size
        void setArrayElement(int i, string currency, double amount);    //setter functiın to set an entire element of array
        string getName(int i);   //getter function for currency name
        void setAmount(int i, double newAmount);    //setter function for amount of currency
        const Wallet &operator= (const Wallet&rhs);    //member function for overloading =
        Wallet &operator+= (const Wallet &rhs);    //member function for overloading +=
};

ostream & operator<<(ostream & os, const Wallet & print);   //free function for overloading <<
Wallet operator+ (const Wallet &lhs, const Money & rhs);    //free function for overloading + for wallet to money
const Wallet operator+ (const Wallet &lhs, const Wallet &rhs);    //free function for overloading + for wallet to wallet
Wallet operator- (const Wallet &lhs, const Money &rhs);     //free function for overloading -
bool operator==(const Wallet &lhs, const Wallet &rhs);      //free function for overloading ==
bool operator>=(const Wallet &lhs, const Money &rhs);       //free function for overloading >=
bool operator<=(const Money &lhs, const Wallet &rhs);       //free function for overloading <=
#endif
