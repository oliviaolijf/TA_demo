//
// Created by Sinem.E on 30/04/2023.
//

#include "Transition.h"

string &Transition::getFrom() {
    return from;
}

void Transition::setFrom(string &from) {
    Transition::from = from;
}

const string &Transition::getTo() const {
    return to;
}

void Transition::setTo(string &to) {
    Transition::to = to;
}

const string &Transition::getInput() const {
    return input;
}

void Transition::setInput(const string &input) {
    Transition::input = input;
}
