//
// Created by ymher on 28.10.2023.
//
#include <iostream>
#include "CNumber.h"

void oo_test(){
    CNumber c_num_0, c_num_1;
    c_num_0 = 368;
    c_num_1 = 1567;

    std::cout << c_num_0.sToStr() << " " << c_num_1.sToStr() << std::endl;

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

std::ostream& operator<<(std::ostream& os, const CNumber& obj){
    std::string stringToReturn;
    for (int i = 0; i < obj.size; ++i) {
        stringToReturn += std::to_string(obj.tab[i]);
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