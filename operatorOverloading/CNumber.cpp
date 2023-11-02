//
// Created by ymher on 28.10.2023.
//
#include <iostream>
#include "CNumber.h"

void oo_test() {
    CNumber c_num_0, c_num_1;
    c_num_0 = 10;
    c_num_1 = 990;

    std::cout << c_num_0.sToStr() << " " << c_num_1.sToStr() << std::endl;

    std::cout << "Sum: " << c_num_1 + c_num_0 << std::endl;

    c_num_0 = c_num_1;

    std::cout << c_num_0 << " " << c_num_1 << std::endl;
}

CNumber &CNumber::operator=(const int iValue) {
    if (tab)
        delete[]tab;

    std::string number = std::to_string(iValue);

    tab = new int[number.size()];
    //why static cast
    size = static_cast<int>(number.size());

    for (int i = 0; i < number.size(); ++i) {
        tab[i] = number[i] - '0';
    }

    return *this;

}

CNumber &CNumber::operator=(const CNumber &pcOther) {
//    tab = pcOther.tab;
//    size = pcOther.size;

    if (&pcOther == this) {
        return *this;
    }

    if (this->tab) {
        delete[] tab;
    }

    this->size = pcOther.size;

    tab = new int[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = pcOther.tab[i];
    }

    return *this;
}

CNumber CNumber::operator+(CNumber &other) {
    CNumber *bigger = this;
    CNumber *smaller = &other;
    if (this->size < other.size) {
        bigger = &other;
        smaller = this;
    }

    CNumber newNumber;
    delete[] newNumber.tab;
    newNumber.tab = new int[bigger->size];
    newNumber.size = bigger->size;

    int singleNum;
    int overTen = 0;
    for (int i = 0; i < bigger->size; ++i) {
        singleNum = bigger->tab[bigger->size - 1 - i] + overTen;
        if (smaller->size - 1 - i >= 0)
            singleNum += smaller->tab[smaller->size - 1 - i];

        newNumber.tab[newNumber.size - 1 - i] = singleNum % 10;

        overTen = singleNum >= 10 ? 1 : 0;
    }

    if (overTen == 1) {
        int *newTab = new int[size + 1];
        newTab[0] = 1;
        for (int i = 1; i < size + 1; ++i) {
            newTab[i] = newNumber.tab[i - 1];
        }
        delete[] newNumber.tab;

        newNumber.tab = newTab;
        newNumber.size++;
    }


    return newNumber;
}

std::ostream &operator<<(std::ostream &os, const CNumber &obj) {
    std::string stringToReturn;
    for (int i = 0; i < obj.size; ++i) {
        stringToReturn += std::to_string(obj.tab[i]);

    }
    os << stringToReturn;
    return os;
}

std::string CNumber::sToStr() {
    std::string stringToReturn;
    for (int i = 0; i < size; ++i) {
        stringToReturn += std::to_string(tab[i]);
    }
    return stringToReturn;
}