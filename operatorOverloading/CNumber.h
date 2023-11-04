//
// Created by ymher on 28.10.2023.
//

#ifndef TEPLABY_CNUMBER_H
#define TEPLABY_CNUMBER_H


#include <vector>

class CNumber {
private:
    int *tab;
    int size;
    static void eraseZerosFromVectorBegin(std::vector<int> &vector);
    static CNumber convertVectorToCNumber(std::vector<int> &vector);
    static std::vector<int> convertCNumberToVector(CNumber *num);
public:
    CNumber(){
        size = 10;
        tab = new int [size];
    }

    ~CNumber(){
        if (tab)
            delete[] tab;
    }

    CNumber& operator=(const int iValue);
    CNumber& operator=(const CNumber &pcOther);
    friend std::ostream& operator<<(std::ostream& os, const CNumber& obj);
    std::string sToStr();
    CNumber operator+(CNumber &other);
    CNumber operator-(CNumber &other);
    CNumber operator*(CNumber &other);
};

void oo_test();


#endif //TEPLABY_CNUMBER_H
