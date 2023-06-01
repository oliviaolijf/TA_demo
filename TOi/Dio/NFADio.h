//
// Created by dio on 29/03/2023.
//

#ifndef OPDRACHT_1_NFA_H
#define OPDRACHT_1_NFA_H


#include "StateDio.h"
#include "json.hpp"
#include "DFADio.h"
#include "StateSetDio.h"
#include <iostream>
#include <fstream>

class NFADio {
private:
public:
    const vector<string> &getAlphabet() const;

    const string &getType() const;

private:
    json configuration;
    vector<StateDio *> states;
    StateDio* startstate;
    vector <string> alphabet;
    string type;


public:
    NFADio();

    NFADio(const char* filename);

    void setStates(const vector<StateDio *> &states);

    void setAlphabet(vector<string> a);

    //bool accepts(const string s);

    void setTransitionFunction (string from,string to,string input);

    virtual DFADio toDFA();

    virtual ~NFADio();

    StateSetDio * createEmptySet();

    //void print();

    DFADio SSC();

    const vector<StateDio *> &getStates() const;

    const json &getConfiguration() const;

    StateDio *getStartstate() const;

    virtual void setStartstate(StateDio *startstate);

    virtual void setType(const string &type);

    virtual bool inVisited(vector<StateSetDio*> visited, vector<StateDio*> newset);

};


#endif //OPDRACHT_1_NFA_H
