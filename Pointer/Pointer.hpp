//
// Created by ymher on 19.12.2023.
//

#ifndef TEPLABY_POINTER_HPP
#define TEPLABY_POINTER_HPP

#include <iostream>

template<typename T, typename = void>
class Pointer;
template <typename T>
class Pointer<T*> {
private:
    T *value;
public:
    explicit Pointer(T *val):value(val){}

    T& operator*() {
        return *value;
    }
};

void pointer_test();

#endif //TEPLABY_POINTER_HPP
