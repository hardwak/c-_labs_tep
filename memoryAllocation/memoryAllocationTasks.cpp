//
// Created by ymher on 27.10.2023.
//
#include <iostream>
#include "memoryAllocationTasks.h"
#include "modification.h"
#include "CTable.h"

void ma_test(){
    cTableTest();
    std::cout << "End of Ctable test" << std::endl;
    v_alloc_table_fill_34(5);
    int **piTable;
    int sizeX = 5, sizeY = 3;

    b_alloc_table_2_dim(&piTable, sizeX, sizeY);
    b_dealloc_table_2_dim(&piTable, sizeX, sizeY);

    int** testTab = allocateTable2DBlock(3, 5);
    deallocateTable2DBlock(testTab);

    std::cout << "end";
}

void v_alloc_table_fill_34(int iSize){
    if (iSize < 1)
        throw std::invalid_argument("Tab tabSize should be greater than 0");

    int* tab;
    tab = new int[iSize];
    for (int i = 0; i < iSize; ++i)
        tab[i] = 34;


    for (int i = 0; i < iSize; ++i)
        std::cout << tab[i] << " ";
    std::cout << std::endl;

    delete tab;
}

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 1 || iSizeY < 1)
        return false;

    *piTable = new int *[iSizeY];

    for (int i = 0; i < iSizeY; ++i) {
        (*piTable)[i] = new int[iSizeX];
//        for (int j = 0; j < iSizeX; ++j) {
//            (*piTable)[i][j] = 0;
//            cout << (*piTable)[i][j] << " ";
//        }
//        cout << endl;
    }
    return true;
}

bool b_dealloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY){
    if (iSizeX < 1 || iSizeY < 1)
        return false;

    for (int i = 0; i < iSizeY; ++i) {
        delete[] (*piTable)[i];
    }
    delete[] (*piTable);

    return true;
}