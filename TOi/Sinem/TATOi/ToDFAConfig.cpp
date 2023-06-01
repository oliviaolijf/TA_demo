//
// Created by Sinem.E on 22/04/2023.
//

#include "ToDFAConfig.h"

const string &ToDFAConfig::getStartState() const {
    return startState;
}

void ToDFAConfig::setStartState(const string &startState) {
    ToDFAConfig::startState = startState;
}

const vector<string> &ToDFAConfig::getFinalStates() const {
    return finalStates;
}

void ToDFAConfig::setFinalStates(const vector<string> &finalStates) {
    ToDFAConfig::finalStates = finalStates;
}

const string &ToDFAConfig::getType() const {
    return type;
}

void ToDFAConfig::setType(const string &type) {
    ToDFAConfig::type = type;
}

const vector<Transition *> &ToDFAConfig::getTransitions() const {
    return transitions;
}

void ToDFAConfig::setTransitions(const vector<Transition *> &transitions) {
    ToDFAConfig::transitions = transitions;
}

const vector<string> &ToDFAConfig::getAlphabet() const {
    return alphabet;
}

void ToDFAConfig::setAlphabet(const vector<string> &alphabet) {
    ToDFAConfig::alphabet = alphabet;
}

void ToDFAConfig::addState(State* state) {
    this->states[state->getName()]=state;
}

string ToDFAConfig::makeString(vector<string> states) {
    string state = "{";
    sort(states.begin(), states.end());
    set<string> toSet(states.begin(), states.end());
    for (string i: toSet) {
        state += i + ",";
    }
    state.erase(state.size()-1,state.size());
    state += "}";

    return state;
}

void ToDFAConfig::addTransitionsDFA(Transition *transition) {
    this->transitions.push_back(transition);
}

map<string, State *> &ToDFAConfig::getStates() {
    return states;
}

void ToDFAConfig::setStates(map<string, State *> &states) {
    ToDFAConfig::states = states;
}

void ToDFAConfig::print() {
    json j;
    j["type"] = getType();
    j["alphabet"] = getAlphabet();

    vector<json> states;
    for(const auto& state: getStates()) {
        json stateInfo;
        //TODO: is het state.second->getName() of state.first
        stateInfo["name"] = state.first;
        stateInfo["starting"] = state.second->isStart();
        stateInfo["accepting"] = state.second->isAccept();
        states.push_back(stateInfo);
    }
    j["states"] = states;

    vector<json> transitions;
    for (const auto i: getTransitions()) {
        json t;
        t["from"] = i->getFrom();
        t["to"] = i->getTo();
        t["input"] = i->getInput();
        transitions.push_back(t);
    }
    j["transitions"] = transitions;

    cout<< setw(4) << j << endl;
}