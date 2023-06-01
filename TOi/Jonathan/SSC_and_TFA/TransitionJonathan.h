//
// Created by Jonathan on 03/03/2023.
//

#ifndef ING_1_TRANSITION_H
#define ING_1_TRANSITION_H
#include <iostream>
#include "StateJonathan.h"
using namespace std;



class TransitionJonathan {
private:
    string symbol;
    StateJonathan* from;
    StateJonathan* to;

public:
    TransitionJonathan(string symbol, StateJonathan* from, StateJonathan* to);

    string getSymbol();
    StateJonathan* getFrom();
    StateJonathan* getTo();



};


#endif //ING_1_TRANSITION_H
