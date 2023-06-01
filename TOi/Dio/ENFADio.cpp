//
// Created by dio on 9/04/2023.
//

#include "ENFADio.h"

ENFADio::ENFADio(const char *filename) : NFADio(filename) {
    eps=getConfiguration()["eps"];
}

DFADio ENFADio::mssc() {
    vector<StateDio*> states=getStates();
    vector<vector<StateDio*>> StateSets;
    for (StateDio* p: states){
        vector<StateDio*> temp=p->eclose(p, eps);
        StateSets.push_back(temp);
    }

    vector<StateDio*> s={getStartstate()};
    StateSetDio *emptySet= createEmptySet();
    bool reached_emptySet=false;
    StateSetDio* start= new StateSetDio(s);
    start->setStartSet(true);
    vector<StateSetDio*> visited;
    visited.push_back(start);
    start->setEclose(eps);


    for(int x=0 ; x<visited.size();x++) {
        StateSetDio *i = visited[x];

        for (auto symbol: getAlphabet()) {
            vector<StateDio *> temp{};
            vector<vector<StateDio*>> temp2{};

            for (StateDio *current_state: i->getSet()) {
                if ((current_state->transition(symbol).size() !=0) && current_state->transition(symbol)[0]!=NULL ){
                    temp2.push_back(current_state->transition(symbol));
                }
            }
            //add epsilon transitions to temp2
            int temp2size=temp2.size();
            for (int EcloseCounter=0; EcloseCounter<temp2size; EcloseCounter++){
                for(auto set: temp2[EcloseCounter]){
                    temp2[EcloseCounter]=set->eclose(set,eps);
                    if(EcloseCounter==temp2size){
                        break;
                    }
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

    StateDio* dfaStartstate;
    map<StateSetDio*,StateDio*> equivalent_state;
    for (StateSetDio* p : visited){
        StateDio* temp=p->toState();
        if(p->isStartSet()){
            temp->setStarting(true);
            dfaStartstate=temp;
        }
        dfa_states.push_back(temp);
        equivalent_state[p]=temp;
    }

    for (StateSetDio* p: visited)
        for(string symbol: getAlphabet()){
            equivalent_state[p]->setTransitionFunction(symbol,equivalent_state[p->transition(symbol)]);
        }
    for (StateSetDio* p: visited){
        delete p;
    }
    //delete emptySet;
    DFADio dfa=DFADio();
    dfa.setStates(dfa_states);
    dfa.setAlphabet(getAlphabet());
    dfa.setStartState(dfaStartstate);

    return dfa;
}

bool ENFADio::inVisited(vector <StateSetDio*> visited, vector<StateDio*> newset){
    for (auto set: visited) {
        if (set->equal(newset)) {
            return true;
        }
    }
    return false;
}

DFADio ENFADio::toDFA() {
    return mssc();
}

void ENFADio::printStats() {
    cout << "no_of_states=" << this->getStates().size() << endl;
    map <string,int> no_of_transitions;

    for (auto i:this->getStates()){
        map <string,vector<StateDio*>>transition_function=i->getTransitionFunction();
        for (auto p: transition_function){
            if(no_of_transitions.find(p.first)==no_of_transitions.end()){
                no_of_transitions[p.first]=p.second.size();
            } else{
                no_of_transitions[p.first]=no_of_transitions[p.first]+p.second.size();
            }
        }
    }
    pair<string, int>e;
    vector<pair<string, int>> temp{};

    for (auto i: no_of_transitions){
        if(i.first==eps){
            e.first=i.first;
            e.second=i.second;

        }
        else{
            pair<string, int>temp2 {i.first,i.second};
            temp.push_back(temp2);
        }
    }
    for (int i=0;i<temp.size();i++){
        if(i<temp.size()-1 && temp[i].first>temp[i+1].first){
            pair<string, int>temp2 = temp[i];
            temp[i]=temp[i+1];
            temp[i+1]=temp2;
            i=0;
        }
    }
    cout << "no_of_transitions[" << get<0>(e) << "]=" << get<1>(e) << endl;

    for (auto i: temp){
        cout << "no_of_transitions[" << i.first << "]=" << i.second << endl;
    }

    map <int,int> degree;
    vector<string> transitionSymbols=getAlphabet();
    transitionSymbols.push_back(eps);
    for(auto i:this->getStates()){
        int d=0;
        for(auto symbol: transitionSymbols){
            d+=i->transition(symbol).size();
        }
        if(degree.find(d)==degree.end()){
            degree[d]=1;
        } else{
            degree[d]++;
        }
    }

    for (auto i: degree){
        cout << "degree[" << i.first << "]=" << i.second << endl;
    }
}

ENFADio::ENFADio() {}

const string &ENFADio::getEps() const {
    return eps;
}

void ENFADio::setEps(const string &eps) {
    ENFADio::eps = eps;
}

bool ENFADio::accepts(string s) {
    return this->toDFA().accepts(s);
}

