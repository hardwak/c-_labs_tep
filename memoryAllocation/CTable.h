//
// Created by ymher on 16.10.2023.
//

#ifndef TEPLABY_CTABLE_H
#define TEPLABY_CTABLE_H

class CTable;
void cTableTest();
void v_mod_tab(CTable *pcTab, int iNewSize);
void v_mod_tab_noP(CTable cTab, int iNewSize);
void printTAB(int *piTab, int size);
void fillTabWithNum(int *piTab, int size, int num);

#endif //TEPLABY_CTABLE_H
