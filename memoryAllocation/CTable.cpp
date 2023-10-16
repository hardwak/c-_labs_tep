//
// Created by ymher on 16.10.2023.
//
#include <iostream>
#include "CTable.h"

using namespace std;

class CTable{
private:
    string s_name;
    string defaultName = "int table";
    int tableLen;
    int defaultTableLen = 10;
    int *piTable;
public:
    CTable(){
        s_name = defaultName;
        tableLen = defaultTableLen;
        piTable = new int [tableLen];
        cout << "bezp: '<" << s_name << ">'" << endl;
    }

    CTable(string sName, int iTableLen){
        s_name = sName;
        tableLen = iTableLen;
        piTable = new int [tableLen];
        cout << "parametr: '<" << s_name << ">'" << endl;
    }

    CTable(CTable &pcOther){
        s_name = pcOther.s_name + "_copy";
        tableLen = pcOther.tableLen;
        piTable = pcOther.piTable;
        cout << "kopiuj: '<" << s_name << ">'" << endl;
    }

    ~CTable(){
        delete[] piTable;
        cout << "usuwam: '<" << s_name << ">'" << endl;
    }

    void vSetName(string sName){
        this->s_name = sName;
    }

    bool bSetNewSize(int iTableLen){
        if (iTableLen < 1)
            return false;

        int *newTable = new int[iTableLen];

        for (int i = 0; i < min(iTableLen, this->tableLen); ++i) {
            newTable[i] = piTable[i];
        }

        delete[] piTable;
        this->piTable = newTable;
        this->tableLen = iTableLen;
        return true;
    }

    CTable *pcClone(){
        return new CTable(*this);
    }

    int *getTab(){
        return piTable;
    }
};

int main(){

    CTable c_tab = *new CTable();  //??? *
    CTable *pc_new_tab;

    fillTabWithNum(c_tab.getTab(), 10, 5);
    printTAB(c_tab.getTab(), 10);

    pc_new_tab = c_tab.pcClone();



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

}

void v_mod_tab(CTable cTab, int iNewSize){

}