//
// Created by dio on 29/03/2023.
//

#include "StateSetDio.h"

StateSetDio::StateSetDio(vector<StateDio *> &set) : set(set) {

    for (StateDio* p: set){
        if (p->isAccepting()){
            acceptSet = true;
        }
        states[p->getLabel()]=p;
    }
    label= createSetLabel(set);
}

StateSetDio::StateSetDio(vector<StateDio *> &set, bool product) : set(set) {
    for (StateDio* p: set){
        if (p->isAccepting()){
            acceptSet = true;
        }
        states[p->getLabel()]=p;
    }
    if (product){
        label= createProductLabel(set);
    }
}

string StateSetDio::createProductLabel(vector<StateDio *> &set){
    vector<string> symbols;
    for(int i=0; i<set.size();i++){
        symbols.push_back(set[i]->getLabel());
    }

    string s="(";
    for(int i=0; i<symbols.size()-1;i++){
        s+=symbols[i];
        s+=",";
    }
    s+=symbols[symbols.size()-1];
    s+=")";
    return s;
}

string StateSetDio::createSetLabel(vector<StateDio *> &set){
    vector<string> symbols;
    for(int i=0; i<set.size();i++){
        symbols.push_back(set[i]->getLabel());
    }
    for (int i=0; i<symbols.size(); i++){
        if(i>0 && symbols[i]<symbols[i-1]){
            string temp=symbols[i];
            symbols[i]=symbols[i-1];
            symbols[i-1]=temp;
            i=0;
        }
    }

    string s="{";
    for(int i=0; i<symbols.size()-1;i++){
        s+=symbols[i];
        s+=",";
    }
    s+=symbols[symbols.size()-1];
    s+="}";
    return s;
}

bool StateSetDio::equal(vector<StateDio *> &altset) {
    if (altset.size()!=set.size()){
        return false;
    }
    for(StateDio * p: altset){
        if (states.find(p->getLabel())==states.end()){
            return false;
        }
    }
    return true;
}

const vector<StateDio *> &StateSetDio::getSet() const {
    return set;
}

bool StateSetDio::isAcceptSet() const {
    return acceptSet;
}

void StateSetDio::setAcceptSet(bool acceptSet) {
    StateSetDio::acceptSet = acceptSet;
}

bool StateSetDio::isStartSet() const {
    return startSet;
}

void StateSetDio::setStartSet(bool startSet) {
    StateSetDio::startSet = startSet;
}

void StateSetDio::setTransitionFunction(string symbol, StateSetDio * to) {
    transition_function[symbol] = to;
}

StateSetDio * StateSetDio::transition(string symbol){
    return transition_function[symbol];
}

StateDio * StateSetDio::toState() {
    StateDio* s= new StateDio();
    s->setLabel(label);
    s->setAccepting(acceptSet);
    s->setStarting(startSet);
    return s;
}

bool StateSetDio::equivalent(StateDio *s) {
    if (s->getLabel()==this->label){
        return true;
    }
    return false;
}

const string &StateSetDio::getLabel() const {
    return label;
}



StateSetDio::StateSetDio() {}

void StateSetDio::setLabel(const string &label) {
    StateSetDio::label = label;
}

void StateSetDio::setSet(const vector<StateDio *> &set) {
    StateSetDio::set = set;
}

void StateSetDio::setEclose(string eps) {
    vector<StateDio*> temp;
    for (StateDio * p: set){
        for (StateDio *s: p->eclose(p, eps)){
            temp.push_back(s);
        }
    }
    this->setSet(temp);
    this->setLabel(createSetLabel(temp));
}



