//
// Created by Jonat on 23/04/2023.
//

#ifndef ING_1_NFA_H
#define ING_1_NFA_H
#include <fstream>
#include <iomanip>
#include <iostream>
#include "StateJonathan.h"
#include "TransitionJonathan.h"
#include "vector"
#include "json.hpp"
#include <iomanip>
#include "DFAJonathan.h"
using json = nlohmann::json;
using namespace std;

class NFAJonathan {
private:
    vector<string> alphabet;
    vector<StateJonathan*> states{};
    vector<TransitionJonathan*> transitions{};
    StateJonathan* startState{};
    vector<StateJonathan*> finalStates;


public:
    NFAJonathan(string filePath);

    bool setAlphabet(vector<string> symbols);

    bool makeState(bool isFinal, bool isFirst, string stateName);

    bool addTransition(string from, string to,string symbol);

    bool inAlphabet(string symbol);

    StateJonathan* getState(string symbol);

    bool accepts(string language);

    DFAJonathan toDFA();

    void toDFAHelper(DFAJonathan *dfa, StateJonathan* state);

    void print();

    vector<string> splitString(string line);

    string orderAlphabeticly(string line);

    bool inVector(vector<StateJonathan*> state, string name);


};


#endif //ING_1_NFA_H
