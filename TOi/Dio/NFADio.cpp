//
// Created by dio on 29/03/2023.
//

#include "NFADio.h"

void NFADio::setStates(const vector<StateDio *> &states) {
    this->states=states;
}

void NFADio::setAlphabet(vector<string> a) {
    this->alphabet=a;
}
/*
bool NFADio::accepts(const string s) {
    return false;
}*/

void NFADio::setTransitionFunction(string from, string to, string input) {
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
    if (s!= nullptr){ //als s een nullptr is, is the state unreachable of een start state
        s->setTransitionFunction(input,destination);
    }
}


NFADio::NFADio() {}

NFADio::NFADio(const char* filename) {
    // inlezen uit file
    using json = nlohmann::json;


    ifstream input(filename);

    nlohmann::json j;
    input >> j;

    configuration=j;

    //alfabet bepalen
    vector <string> v;

    this->type=j["type"];

    for (int i = 0; i < j["alphabet"].size(); ++i) {
        v.push_back(j["alphabet"][i]);
    }
    this->setAlphabet(v);

    //States aanmaken en opslaan in vector "states"
    vector < StateDio * > states;
    for (int i = 0; i < j["states"].size(); ++i) {

        StateDio *s = new StateDio(j["states"][i]["name"]); //naam bepalen
        s->setAccepting(j["states"][i]["accepting"]); //accept state?
        s->setStarting(j["states"][i]["starting"]); //start state?
        if(s->isStarting()){
            startstate=s;
        }
        states.push_back(s);

    }
    //set states of NFADio
    this->setStates(states);
    for (int i = 0; i < j["transitions"].size() ; ++i) {

        this->setTransitionFunction(j["transitions"][i]["from"],j["transitions"][i]["to"],j["transitions"][i]["input"]);
    }
}


DFADio NFADio::SSC() {//subset constructie
    vector<StateDio*> s={startstate};
    StateSetDio *emptySet= createEmptySet();
    bool reached_emptySet=false;
    StateSetDio* start= new StateSetDio(s);
    start->setStartSet(true);
    vector<StateSetDio*> visited;
    visited.push_back(start);


    for(int x=0 ; x<visited.size();x++) {
        StateSetDio *i = visited[x];

        for (auto symbol: alphabet) {
            vector<StateDio *> temp{};
            vector<vector<StateDio*>> temp2{};
            for (StateDio *current_state: i->getSet()) {
                if ((current_state->transition(symbol).size() !=0) && current_state->transition(symbol)[0]!=NULL ){
                    temp2.push_back(current_state->transition(symbol));
                }
            }
            for (auto set: temp2)
                for(StateDio* pointer2: set){
                    int counter=0;
                    bool duplicate= false;
                    while(counter<temp.size()){
                        if (temp[counter]==pointer2){
                            duplicate= true;
                        }
                        counter++;
                    }
                    if (!duplicate){temp.push_back(pointer2);}
                }
            if (!inVisited(visited, temp) && temp.size()>0) {
                StateSetDio * p = new StateSetDio(temp);
                visited.push_back(p);
                i->setTransitionFunction(symbol,p);
            } else{
                bool transition_to_empty_set = true;
                for (StateSetDio * existing_set: visited){
                    if(existing_set->equal(temp)){
                        i->setTransitionFunction(symbol,existing_set);
                        transition_to_empty_set = false;
                    }
                }
                if (transition_to_empty_set){
                    i->setTransitionFunction(symbol,emptySet);
                    reached_emptySet=true;
                }
            }
        }
    }
    if (reached_emptySet){
        visited.push_back(emptySet);
    } else{
        delete emptySet;
    }
    vector<StateDio*> dfa_states;

    map<StateSetDio*,StateDio*> equivalent_state;
    for (StateSetDio* p : visited){
        StateDio* temp=p->toState();
        dfa_states.push_back(temp);
        equivalent_state[p]=temp;
    }

    for (StateSetDio* p: visited)
        for(string symbol: alphabet){
            equivalent_state[p]->setTransitionFunction(symbol,equivalent_state[p->transition(symbol)]);
        }
    for (StateSetDio* p: visited){
        delete p;
    }
    //delete emptySet;
    DFADio dfa=DFADio();
    dfa.setStates(dfa_states);
    dfa.setAlphabet(alphabet);
    return dfa;
}

DFADio NFADio::toDFA() {
  return SSC();
}

bool NFADio::inVisited(vector <StateSetDio*> visited, vector<StateDio*> newset){
    for (auto set: visited) {
        if (set->equal(newset)) {
            return true;
        }
    }
    return false;
}

/*
vector<vector<StateDio *>> NFADio::SCC(StateDio *state) {
    vector<StateDio *> * temp;
    for(auto symbol: alphabet){
        //temp->push_back(state->transition(symbol));
    }

    return vector<vector<StateDio *>>();
}*/

NFADio::~NFADio() {
    for (StateDio* state:states){
        delete state;
    }
}

StateSetDio *NFADio::createEmptySet() {
    StateSetDio * emptySet=new StateSetDio();
    vector<StateDio *> empty{};
    emptySet->setLabel("{}");
    emptySet->setAcceptSet(false);
    emptySet->setStartSet(false);
    for (string symbol: alphabet){
        emptySet->setTransitionFunction(symbol,emptySet);
    }
    return emptySet;
}



const vector<StateDio *> &NFADio::getStates() const {
    return states;
}

const json &NFADio::getConfiguration() const {
    return configuration;
}

StateDio *NFADio::getStartstate() const {
    return startstate;
}

const vector<string> &NFADio::getAlphabet() const {
    return alphabet;
}

const string &NFADio::getType() const {
    return type;
}

void NFADio::setStartstate(StateDio *startstate) {
    NFADio::startstate = startstate;
}

void NFADio::setType(const string &type) {
    NFADio::type = type;
}


