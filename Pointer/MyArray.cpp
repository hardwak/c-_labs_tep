//
// Created by ymher on 09.01.2024.
//

#include "MyArray.h"
#include <iostream>
void myArrayTest(){
    MyArray<int> array(5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i*2;
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout<< std::endl;
    std::cout<< array.size() << std::endl;
//    std::cout << array[5];

//    MyArray<int> array1(5);
//    array1 = array;
//    for (int i = 0; i < 5; ++i) {
//        std::cout << array1[i] << " ";
//    }
//    std::cout<< std::endl;
//
//    array1[0] = 10;
//
//    std::cout << array[0] << " " << array1[0];
//    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
        array[i] = array[i]*2;
    }


    for (int i = 0; i < 5; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout<< std::endl;

//    for (int i = 0; i < 5; ++i) {
//        std::cout << array1[i] << " ";
//    }
//    std::cout<< std::endl;
}