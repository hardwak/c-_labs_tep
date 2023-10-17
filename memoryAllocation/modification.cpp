//
// Created by ymher on 17.10.2023.
//
#include "modification.h"
#include <iostream>
using namespace std;

int** allocateTable2DBlock(int sizeX, int sizeY) {
    if (sizeY < 1 || sizeX < 1)
        return nullptr;

    int fullsize = sizeX * sizeY;

    int * fullBlock = new int [fullsize];

    for (int i = 0; i < fullsize; ++i) {
        fullBlock[i] = i;
    }

    int ** mainTab = new int *[sizeX];
    for (int i = 0; i < sizeX; ++i) {
        mainTab[i] = &fullBlock[(i*sizeY)];
    }

    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            cout << mainTab[i][j] << " ";
        }
        cout << endl;
    }

    return mainTab;
}

void deallocateTable2DBlock(int **tab){
    delete[] tab[0];
    delete[] tab;
}