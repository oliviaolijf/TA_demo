//
// Created by Sinem.E on 22/04/2023.
//

#include "NFAConfig.h"

string &NFAConfig::getStartState() {
    return startState;
}

void NFAConfig::setStartState(string &startState) {
    this->startState = startState;
}

vector<string> &NFAConfig::getAlphabet() {
    return alphabet;
}

void NFAConfig::setAlphabet(string alphabet) {
    this->alphabet.push_back(alphabet);
}

void NFAConfig::addToStates(State* state) {
    this->states[state->getName()] = state;
}

string &NFAConfig::getType() {
    return type;
}

void NFAConfig::setType(string &type) {
    this->type = type;
}

vector<string> &NFAConfig::getFinalStates() {
    return finalStates;
}

void NFAConfig::setFinalStates(string finalState) {
    this->finalStates.push_back(finalState);
}

const vector<Transition *> &NFAConfig::getTransitions() const {
    return transitions;
}

void NFAConfig::setTransitions(const vector<Transition *> &transitions) {
    NFAConfig::transitions = transitions;
}

void NFAConfig::addTransitionsNFA(Transition* transition) {
    this->transitions.push_back(transition);
}

map<string, State *> &NFAConfig::getStates() {
    return states;
}


