//
// Created by ymher on 04.01.2024.
//

#ifndef TEPLABY_CREFCOUNTER_H
#define TEPLABY_CREFCOUNTER_H


class CRefCounter
{
public:
    CRefCounter() { i_count; }
    int iAdd() { return(++i_count); }
    int iDec() { return(--i_count); };
    int iGet() { return(i_count); }
private:
    int i_count;
};


#endif //TEPLABY_CREFCOUNTER_H
