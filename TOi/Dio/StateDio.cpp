//
// Created by dio on 27/02/2023.
//

#include <cassert>
#include "StateDio.h"

void StateDio::setTransitionFunction(string input, StateDio* to) {
    initcheck=this;
    if (this->uniqueTransition(input)){
        vector<StateDio*> states {to};
        transition_function[input] = states;
    } else{
        transition_function[input].push_back(to);
    }
}

vector<StateDio *> StateDio::transition(string input){
    return transition_function[input];
}

StateDio::StateDio(const string &label) : label(label) {
    initcheck=this;
}

bool StateDio::isStarting() const {
    return starting;
}

void StateDio::setStarting(bool starting) {
    StateDio::starting = starting;
}

bool StateDio::isAccepting() const {
    return accepting;
}

void StateDio::setAccepting(bool accepting) {
    StateDio::accepting = accepting;
}

const string &StateDio::getLabel() const {
    return label;
}

bool StateDio::uniqueTransition(string symbol) const {
    if (transition_function.find(symbol)==transition_function.end()){
        return true;
    } else{
        return false;
    }
}

StateDio::~StateDio() {
    initcheck= nullptr;
}

void StateDio::setLabel(const string &label) {
    StateDio::label = label;
}

vector<StateDio*> StateDio::eclose(StateDio* s, string eps) {
    vector<StateDio*> states;
    if (transition_function.find(eps)==transition_function.end()){
        states.push_back(this);
        return states;
    } else{
        states.push_back(this);
        vector<StateDio*> temp= this->transition(eps);
        for (auto p: temp) {
            if (p!=s){
                for  (auto i: p->eclose(p, eps)){
                    states.push_back(i);
                }
            }
        }
        return states;
    }

}
StateDio::StateDio() {
    initcheck=this;
}

const map<string, vector<StateDio *>> &StateDio::getTransitionFunction() const {
    return transition_function;
}

bool StateDio::properlInitialized() {
    if(initcheck==this){
        return true;
    }
    return false;
}


