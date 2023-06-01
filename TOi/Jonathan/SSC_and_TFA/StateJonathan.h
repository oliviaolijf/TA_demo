//
// Created by Jonathan on 01/03/2023.
//

#ifndef ING_1_STATE_H
#define ING_1_STATE_H
#include <iostream>
#include "vector"
using namespace std;

class StateJonathan {
private:
    string name;
    bool final;
    bool first;

public:
    StateJonathan(bool isFinal, bool isFirst, string stateName);
    string getName();
    bool getFinal();
    bool getFirst();

};




#endif //ING_1_STATE_H
