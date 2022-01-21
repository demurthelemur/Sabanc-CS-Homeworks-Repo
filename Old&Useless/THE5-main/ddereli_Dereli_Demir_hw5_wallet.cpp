#include "ddereli_Dereli_Demir_hw5_wallet.h"
#include <iostream>
#include <sstream>

using namespace std;

//default constructor
Wallet::Wallet() {
    size = 0;
    array = NULL;
}

//destructor
Wallet::~Wallet() {
    delete[] array;
}

//copy constructor
Wallet::Wallet(const Wallet& toCoppy) {
    size = toCoppy.size;
    array = new Money[size];
    for (int i = 0; i < size; i++) {
        array[i] = toCoppy.array[i];
    }
}

//getter for size
int Wallet::getSize() const {
    return size;
}

//getter for name
string Wallet::getName(int i) const {
    return array[i].currency;
}

//getter for amount
double Wallet::getAmount(int i) const {
    return array[i].amount;
}

//size setter
void Wallet::setSize(int newSize) {
    size = newSize;
    array = new Money[size];
}

//setter to change one element of the array
void Wallet::setArrayElement(int i, string name, double amount) {
    array[i].currency = name;
    array[i].amount = amount;
}

//getting the name element from the selected array location
string Wallet::getName(int i) {
    return array[i].currency;
}

//setter to change the amount
void Wallet::setAmount(int i, double newAmount) {
    array[i].amount = newAmount;
}

// << operator overload

ostream& operator<<(ostream& os, const Wallet& selected) {
    for (int i = 0; i < selected.getSize(); i++) {
        os << selected.getName(i) << " " << selected.getAmount(i) << " - ";
    }
    return os;
}

// + operation overload lhs Wallet rhs Money
Wallet operator+ (const Wallet& lhs, const Money& rhs) {
    Wallet copy;
    bool inArray = false;
    int foundLocation = 0;
    for (int i = 0; i < lhs.getSize(); i++) {
        if (lhs.getName(i) == rhs.currency) {
            inArray = true;
            foundLocation = i;
        }
    }
    if(inArray){
        copy.setSize(lhs.getSize());
    }else if(lhs.getSize() == 0 ){
        copy.setSize(1);
    }else{
        copy.setSize(lhs.getSize() + 1);
    }

    string tempName;
    double tempAmount;
    for (int i = 0; i < lhs.getSize(); i++) {
        tempName = lhs.getName(i);
        tempAmount = lhs.getAmount(i);
        copy.setArrayElement(i, tempName, tempAmount);
    }

    if (inArray) {
        copy.setAmount(foundLocation, rhs.amount + copy.getAmount(foundLocation));
    }
    else {
        copy.setArrayElement(copy.getSize() - 1, rhs.currency, rhs.amount);
    }

    return copy;
}


// + operation overload lhs Wallet rhs Wallet
const Wallet operator+ (const Wallet& lhs, const Wallet& rhs) {
    Wallet copy;
    int sharedCurrencies = 0;
    for (int i = 0; i < lhs.getSize(); i++) {
        for (int k = 0; k < rhs.getSize(); k++) {
            if (lhs.getName(i) == rhs.getName(k)) {
                sharedCurrencies++;
            }
        }
    }
    copy.setSize(lhs.getSize() + rhs.getSize() - sharedCurrencies);

    string tempName;
    double tempAmount;
    for (int i = 0; i < lhs.getSize(); i++) {
        tempName = lhs.getName(i);
        tempAmount = lhs.getAmount(i);
        copy.setArrayElement(i, tempName, tempAmount);
    }

    int currentLocation = lhs.getSize();
    for (int i = 0; i < lhs.getSize(); i++) {
        for (int k = 0; k < rhs.getSize(); k++) {
            if (copy.getName(i) == rhs.getName(k)) {
                copy.setAmount(i, rhs.getAmount(k) + lhs.getAmount(i));
            }
            else {
                copy.setArrayElement(currentLocation, rhs.getName(k), rhs.getAmount(k));
                currentLocation++;
            }
        }
    }
    return copy;
}

//Operator overloading for - operator
Wallet operator- (const Wallet& lhs, const Money& rhs) {
    Wallet copy;
    bool moneyIn = false;
    int locationFound = 0;
    for (int i = 0; i < lhs.getSize(); i++) {
        if (lhs.getName(i) == rhs.currency) {
            moneyIn = true;
            locationFound = i;
        }
    }
    double moneyInWallet = lhs.getAmount(locationFound);
    double moneySpent(rhs.amount);

    string tempName;
    double tempAmount;

    if (moneyInWallet - moneySpent < 0) {
        for (int i = 0; i < lhs.getSize(); i++) {
            tempName = lhs.getName(i);
            tempAmount = lhs.getAmount(i);
            copy.setArrayElement(i, tempName, tempAmount);
        }
        return copy;
    }
    else {
        for (int i = 0; i < lhs.getSize(); i++) {
            tempName = lhs.getName(i);
            tempAmount = lhs.getAmount(i);
            copy.setArrayElement(i, tempName, tempAmount);
        }
        copy.setAmount(locationFound, moneyInWallet - moneySpent);
        return copy;

    }
}
/* Begin: code taken from linkedistextraoperator.cpp and updated */
//operator overloading for = operator
const Wallet& Wallet::operator= (const Wallet& rhs) {
    if (this != &rhs) {
        delete[] array;
        size = rhs.size;
        array = new Money[size];
        for (int i = 0; i < rhs.size; i++) {
            array[i] = rhs.array[i];
        }
    }
    return *this;
}
/* End: code taken from linkedistextraoperator.cpp and updated */

//operator overload for ==
bool operator==(const Wallet &lhs, const Wallet&rhs){//  operator (==)
    if (lhs.getSize() == rhs.getSize()){
        for (int i = 0; i < lhs.getSize(); i++){
            for (int k = 0; k < rhs.getSize(); k++){
                if ((lhs.getAmount(i) == rhs.getAmount(k)) && lhs.getName(i) == rhs.getName(k)){
                    return true;
                }
            }
        }
    }
    return false;
}

//operator overload for >=
bool operator>=(const Wallet& lhs, const Money& rhs) {
    int foundLocation = 0;
    bool doesExists = false;
    for (int i = 0; i < lhs.getSize(); i++) {
        if (lhs.getName(i) == rhs.currency) {
            foundLocation = i;
            doesExists = true;
        }
    }
    if (!doesExists) {
        return false;
    }
    if (lhs.getAmount(foundLocation) >= rhs.amount) {
        return true;
    }
    else {
        return false;
    }
}

//operator overload for <=
bool operator<=(const Money& lhs, const Wallet& rhs) {
    int foundLocation = 0;
    for (int i = 0; i < rhs.getSize(); i++) {
        if (lhs.currency == rhs.getName(i)) {
            foundLocation = i;
        }
    }
    if (lhs.amount <= rhs.getAmount(foundLocation)) {
        return true;
    }
    else {
        return false;
    }
}

//operator overload for +=

Wallet& Wallet::operator+= (const Wallet& rhs) {
    Wallet copy;
    int inBoth = 0;
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < rhs.getSize(); k++) {
            if (array[i].currency == rhs.getName(k)) {
                inBoth++;
            }
        }
    }
    copy.setSize(size + rhs.size -inBoth);
    string tempName;
    double tempAmount;
    for (int i = 0; i < size; i++) {
        tempName = array[i].currency;
        tempAmount = array[i].amount;
        copy.setArrayElement(i, tempName, tempAmount);
    }

    int currentLocation = size;
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < rhs.getSize(); k++) {
            if (copy.getName(i) == rhs.getName(k)) {
                copy.setAmount(i, rhs.getAmount(k) + array[i].amount);
            }
            else {
                copy.setArrayElement(currentLocation, rhs.getName(k), rhs.getAmount(k));
                currentLocation++;
            }
        }
    }
    delete[] array;
    size = 1;
    for (int i = 0; i < rhs.size; i++) {
        array[i] = copy.array[i];
    }
    return *this;
}

