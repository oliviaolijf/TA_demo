//
// Created by Sinem.E on 30/04/2023.
//

#ifndef DFA_CPP_DFACONFIG_H
#define DFA_CPP_DFACONFIG_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "State.h"
#include "Transition.h"

using json = nlohmann::json;
using namespace std;

class DFAConfig {

private:
    string startState;
    vector<string> finalStates;
    map<string,State *> states;
    string type;
    vector<Transition *> transitions ;
    vector<string> alphabet;

public:
    const string &getStartState() const;

    void setStartState(const string &startState);

    const vector<string> &getFinalStates() const;

    void addFinalState(string finalStates);

    void setFinalStates(const vector<string> &finalStates);

    const string &getType() const;

    void setType(const string &type);

    const vector<Transition *> &getTransitions() const;

    void setTransitions(const vector<Transition *> &transitions);

    const vector<string> &getAlphabet() const;

    void setAlphabet(const vector<string> &alphabet);

    void addAlphabet(string alphabet);

    void addState(State* state);

    string makeString(vector<string> states);

    void addTransitionsDFA(Transition* transition);

    map<string, State *> &getStates();

    void setStates(map<string, State *> &states);

    void print();

};



#endif //DFA_CPP_DFACONFIG_H
