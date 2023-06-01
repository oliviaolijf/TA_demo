//
// Created by dio on 19/04/2023.
//

#ifndef OPDRACHT_1_RE_H
#define OPDRACHT_1_RE_H

#include <iostream>
#include "ENFADio.h"
#include "MyStack.h"

using namespace std;

class REDio {
public:

    friend class State;

    REDio(const string &expression, char eps);

    ENFADio toENFA();

    StateDio *createDefaultSet();

    tuple<ENFADio*,int> createENFA(const string &expression, int &i, StateDio * &start, StateDio* &current);

    void KleeneOperation(StateDio* &beginning, StateDio* &ending);

    void orOperation(StateDio *&start, StateDio *&current, MyStack &orStack);

    void endOR(StateDio *&current, MyStack &orStack);

    void concatenate(StateDio*& current, int &i);




private:
    string expression;
    char eps;
    int stateCounter=0;
    vector<StateDio*> states;
    StateDio* start;
    StateDio* ending;
    vector<string> alphabet;


};


#endif //OPDRACHT_1_RE_H
