//
// Created by ymher on 16.10.2023.
//

#ifndef TEPLABY_CTABLE_H
#define TEPLABY_CTABLE_H

class CTable{
private:
    std::string s_name;
    std::string defaultName = "int table";
    int tableLen;
    int defaultTableLen = 10;
    int *piTable;
public:
    CTable(){
        s_name = defaultName;
        tableLen = defaultTableLen;
        piTable = new int [tableLen];
        std::cout << "bezp: '<" << s_name << ">'" << std::endl;
    }

    CTable(std::string sName, int iTableLen){
        s_name = sName;
        tableLen = iTableLen;
        piTable = new int [tableLen];
        std::cout << "parametr: '<" << s_name << ">'" << std::endl;
    }

    CTable(CTable &pcOther){
        s_name = pcOther.s_name + "_copy";
        tableLen = pcOther.tableLen;
        piTable = new int [tableLen];

        for (int i = 0; i < tableLen; ++i) {
            piTable[i] = pcOther.piTable[i];
        }

        std::cout << "kopiuj: '<" << s_name << ">'" << std::endl;
    }

    ~CTable(){
        delete[] piTable;
        std::cout << "usuwam: '<" << s_name << ">'" << std::endl;
    }

    void vSetName(std::string sName){
        this->s_name = sName;
    }

    bool bSetNewSize(int iTableLen){
        if (iTableLen < 1)
            return false;

        int *newTable = new int[iTableLen];

        for (int i = 0; i < std::min(iTableLen, this->tableLen); ++i) {
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
void cTableTest();
void v_mod_tab(CTable *pcTab, int iNewSize);
void v_mod_tab_noP(CTable cTab, int iNewSize);
void printTAB(int *piTab, int size);
void fillTabWithNum(int *piTab, int size, int num);

#endif //TEPLABY_CTABLE_H
