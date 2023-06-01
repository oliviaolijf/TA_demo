//
// Created by Jonat on 23/04/2023.
//

#include "NFAJonathan.h"


NFAJonathan::NFAJonathan(string filePath) {

    ifstream input(filePath);
    json j;
    input >> j;

    string automataType = j["type"];

    // Set alphabet
    vector<string> temp;
    for(auto symbol : j["alphabet"]) {
        temp.push_back(symbol);
    }
    setAlphabet(temp);

    // make states
    for(auto s : j["states"]){
        makeState(s["accepting"],s["starting"],s["name"]);
    }

    // make transitions
    for(auto t : j["transitions"]){
        addTransition(t["from"],t["to"],t["input"]);
    }





//    setAlphabet(vector<string> {"1","0"});
//    makeState(true,true,"S0");
//    makeState(false,false,"S1");
//    makeState(false,false,"S2");
//
//    addTransition("S0","S0","0");
//    addTransition("S0","S1","1");
//    addTransition("S1","S0","1");
//    addTransition("S1","S2","0");
//    addTransition("S2","S1","0");
//    addTransition("S2","S2","1");

}

bool NFAJonathan::setAlphabet(vector<std::string> symbols) {
    NFAJonathan::alphabet = symbols;
    return true;
}

bool NFAJonathan::makeState(bool isFinal, bool isFirst, string stateName) {
    StateJonathan* n = new StateJonathan(isFinal, isFirst, stateName);
    NFAJonathan::states.push_back(n);
    if(isFirst and NFAJonathan::startState == nullptr){
        NFAJonathan::startState = n;
    }
    if(isFinal){
        NFAJonathan::finalStates.push_back(n);
    }
    return true;
}

bool NFAJonathan::addTransition(string from, string to, string symbol) {
    StateJonathan* f = getState(from);
    StateJonathan* t = getState(to);


    if(inAlphabet(symbol)){
        transitions.push_back(new TransitionJonathan(symbol, f, t));
        return true;
    } else{
        return false;
    }
}

bool NFAJonathan::inAlphabet(std::string symbol) {
    for(auto s : alphabet){
        if(symbol == s){
            return true;
        }
    }
    return false;
}

StateJonathan* NFAJonathan::getState(std::string symbol) {
    for(auto s : states){
        if(s->getName() == symbol){
            return s;
        }
    }
    return nullptr;
}

bool NFAJonathan::accepts(std::string language) {
    StateJonathan* current = startState;
    for(auto s : language){
        for(auto t : transitions){
            if(current == t->getFrom() and string(1,s) == t->getSymbol()){
                current = t->getTo();
                break;
            }
        }
    }
    for(auto f : finalStates){
        if(f == current){
            return true;
        }
    }
    return false;
}


void NFAJonathan::print() {
    json j;
    json d;

    for(auto state: states){
        d["name"] =state->getName();
        d["starting"] = state->getFirst();
        d["accepting"] = state->getFinal();
        j["states"].push_back(d);
    }

    json t;

    for(auto transition : transitions){
        t["from"]=transition->getFrom()->getName();
        t["input"]=transition->getSymbol();
        t["to"]=transition->getTo()->getName();
        j["transitions"].push_back(t);
    }
    j["type"] = "NFAJonathan";
    j["alphabet"] = alphabet;
    cout << setw(4) << j << endl;

}

vector<string> NFAJonathan::splitString(string line){
    vector<string> temp{};
    string tempString{};
    for(auto x : line){
        if(x != ','){
            tempString = tempString + x;
        }else{
            temp.push_back(tempString);
            tempString.clear();
        }
    }
    temp.push_back(tempString);
    return temp;
}

bool NFAJonathan::inVector(vector<StateJonathan*> vec, string name){
    for(auto n : vec){
        if(n->getName() == name){
            return true;
        }
    }
    return false;
}

DFAJonathan NFAJonathan::toDFA() {
    DFAJonathan *dfa = new DFAJonathan();
    dfa->setAlphabet(alphabet);
    // create startstate
    toDFAHelper(dfa,startState);
    return *dfa;

}

void NFAJonathan::toDFAHelper(DFAJonathan *dfa, StateJonathan* state){
    dfa->makeState(state->getFinal(),state->getFirst(),state->getName());
    for(auto symbol : alphabet){
        vector<StateJonathan*> stats;
        for(auto n : splitString(state->getName())){
            for(auto transition: transitions) {
                if (symbol == transition->getSymbol() and transition->getFrom()->getName() == n and !inVector(stats,transition->getTo()->getName())) {
                    stats.push_back(transition->getTo());
                }
            }
        }

        bool fin = false;
        bool fir = false;
        string name;
        int count = 0;
        for(auto s : stats){
            if(s->getFinal()){
                fin = true;
            }
            if(count != stats.size()-1){
                name = name + s->getName() + ",";
            } else{
                name = name + s->getName();
            }
            count ++;
        }
        name = orderAlphabeticly(name);
        StateJonathan* newState = new StateJonathan(fin, fir, name);
        if(!dfa->stateExists(name)){

            toDFAHelper(dfa,newState);
        }
        dfa->addTransition(state->getName(),newState->getName(),symbol);
    }
}

string NFAJonathan::orderAlphabeticly(string line) {
    vector<string> splitLine = splitString(line);
    vector<string> temp(splitLine.size(),"");

    for(auto n : splitLine){
        int count =splitLine.size()-1;
        for(auto x : splitLine){
            if(n[0] < x[0]){
                count --;
            }
        }
        temp[count] = n;
    }
    string tmpString{};
    for(auto h : temp){
        if(h != temp[temp.size()-1]){
            tmpString = tmpString + h + ",";
        } else{
            tmpString = tmpString + h;
        }
    }
    return tmpString;
}



