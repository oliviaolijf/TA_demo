//
// Created by Sinem.E on 30/04/2023.
//

#include "DFAConfig.h"

const string &DFAConfig::getStartState() const {
    return startState;
}

void DFAConfig::setStartState(const string &startState) {
    DFAConfig::startState = startState;
}

const vector<string> &DFAConfig::getFinalStates() const {
    return finalStates;
}

void DFAConfig::setFinalStates(const vector<string> &finalStates) {
    DFAConfig::finalStates = finalStates;
}
void DFAConfig::addFinalState(string finalState) {
    this->finalStates.push_back(finalState);
}

const string &DFAConfig::getType() const {
    return type;
}

void DFAConfig::setType(const string &type) {
    DFAConfig::type = type;
}

const vector<Transition *> &DFAConfig::getTransitions() const {
    return transitions;
}

void DFAConfig::setTransitions(const vector<Transition *> &transitions) {
    DFAConfig::transitions = transitions;
}

const vector<string> &DFAConfig::getAlphabet() const {
    return alphabet;
}

void DFAConfig::setAlphabet(const vector<string> &alphabet) {
    DFAConfig::alphabet = alphabet;
}

void DFAConfig::addAlphabet(string alphabet) {
    this->alphabet.push_back(alphabet);
}


void DFAConfig::addState(State* state) {
    this->states[state->getName()]=state;
}

string DFAConfig::makeString(vector<string> states) {
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

void DFAConfig::addTransitionsDFA(Transition *transition) {
    this->transitions.push_back(transition);
}

map<string, State *> &DFAConfig::getStates() {
    return states;
}

void DFAConfig::setStates(map<string, State *> &states) {
    DFAConfig::states = states;
}

void DFAConfig::print() {
    json j;
    j["type"] = getType();
    j["alphabet"] = getAlphabet();

    vector<json> states;
    for(const auto& state: getStates()) {
        json stateInfo;
        stateInfo["name"] = state.second->getName();
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