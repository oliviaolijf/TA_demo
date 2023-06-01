//
// Created by dio on 9/04/2023.
//

#ifndef OPDRACHT_1_ENFA_H
#define OPDRACHT_1_ENFA_H

#include "NFADio.h"

class ENFADio: public NFADio{
    string eps;
public:
    explicit ENFADio(const char *filename);

    ENFADio();

    virtual bool inVisited(vector <StateSetDio*> visited, vector<StateDio*> newset);

    virtual DFADio toDFA();

    DFADio mssc();

    void printStats();

    const string &getEps() const;

    void setEps(const string &eps);

    bool accepts(string s);


};


#endif //OPDRACHT_1_ENFA_H
