//
// Created by dio on 27/02/2023.
//
using namespace std;

#include <set>
#include <string>
#include "vector"
#include "StateDio.h"
#include "json.hpp"
#include "StateSetDio.h"

using json = nlohmann::json;


#ifndef OPDRACHT_1_DFA_H
#define OPDRACHT_1_DFA_H


class DFADio{

private:
    bool deleted=false;
    vector<StateDio *> states;
    vector <string> alphabet;
    StateDio * startState;
public:
    void setStartState(StateDio *startState);

public:
    void setStates(const vector<StateDio *> &states);

    void setAlphabet(vector<string> a);

    bool accepts(const string s);

    void setTransitionFunction (string from,string to,string input);

    DFADio(const char* a);

    DFADio(json a);

    DFADio();

    DFADio(DFADio &dfa1, DFADio &dfa2, bool intersection);
    //indien bool=true creër je de intersectie van dfa1 en dfa2
    //indien bool=false creër je de unie van dfa1 en dfa2

    void print();

    json get_json_dfa();

    virtual ~DFADio();

    void createProductStateSets(string symbol, StateSetDio* current, vector<StateSetDio*> &visited);

    const vector<StateDio *> &getStates() const;

    const vector<string> &getAlphabet() const;

    StateDio *getStartState() const;

    void changeToComplementDFA();

};


#endif //OPDRACHT_1_DFA_H
