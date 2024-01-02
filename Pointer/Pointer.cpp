//
// Created by ymher on 19.12.2023.
//

#include "Pointer.hpp"

void pointer_test(){
    int* val = new int(5);
    std::string str = "string";
    Pointer<int*> pointer(val);
    Pointer<std::string*> pointer1(&str);
    std::cout << *pointer << std::endl;
    delete val;

}