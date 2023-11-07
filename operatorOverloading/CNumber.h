//
// Created by ymher on 28.10.2023.
//

#ifndef TEPLABY_CNUMBER_H
#define TEPLABY_CNUMBER_H


#include <vector>

class CNumber {
private:
    bool isNegative;
    int *tab;
    int size;
    static void eraseZerosFromVectorBegin(std::vector<int> &vector);
    static CNumber convertVectorToCNumber(std::vector<int> &vector);
    static std::vector<int> convertCNumberToVector(CNumber *num);
    CNumber add(CNumber &other);
    CNumber subtract(CNumber &other);
public:
    CNumber(){
        size = 10;
        tab = new int [size];
        isNegative = false;
    }

    ~CNumber(){
        if (tab)
            delete[] tab;
    }

    CNumber& operator=(int iValue);
    CNumber& operator=(const CNumber &pcOther);
    friend std::ostream& operator<<(std::ostream& os, const CNumber& obj);
    std::string sToStr();
    CNumber operator+(CNumber &other);
    CNumber operator+(int value);
    CNumber operator-(CNumber &other);
    CNumber operator-(int value);
    CNumber operator*(CNumber &other);
    CNumber operator*(int value);
    CNumber operator/(CNumber &other) const;
    CNumber operator/(int value) const;
    bool operator>(CNumber &other) const;
    bool operator==(CNumber &other);
};

void oo_test();


#endif //TEPLABY_CNUMBER_H
