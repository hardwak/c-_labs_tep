//
// Created by ymher on 16.10.2023.
//
#include <iostream>
#include "CTable.h"

using namespace std;

void cTableTest(){

    CTable c_tab = *new CTable();  //??? *
    CTable *pc_new_tab;

    fillTabWithNum(c_tab.getTab(), 10, 5);
    printTAB(c_tab.getTab(), 10);

    pc_new_tab = c_tab.pcClone();

    cout << "--------------------------" << endl;
    cout << "first Tab" << endl;

    v_mod_tab(pc_new_tab, 5);
    printTAB(pc_new_tab->getTab(), 5);

    cout << "second Tab" << endl;
    v_mod_tab_noP(c_tab, 5);
    printTAB(c_tab.getTab(), 5);


}

void printTAB(int *piTab, int size){
    for (int i = 0; i < size; ++i) {
        cout << piTab[i] << " ";
    }
    cout << endl;
}

void fillTabWithNum(int *piTab, int size, int num){
    for (int i = 0; i < size; ++i) {
        piTab[i] = num;
    }
}

void v_mod_tab(CTable *pcTab, int iNewSize){
    if (iNewSize < 1)
        return;

//    pcTab->bSetNewSize(iNewSize);
    pcTab->getTab()[0] = 0;
}

void v_mod_tab_noP(CTable cTab, int iNewSize){
    if (iNewSize < 1)
        return;

//    cTab.bSetNewSize(iNewSize);
    cTab.getTab()[0] = 0;
}