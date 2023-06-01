//
// Created by Jonathan on 01/03/2023.
//

#include "DFAJonathan.h"

DFAJonathan::DFAJonathan() {}

DFAJonathan::DFAJonathan(string filePath) {

    ifstream input(filePath);
    json j{};
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

}

DFAJonathan::DFAJonathan(json j) {

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

}

bool DFAJonathan::setAlphabet(vector<std::string> symbols) {
    DFAJonathan::alphabet = symbols;
    return true;
}

bool DFAJonathan::makeState(bool isFinal, bool isFirst, string stateName) {
    StateJonathan* n = new StateJonathan(isFinal, isFirst, stateName);
    DFAJonathan::states.push_back(n);
    if(isFirst and DFAJonathan::startState == nullptr){
        DFAJonathan::startState = n;
    }
    if(isFinal){
        DFAJonathan::finalStates.push_back(n);
    }
    return true;
}

bool DFAJonathan::addTransition(string from, string to, string symbol) {
    StateJonathan* f = getState(from);
    StateJonathan* t = getState(to);


    if(inAlphabet(symbol)){
        transitions.push_back(new TransitionJonathan(symbol, f, t));
        return true;
    } else{
        return false;
    }
}

bool DFAJonathan::inAlphabet(std::string symbol) {
    for(auto s : alphabet){
        if(symbol == s){
            return true;
        }
    }
    return false;
}

StateJonathan* DFAJonathan::getState(std::string symbol) {
    for(auto s : states){
        if(s->getName() == symbol){
            return s;
        }
    }
    return nullptr;
}

bool DFAJonathan::accepts(std::string language) {
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


void DFAJonathan::print() {

    json j;
    json d;

    for(auto state: states){
        string name ="";
        for(int x =0 ; x < splitString( state->getName()).size() ; x++){
            if(splitString(state->getName())[x] == splitString( state->getName())[splitString( state->getName()).size()-1]){
                name += splitString(state->getName())[x];
            }else{
                name += splitString(state->getName())[x] + ", ";
            }
        }

        d["name"] ="{" + name + "}";
        d["starting"] = state->getFirst();
        d["accepting"] = state->getFinal();
        j["states"].push_back(d);
    }

    json t;

    for(auto transition : transitions){
        string from ="";
        for(int x =0 ; x < splitString( transition->getFrom()->getName()).size() ; x++){
            if(splitString(transition->getFrom()->getName())[x] == splitString( transition->getFrom()->getName())[splitString( transition->getFrom()->getName()).size()-1]){
                from += splitString(transition->getFrom()->getName())[x];
            }else{
                from += splitString(transition->getFrom()->getName())[x] + ", ";
            }
        }

        string to ="";
        for(int x =0 ; x < splitString( transition->getTo()->getName()).size() ; x++){
            if(splitString(transition->getTo()->getName())[x] == splitString( transition->getTo()->getName())[splitString( transition->getTo()->getName()).size()-1]){
                to += splitString(transition->getTo()->getName())[x];
            }else{
                to += splitString(transition->getTo()->getName())[x] + ", ";
            }
        }

        t["from"]= "{" + from+ "}";
        t["input"]=transition->getSymbol();
        t["to"]="{" + to+ "}";
        j["transitions"].push_back(t);
    }
    j["type"] = "DFAJonathan";
    j["alphabet"] = alphabet;
    cout << setw(4) << j << endl;
}

json DFAJonathan::get_json_dfa(){
    json j;
    json d;

    for(auto state: states){
        string name ="";
        for(int x =0 ; x < splitString( state->getName()).size() ; x++){
            if(splitString(state->getName())[x] == splitString( state->getName())[splitString( state->getName()).size()-1]){
                name += splitString(state->getName())[x];
            }else{
                name += splitString(state->getName())[x] + ", ";
            }
        }

        d["name"] ="{" + name + "}";
        d["starting"] = state->getFirst();
        d["accepting"] = state->getFinal();
        j["states"].push_back(d);
    }

    json t;

    for(auto transition : transitions){
        string from ="";
        for(int x =0 ; x < splitString( transition->getFrom()->getName()).size() ; x++){
            if(splitString(transition->getFrom()->getName())[x] == splitString( transition->getFrom()->getName())[splitString( transition->getFrom()->getName()).size()-1]){
                from += splitString(transition->getFrom()->getName())[x];
            }else{
                from += splitString(transition->getFrom()->getName())[x] + ", ";
            }
        }

        string to ="";
        for(int x =0 ; x < splitString( transition->getTo()->getName()).size() ; x++){
            if(splitString(transition->getTo()->getName())[x] == splitString( transition->getTo()->getName())[splitString( transition->getTo()->getName()).size()-1]){
                to += splitString(transition->getTo()->getName())[x];
            }else{
                to += splitString(transition->getTo()->getName())[x] + ", ";
            }
        }

        t["from"]= "{" + from+ "}";
        t["input"]=transition->getSymbol();
        t["to"]="{" + to+ "}";
        j["transitions"].push_back(t);
    }
    j["type"] = "DFAJonathan";
    j["alphabet"] = alphabet;
    return j;
}


bool DFAJonathan::stateExists(string name) {
    for(auto state : states){
        if(state->getName() == name){
            return true;
        }
    }
    return false;
}

vector<string> DFAJonathan::splitString(string line){
    vector<string> temp{};
    string tempString{};
    for(auto x : line){
        if(x != '%'){
            tempString = tempString + x;
        }else{
            temp.push_back(tempString);
            tempString.clear();
        }
    }
    temp.push_back(tempString);
    return temp;
}

void DFAJonathan::setTable(vector<vector<char>> table) {
    DFAJonathan::table = table;
}

int DFAJonathan::getAllMarked(vector<vector<char>> tb) {
    int count = 0;
    for(auto t : tb){
        for(auto x : t){
            if(x == 'X'){
                count ++;
            }
        }
    }
    return count;
}

DFAJonathan DFAJonathan::minimize() {
    //char tble[states.size()][states.size()];
    vector<vector<char> > tble(states.size(),vector<char>(states.size()));
    int count = 0;
    for(int x = 0; x < states.size();x++){
        for(int y = 0; y < states.size();y++){
            if(y < count){
                tble[x][y] = '-';
            }else{
                tble[x][y] = 'G';
            }
        }
        count ++;
    }
    vector<string> orderdStates = getSateNames();

    for(int n = 0 ; n < orderdStates.size(); n++){
        if(getState(orderdStates[n])->getFinal()){
            for(int g = 0 ; g < orderdStates.size(); g++){
                if(!getState(orderdStates[g])->getFinal() and tble[n][g] != 'G'){
                    tble[n][g] = 'X';
                }
            }
        }else{
            for(int g = 0 ; g < orderdStates.size(); g++){
                if(getState(orderdStates[g])->getFinal() and tble[n][g] != 'G'){
                    tble[n][g] = 'X';
                }
            }
        }

    }
    DFAJonathan newwDFA =  *this;
    map<string,string> modPairs{};
    vector<string> stringPairs;
    for(auto p : modPairs){
        stringPairs.push_back(orderAlphabeticly(p.first + "%"+ p.second));
    }


    vector<string > finalPairs;

    for(auto p: stringPairs){
        int count = 0;
        for(auto c : stringPairs){
            if(p == c){
                count ++;
            }
        }
        if(count == splitString(p).size() and !inVector(finalPairs,p)){
            finalPairs.push_back(p);
        }
    }

    string stw = "";
    for(auto b : finalPairs){
        if(stw == ""){
            stw += b;
        }else{
            stw +="%"+ b;
        }
    }

    for(auto c : getSateNames()){
        int count = 0;
        for(auto a : splitString(stw)){
            if(c == a){
                count = 1;
            }
        }
        if(count != 1){
            finalPairs.push_back(c);
        }
    }



    DFAJonathan* newDFA = new DFAJonathan();
    newDFA->alphabet = alphabet;
    for(auto x : finalPairs){
        bool fnl = false;
        bool frst = false;
        for(auto y : splitString(x)){
            if(getState(y)->getFinal()){
                 fnl = true;
            }
            if(getState(y)->getFirst()){
                 frst = true;
            }
        }
        newDFA->makeState(fnl,frst,x);
    }

    for(auto x : finalPairs){
        for(auto a : alphabet){
            for(auto t : transitions){
                if(t->getSymbol() == a and t->getFrom()->getName() ==splitString(x)[0]){
                    newDFA->addTransition(x,stateContaining(t->getTo()->getName(),newDFA),a);
                }
            }
        }
    }



    newDFA->setTable(tble);
    DFAJonathan::table = tble;


    return newwDFA;
}

string DFAJonathan::stateContaining(string line, DFAJonathan* df) {
    for( auto n : df->states){
        if (n->getName().find(line) != std::string::npos) {
            return df->getState(n->getName())->getName();
        }
    }
    return "NULDDDL";
}


int DFAJonathan::getStateOrder(StateJonathan *st, vector<string> orderdedStates) {
    for(int x = 0; x < orderdedStates.size() ; x++){
        if( orderdedStates[x] == st->getName()){
            return x;
        }
    }
    return 404;
}


//vector<vector<string>> DFAJonathan::getTransitionTable() {
//
//    vector<vector<string> > temp(states.size(),vector<string>(alphabet.size()));
//    for(int x = 0; x < getSateNames().size(); x++){
//        for(int y = 0; y < alphabet.size(); y++){
//            for(auto t : transitions){
//                if(t->getFrom()->getName() == getSateNames()[x] and t->getSymbol() == alphabet[y]){
//                    temp[x][y] = t->getTo()->getName();
//                }
//            }
//        }
//    }
//    return temp;
//}

#include <unordered_map>
// ...

vector<vector<string>> DFAJonathan::getTransitionTable() {
    vector<vector<string>> temp(states.size(), vector<string>(alphabet.size()));

    // Create a hash table to store transitions for efficient lookup
    unordered_map<string, unordered_map<string, string>> transitionMap;
    for (const auto& t : transitions) {
        transitionMap[t->getFrom()->getName()][t->getSymbol()] = t->getTo()->getName();
    }

    for (int x = 0; x < getSateNames().size(); x++) {
        for (int y = 0; y < alphabet.size(); y++) {
            const string fromStateName = getSateNames()[x];
            const string symbol = alphabet[y];

            // Lookup the transition in the hash table
            auto it = transitionMap.find(fromStateName);
            if (it != transitionMap.end()) {
                const auto& transitionsFromState = it->second;
                auto transitionIt = transitionsFromState.find(symbol);
                if (transitionIt != transitionsFromState.end()) {
                    temp[x][y] = transitionIt->second;
                }
            }
        }
    }

    return temp;
}


vector<int> DFAJonathan::findPairsHelper(string find, vector<vector<string> > table, int row) {
    vector<int> result{};
    for( int startColumn = 0; startColumn < table.size(); startColumn++) {
        if(table[startColumn][row] == find){
            result.push_back(startColumn);
        }
    }
    return result;
}

vector<string> DFAJonathan::findPairs(StateJonathan* st1, StateJonathan* st2) {
    vector<string> uniquePairs{};
    vector<string> stNames = getSateNames();


    vector<vector<string> >tTbale = getTransitionTable();
    string find1 = st1->getName();
    string find2 = st2->getName();

    for(int x = 0 ; x < alphabet.size(); x++) {
        for (int y = 0; y < tTbale.size(); y++) {
            if(tTbale[y][x] == find1){
                int count = 0;
                vector<int>  helperResult = findPairsHelper(find2,tTbale,x);
                for(auto a : helperResult){
                    uniquePairs.push_back(getState(stNames[y])->getName() + "%" + "2" + "%"  + getState(stNames[a])->getName() +"%" +alphabet[x]);
                }
            } else if(tTbale[y][x] == find2){
                vector<int> helperResult = findPairsHelper(find1,tTbale,x);
                for(auto a : helperResult){
                    uniquePairs.push_back(getState(stNames[y])->getName() + "%" + "2" + "%"  + getState(stNames[a])->getName() +"%" +alphabet[x]);
                }
            }
        }
    }
    return uniquePairs;

}

bool DFAJonathan::inVector(vector<string> vec, string name) {
    for(auto n : vec){
        if(name == n){
            return true;
        }
    }
    return false;
}

vector<string> DFAJonathan::getSateNames() {
    int count = 0;
    string name = "";
    for(auto s : states){

        if(count != states.size()-1){
            name = name + s->getName() + "%";
        } else{
            name = name + s->getName();
        }
        count ++;
    }
    string line = name;
    vector<string> splitLine = splitString(line);
    vector<string> temp(splitLine.size(),"");

    for(auto n : splitLine){
        int count =splitLine.size()-1;
        for(auto x : splitLine){
            if(n[3] < x[3]){
                count --;
            }
        }
        temp[count] = n;
    }
    vector<string> tmpString{};
    for(auto h : temp){
        tmpString.push_back(h);
    }
    //return tmpString;
    return splitLine;
}


string DFAJonathan::orderAlphabeticly(string line) {
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

void DFAJonathan::printTable() {
    for(int x = 1; x < getSateNames().size(); x ++){
        cout << getSateNames()[x] + "   ";
        for(int y = 0; y < x; y++) {
            cout << table[x][y];
            cout << "   ";
        }
        cout << endl;
    }
    cout << "    ";
    for(int x = 0; x < getSateNames().size() -1; x ++){
        cout << getSateNames()[x] + "   ";
    }
    cout << endl;

}





