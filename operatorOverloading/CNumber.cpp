//
// Created by ymher on 28.10.2023.
//
#include <iostream>
#include "CNumber.h"
#include <vector>

void oo_test() {
    CNumber c_num_0, c_num_1, c_num_2;
    c_num_0 = 2147483647;
    c_num_1 = 24512;

    std::cout << c_num_0.sToStr() << " " << c_num_1.sToStr() << std::endl;

    c_num_2 = c_num_1 + c_num_0;

    std::cout << "Sum: " << c_num_2 << std::endl;

    std::cout << "Diff: " << c_num_0 - c_num_1 << std::endl;

    std::cout << "Mult: " << c_num_0 * c_num_1 << std::endl;

    std::cout << "Division: " << c_num_0 / c_num_1 << std::endl;
//    c_num_0 = c_num_1;

    std::cout << c_num_0 << " " << c_num_1 << std::endl;
}

void CNumber::eraseZerosFromVectorBegin(std::vector<int> &vector) {
    while (vector.size() > 0 && vector.front() == 0) {
        vector.erase(vector.begin());
    }

    if (vector.empty())
        vector.push_back(0);
}

CNumber CNumber::convertVectorToCNumber(std::vector<int> &vector) {
    CNumber newNumber;
    delete[] newNumber.tab;
    newNumber.tab = new int[vector.size()];
    newNumber.size = vector.size();

    for (int i = 0; i < vector.size(); ++i) {
        newNumber.tab[i] = vector.at(i);
    }

    return newNumber;
}

std::vector<int> CNumber::convertCNumberToVector(CNumber *num) {
    std::vector<int> v;
    v.reserve(num->size);
    for (int i = 0; i < num->size; ++i)
        v.push_back(num->tab[i]);

    return v;
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

    num1 = convertCNumberToVector(this);
    num2 = convertCNumberToVector(&other);

    int borrow = 0;
    for (int i = 0; i < std::max(num1.size(), num2.size()); ++i) {
        int singleNum1 = (i < num1.size()) ? num1.at(num1.size() - 1 - i) : 0;
        int singleNum2 = (i < num2.size()) ? num2.at(num2.size() - 1 - i) : 0;

        int diff = singleNum1 - singleNum2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else
            borrow = 0;

        result.insert(result.begin(), diff);
    }

    eraseZerosFromVectorBegin(result);

    return convertVectorToCNumber(result);
}

CNumber CNumber::operator*(CNumber &other) {
    std::vector<int> num1, num2;

    CNumber result;
    result = 0;

    num1 = convertCNumberToVector(this);
    num2 = convertCNumberToVector(&other);

    int borrow = 0;
    for (int i = 0; i < num2.size(); ++i) {
        std::vector<int> nextNum;
        for (int j = 0; j < num1.size(); ++j) {
            int singleNum = num2.at(num2.size() - 1 - i) * num1.at(num1.size() - 1 - j) + borrow;
            borrow = singleNum / 10;
            nextNum.insert(nextNum.begin(), singleNum % 10);
            if (j == num1.size() - 1 && borrow > 0) {
                nextNum.insert(nextNum.begin(), singleNum / 10);
            }
        }
        borrow = 0;

        eraseZerosFromVectorBegin(nextNum);

        CNumber newNumber;
        delete[] newNumber.tab;
        newNumber.tab = new int[nextNum.size() + i];
        newNumber.size = nextNum.size() + i;

        for (int j = 0; j < nextNum.size() + i; ++j) {
            if (j < nextNum.size())
                newNumber.tab[j] = nextNum.at(j);
            else
                newNumber.tab[j] = 0;
        }

        result = result + newNumber;
    }

    return result;
}

CNumber CNumber::operator/(CNumber &other) const {
    CNumber copy, result, one;
    copy = *this;
    one = 1;
    result = 0;

    if (other == result)
        throw std::invalid_argument("Division by zero not allowed");

    while (copy > other || copy == other) {
        copy = copy - other;
        result = result + one;
    }

    return result;

    /*std::vector<int> num1, result;

    num1 = convertCNumberToVector(this);

    int num2 = 0;
    for (int i = 0; i < other.size; ++i) {
        num2 += other.tab[other.size - 1 -i] * std::pow(10, i);
    }

    int borrow = 1;
    while (num1.size() > 0){
        int singleNum = 0;
        for (int i = 0; i < borrow; ++i) {
            singleNum += num1.at(borrow - 1 - i) * std::pow(10, i);
        }
        if (singleNum / num2 == 0){
            borrow++;
        }
        else{
            result.push_back(singleNum / num2);

            int rest = singleNum % num2;
            for (int i = 0; i < borrow; ++i) {
                num1.erase(num1.begin());
            }//first erase numbers, then push to begin rest

            borrow = 1;
        }
    }*/
}

bool CNumber::operator>(CNumber &other) {
    if (this->size == other.size) {
        for (int i = 0; i < this->size; ++i) {
            if (this->tab[i] > other.tab[i])
                return true;
            else if (this->tab[i] != other.tab[i])
                return false;
        }
    } else
        return this->size > other.size;
    return false;
}

bool CNumber::operator==(CNumber &other) {
    if (this->size != other.size)
        return false;
    else {
        for (int i = 0; i < this->size; ++i) {
            if (this->tab[i] != other.tab[i])
                return false;
        }
    }
    return true;
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

CNumber CNumber::operator+(int value) {
    CNumber num;
    num = value;
    return *this + num;
}

CNumber CNumber::operator-(int value) {
    CNumber num;
    num = value;
    return *this - num;
}

CNumber CNumber::operator*(int value) {
    CNumber num;
    num = value;
    return *this * num;
}

CNumber CNumber::operator/(int value) const {
    CNumber num;
    num = value;
    return *this / num;
}
