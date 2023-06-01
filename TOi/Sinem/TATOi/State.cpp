//
// Created by Sinem.E on 26/04/2023.
//

#include "State.h"


const string &State::getName() const {
    return name;
}

void State::setName(const string &name) {
    State::name = name;
}

bool State::isStart() const {
    return start;
}

void State::setStart(bool start) {
    State::start = start;
}

bool State::isAccept() const {
    return accept;
}

void State::setAccept(bool accept) {
    State::accept = accept;
}


