//
// Created by Jonathan on 01/03/2023.
//

#include "StateJonathan.h"

StateJonathan::StateJonathan(bool isFinal, bool isFirst, string stateName) {
    StateJonathan::name = stateName;
    StateJonathan::final = isFinal;
    StateJonathan::first = isFirst;
}

string StateJonathan::getName() {
    return name;
}

bool StateJonathan::getFinal() {
    return final;
}

bool StateJonathan::getFirst() {
    return first;
}