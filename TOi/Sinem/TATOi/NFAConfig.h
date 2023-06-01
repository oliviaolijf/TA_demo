//
// Created by Sinem.E on 22/04/2023.
//

#ifndef TATOI_NFACONFIG_H
#define TATOI_NFACONFIG_H

#include <string>
#include <vector>
#include <map>
#include "State.h"
#include "Transition.h"

using namespace std;

class NFAConfig {
private:
    string startState;
    vector<string> finalStates;
    vector<string> alphabet;
    map<string, State*> states;
    string type;
    vector<Transition*> transitions;

public:
    string &getStartState();

    void setStartState(string &startState);

    vector<string> &getAlphabet();

    void setAlphabet(string alphabet);

    map<string, State *> &getStates();

    void addToStates(State* state);

    string &getType();

    void setType(string &type);

    vector<string> &getFinalStates();

    void setFinalStates(string finalState);

    const vector<Transition *> &getTransitions() const;

    void setTransitions(const vector<Transition *> &transitions);

    void addTransitionsNFA(Transition* transition);

};


#endif //TATOI_NFACONFIG_H
