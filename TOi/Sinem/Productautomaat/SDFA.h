//
// Created by Sinem.E on 30/04/2023.
//

#ifndef PRODUCTAUTOMAAT_DFA_H
#define PRODUCTAUTOMAAT_DFA_H

#include <string>
#include <iostream>
#include "DFAConfig.h"
#include "State.h"
#include <set>

using namespace std;

class SDFA {

private:
    DFAConfig dfaConfig;
    bool productType ;
    DFAConfig parseJson(string filename);
    DFAConfig product(SDFA dfa1, SDFA dfa2);

public:
    SDFA();

    SDFA(string filename);

    SDFA(SDFA dfa1, SDFA dfa2, bool type);

    void print();

    const DFAConfig &getDfaConfig() const;

    string  getToStateName(string fromStateName, string input);

    string  makeStateName(string stateName1, string stateName2);

    void addNext(SDFA dfa1, string currentStateOfDFA1, SDFA dfa2, string currentStteOfDFA2) ;

    bool isExist(string stateName);

    bool isEndState(string stateName);

};


#endif //PRODUCTAUTOMAAT_DFA_H
