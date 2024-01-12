//
// Created by ymher on 09.01.2024.
//

#include "MySmartPointer.h"
#include <stdexcept>

#ifndef TEPLABY_MYARRAY_H
#define TEPLABY_MYARRAY_H

template <typename T>
class MyArray {
public:
    MySmartPointer<T> ptr;
    int tabSize;

    MyArray(int size): tabSize(size), ptr(new T[size]){}

    MyArray(const MyArray<T> &other): tabSize(other.tabSize){
        MySmartPointer<T> newPtr(new T[other.tabSize]);
        for (int i = 0; i < tabSize; ++i) {
            newPtr.operator->()[i] = other.ptr.operator->()[i];
        }
        ptr = newPtr;
    }

    MyArray(MyArray<T> &&other) noexcept : tabSize(other.tabSize), ptr(other.ptr) {
        other.ptr = nullptr;
        other.tabSize = 0;
    }

    ~MyArray(){
//        delete[] *ptr;
    }

    int size(){
        return tabSize;
    }

    T& operator[](int index){
        if (index < tabSize && index > -1) {
            return *(ptr.operator->() + index);
        } else
            throw std::out_of_range("Index out of bound");
    }

    MyArray& operator=(MyArray<T> &other) noexcept {
        if (this != &other){
            tabSize = other.tabSize;
            MySmartPointer<T> newPtr(new T[other.tabSize]);
            for (int i = 0; i < tabSize; ++i) {
                newPtr.operator->()[i] = other.ptr.operator->()[i];
            }
            ptr = newPtr;
        }
        return *this;
    }
//
//    MyArray& operator=(MyArray<T> &&other) noexcept {
//        if (this != &other){
//            delete ptr;
//            tabSize = other.tabSize;
//            ptr = other.ptr;
//            other.ptr = nullptr;
//            other.tabSize = 0;
//        }
//        return *this;
//    }
};

void myArrayTest();

#endif //TEPLABY_MYARRAY_H
