//
// Created by ymher on 04.01.2024.
//

#include "MySmartPointer.h"
#include <iostream>
class Class {
public:
    Class(int val) : data(val) {}

    void show() {
        std::cout << "Data: " << data << std::endl;
    }

private:
    int data;
};


void smart_pointer_test() {
    MySmartPointer<Class> smartPtr(new Class(42));
    std::cout << "Reference Count: " << smartPtr.pc_counter->iGet() << std::endl;
    MySmartPointer<Class> smartPtrCopy = smartPtr;

    smartPtr->show();
    smartPtrCopy->show();
    std::cout << "Reference Count: " << smartPtr.pc_counter->iGet() << std::endl;

}