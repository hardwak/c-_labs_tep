//
// Created by ymher on 28.10.2023.
//
#include <iostream>
#include "CNumber.h"
#include <vector>

void oo_test() {
    CNumber c_num_0, c_num_1;
    c_num_0 = 234;
    c_num_1 = 78;

    std::cout << c_num_0.sToStr() << " " << c_num_1.sToStr() << std::endl;

    std::cout << "Sum: " << c_num_1 + c_num_0 << std::endl;

    std::cout << "Diff: " << c_num_0 - c_num_1 << std::endl;

//    c_num_0 = c_num_1;

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
    int borrow = 0;
    for (int i = 0; i < bigger->size; ++i) {
        singleNum = bigger->tab[bigger->size - 1 - i] + borrow;
        if (smaller->size - 1 - i >= 0)
            singleNum += smaller->tab[smaller->size - 1 - i];

        newNumber.tab[newNumber.size - 1 - i] = singleNum % 10;

        borrow = singleNum >= 10 ? 1 : 0;
    }

    if (borrow == 1) {
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

CNumber CNumber::operator-(CNumber &other) {
    std::vector<int> num1, num2, result;

    num1.reserve(this->size);
    for (int i = 0; i < this->size; ++i)
        num1.push_back(this->tab[i]);

    num2.reserve(other.size);
    for (int i = 0; i < other.size; ++i)
        num2.push_back(other.tab[i]);

    int borrow = 0;
    for (int i = 0; i < std::max(num1.size(), num2.size()); ++i) {
        int singleNum1 = (i < num1.size()) ? num1.at(num1.size() - 1 - i) : 0;
        int singleNum2 = (i < num2.size()) ? num2.at(num2.size() - 1 - i) : 0;

        int diff = singleNum1 - singleNum2 - borrow;
        if (diff < 0){
            diff += 10;
            borrow = 1;
        } else
            borrow = 0;

        result.insert(result.begin(), diff);
    }

    while (result.size() > 0 && result.front() == 0){
        result.erase(result.begin());
    }

    if (result.empty())
        result.push_back(0);

    CNumber newNumber;
    delete[] newNumber.tab;
    newNumber.tab = new int[result.size()];
    newNumber.size = result.size();

    for (int i = 0; i < result.size(); ++i) {
        newNumber.tab[i] = result.at(i);
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