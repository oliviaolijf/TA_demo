//
// Created by dio on 27/02/2023.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include "DFADio.h"
#include "StateDio.h"
#include "string"
#include "json.hpp"

DFADio::DFADio(const char* a) {


    // inlezen uit file
    using json = nlohmann::json;

    ifstream input(a);

    nlohmann::json j;
    input >> j;

    //alfabet bepalen
    vector<string> v;

    for (int i = 0; i < j["alphabet"].size() ; ++i) {
        v.push_back(j["alphabet"][i]);
    }
    this->setAlphabet(v);

    //States aanmaken en opslaan in vector "states"
    vector<StateDio*> states;
    for (int i = 0; i < j["states"].size() ; ++i) {

        StateDio* s=new StateDio(j["states"][i]["name"]); //naam bepalen
        s->setAccepting(j["states"][i]["accepting"]); //accept state?
        s->setStarting(j["states"][i]["starting"]); //start state?
        if(j["states"][i]["starting"]){
            this->startState=s;
        }
        states.push_back(s);
    }

    //set states of DFADio
    this->setStates(states);
    for (int i = 0; i < j["transitions"].size() ; ++i) {

        this->setTransitionFunction(j["transitions"][i]["from"],j["transitions"][i]["to"],j["transitions"][i]["input"]);
    }
}

DFADio::DFADio(json j) {

    // inlezen uit file
    using json = nlohmann::json;


    //alfabet bepalen
    vector<string> v;

    for (int i = 0; i < j["alphabet"].size() ; ++i) {
        v.push_back(j["alphabet"][i]);
    }
    this->setAlphabet(v);

    //States aanmaken en opslaan in vector "states"
    vector<StateDio*> states;
    for (int i = 0; i < j["states"].size() ; ++i) {

        StateDio* s=new StateDio(j["states"][i]["name"]); //naam bepalen
        s->setAccepting(j["states"][i]["accepting"]); //accept state?
        s->setStarting(j["states"][i]["starting"]); //start state?
        if(j["states"][i]["starting"]){
            this->startState=s;
        }
        states.push_back(s);
    }

    //set states of DFADio
    this->setStates(states);
    for (int i = 0; i < j["transitions"].size() ; ++i) {

        this->setTransitionFunction(j["transitions"][i]["from"],j["transitions"][i]["to"],j["transitions"][i]["input"]);
    }
}


void DFADio::setAlphabet(vector<string> a) {
    for (int i=0; i<a.size();i++){
        alphabet.push_back(a[i]);
    }
}

bool DFADio::accepts(const string x) {
    StateDio *current = getStartState();


    string s = x;
    for (auto it: s) {
        bool valid_input= false;
        string input;
        for(auto i:alphabet){
            char p=*i.data();
            if(p==it){
                valid_input= true;
                input=i;
                break;
            }
        }
        if (valid_input== false) {
            return false;
        } else{
            current=(current->transition(input))[0];
        }
    }
    return current->isAccepting();
}



DFADio::~DFADio() {

    for (int i = 0 ; i<states.size(); i++){
        //delete states[i];
    }
}

void DFADio::setStates(const vector<StateDio *> &states) {
    DFADio::states = states;
}

void DFADio::setTransitionFunction(string from, string to, string input) {
    //instellen van transitie functie
    //from = vertrekstate, to=state van toekomen, input=transitiesymbool
    StateDio* s= nullptr;
    StateDio* destination= nullptr;

    for(auto i: states){
        if(from==i->getLabel()){
            s=i;
        }
        if(to==i->getLabel()){
            destination=i;
        }
    }
    s->setTransitionFunction(input,destination);

}

void DFADio::print() {
    json j;

    vector<int> s;

    json stas;

    for (StateDio * s:states){
        stas["name"]=s->getLabel();
        stas["starting"]=s->isStarting();
        stas["accepting"]=s->isAccepting();
        j["states"].push_back(stas);
    }

    json transitions;
    for (auto i: alphabet){

        for (StateDio * s:states){
            transitions["from"]=s->getLabel();
            transitions["input"]=i;
            transitions["to"]=(s->transition(i))[0]->getLabel();
            j["transitions"].push_back(transitions);
        }
    }

    j["type"] = "DFADio";
    j["alphabet"] = alphabet;
    cout << setw(4) << j << endl;
}
json DFADio::get_json_dfa() {
    json j;

    vector<int> s;

    json stas;

    for (StateDio * s:states){
        stas["name"]=s->getLabel();
        stas["starting"]=s->isStarting();
        stas["accepting"]=s->isAccepting();
        j["states"].push_back(stas);
    }

    json transitions;
    for (auto i: alphabet){

        for (StateDio * s:states){
            transitions["from"]=s->getLabel();
            transitions["input"]=i;
            transitions["to"]=(s->transition(i))[0]->getLabel();
            j["transitions"].push_back(transitions);
        }
    }

    j["type"] = "DFADio";
    j["alphabet"] = alphabet;
    return j;
}


DFADio::DFADio() {}

DFADio::DFADio(DFADio &dfa1, DFADio &dfa2, bool intersection) {
    //indien bool=true creër je de intersectie van dfa1 en dfa2
    //indien bool=false creër je de unie van dfa1 en dfa2

    //alphabet construction
    this->alphabet= dfa1.getAlphabet();
    for (auto symbol:dfa2.getAlphabet()){
        if (find(this->alphabet.begin(), this->alphabet.end(),symbol)==this->alphabet.end()){
            this->alphabet.push_back(symbol);
        }
    }

    vector<StateDio*> st{dfa1.getStartState(), dfa2.getStartState()};
    StateSetDio* start = new StateSetDio(st, true);
    start->setStartSet(true);
    vector<StateSetDio*> visited{start};


    for (int i=0; i<visited.size(); i++){
        for (auto symbol:alphabet){
            createProductStateSets(symbol,visited[i],visited);
        }
    }




    map <StateSetDio*,StateDio*> equivalent_states;
    map <vector<StateDio*>,StateSetDio*> equivalent_sets;
    //setaccept states and startstates
    for (auto set : visited){
        vector<StateDio*>temp=set->getSet();
        for (auto state : temp){
            if (!intersection && state->isAccepting()){
                set->setAcceptSet(true);
                break;
            } else if(intersection){
                set->setAcceptSet(true);
                if(!state->isAccepting()){
                    set->setAcceptSet(false);
                    break;
                }
            }
        }
    }
    for (auto set: visited){
        StateDio * temp=set->toState();
        if(set->isStartSet()){
            temp->setStarting(true);
            this->setStartState(temp);
        }
        this->states.push_back(temp);
        equivalent_states[set]=temp;
        equivalent_sets[set->getSet()]=set;
    }



    for (auto symbol: alphabet)
        for (auto stateSet: visited){
            equivalent_states[stateSet]->setTransitionFunction(symbol,equivalent_states[stateSet->transition(symbol)]);
        }
    for (StateSetDio* s:visited){
        delete s;
    }
}

void DFADio::createProductStateSets(string symbol, StateSetDio* current, vector<StateSetDio*> &visited){
    vector<StateDio*> destinations{};

    //eerste state aan destinations toevoegen
    if (current->getSet().empty()== false){
        destinations=current->getSet()[0]->transition(symbol);
    }
    //tweede en volgende states aan destinations toevoegen
    for (auto stateset: current->getSet())
        for (auto state: stateset->transition(symbol)){
            if (find(destinations.begin(), destinations.end(),state)==destinations.end() && state!= NULL){
                destinations.push_back(state);
            }
    }
    for (auto set: visited){
        int counter=destinations.size();
        if (destinations.size()==set->getSet().size()){
            for (StateDio* state:set->getSet()){
                if (find(destinations.begin(), destinations.end(),state)!=destinations.end()){
                    counter-=1;
                }
                if (counter==0){
                    current->setTransitionFunction(symbol,set);
                    return;
            }
        }
    }
    }
    if (destinations.empty()== false && destinations[0]!=NULL){
        StateSetDio * temp =new StateSetDio(destinations, true);
        current->setTransitionFunction(symbol,temp);
        visited.push_back(temp);
        createProductStateSets(symbol,temp,visited);
    }
}

const vector<StateDio *> &DFADio::getStates() const {
    return states;
}

const vector<string> &DFADio::getAlphabet() const {
    return alphabet;
}

StateDio *DFADio::getStartState() const {
    return startState;
}

void DFADio::changeToComplementDFA() {
    for(auto state: this->states){
        if(state->isAccepting()){
            state->setAccepting(false);
        }else{
            state->setAccepting(true);
        }
    }
}

void DFADio::setStartState(StateDio *startState) {
    DFADio::startState = startState;
}
