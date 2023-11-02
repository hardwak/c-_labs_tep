//
// Created by ymher on 28.10.2023.
//
#include <iostream>
#include "CNumber.h"

void oo_test(){
    CNumber c_num_0, c_num_1;
    c_num_0 = 21474;
    c_num_1 = 2147483647;

    std::cout << c_num_0.sToStr() << " " << c_num_1.sToStr() << std::endl;

    std::cout << "Sum: " << c_num_1 + c_num_0 << std::endl;

    c_num_0 = c_num_1;

    std::cout << c_num_0 << " " << c_num_1 << std::endl;
}

CNumber& CNumber::operator=(const int iValue) {
    if (tab)
        delete[]tab;

    std::string number = std::to_string(iValue);

    tab = new int [number.size()];
    //why static cast
    size = static_cast<int>(number.size());

    for (int i = 0; i < number.size(); ++i) {
        tab[i] = number[i] - '0';
    }

    return *this;

}

CNumber& CNumber::operator=(const CNumber &pcOther) {
//    tab = pcOther.tab;
//    size = pcOther.size;

    if (&pcOther == this){
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
    CNumber newNumber;
    delete[] newNumber.tab;
    newNumber.tab = new int [std::max(this->size, other.size)];
    newNumber.size = std::max(this->size, other.size);
    
    int singleNum;
    int overTen = 0;
    for (int i = 0; i < std::min(this->size, other.size); ++i) {
        singleNum = this->tab[this->size - 1 - i] + other.tab[other.size - 1 - i] + overTen;

        newNumber.tab[size - 1 - i] = singleNum % 10;

        overTen = singleNum >= 10 ? 1 : 0;
    }

    if (this->size == other.size && overTen == 1){
        int *newTab = new int[size + 1];
        newTab[0] = 1;
        for (int i = 1; i < size + 1; ++i) {
            newTab[i] = newNumber.tab[i - 1];
        }
        delete[] newNumber.tab;

        newNumber.tab = newTab;
        newNumber.size++;
    }

    if (this->size != other.size){
        CNumber* bigger;
        CNumber* smaller;
        if (this->size > other.size){
            bigger = this;
            smaller = &other;
        } else{
            bigger = &other;
            smaller = this;
        }

        int posOfDiff = bigger->size - smaller->size - 1;
        for (int i = 0; i <= posOfDiff; ++i) {
            newNumber.tab[posOfDiff - i] = bigger->tab[posOfDiff - i] + overTen;
            overTen = 0;
        }
    }

    return newNumber;
}

std::ostream& operator<<(std::ostream& os, const CNumber& obj){
    std::string stringToReturn;
    for (int i = 0; i < obj.size; ++i) {
        stringToReturn += std::to_string(obj.tab[i]) + " ";

    }
    os << stringToReturn;
    return os;
}

std::string CNumber::sToStr(){
    std::string stringToReturn;
    for (int i = 0; i < size; ++i) {
        stringToReturn += std::to_string(tab[i]);
    }
    return stringToReturn;
}