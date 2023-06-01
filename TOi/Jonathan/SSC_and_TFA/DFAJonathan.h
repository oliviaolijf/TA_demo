//
// Created by Jonathan on 01/03/2023.
//

#ifndef ING_1_DFA_H
#define ING_1_DFA_H
#include <fstream>
#include <iomanip>
#include <iostream>
#include "StateJonathan.h"
#include "TransitionJonathan.h"
#include "vector"
#include "json.hpp"
#include <iomanip>
#include "map"
using json = nlohmann::json;
using namespace std;


class DFAJonathan {
private:
    vector<string> alphabet;
    vector<StateJonathan*> states{};
    vector<TransitionJonathan*> transitions{};
    StateJonathan* startState{};
    vector<StateJonathan*> finalStates;
    vector<vector<char> > table{};


public:
    bool operator == (DFAJonathan eq1){
        //eq1.minimize()
        // minimize();
        for(auto x : eq1.states){
            states.push_back(x);
        }
        for(auto t : eq1.transitions){
            transitions.push_back(t);
        }
        minimize();
        printTable();
        vector<int> check{};
        for(int x = 0; x < table.size(); x++){
            if(getState(getSateNames()[x])->getFirst()){
                check.push_back(x);
            }
        }
        if(table[check[0]][check[1]] == 'X') {
            return false;
        }else{
            return true;
        }



    };

    DFAJonathan();

    DFAJonathan(string filePath);

    DFAJonathan(json j);

    int getAllMarked(vector<vector<char> > tb);

    bool setAlphabet(vector<string> symbols);

    bool makeState(bool isFinal, bool isFirst, string stateName);

    bool addTransition(string from, string to,string symbol);

    bool inAlphabet(string symbol);

    StateJonathan* getState(string symbol);

    bool accepts(string language);

    bool stateExists(string name);

    vector<string> splitString(string line);

    void print();

    json get_json_dfa();

    DFAJonathan minimize();

    void printTable();

    vector<string> getSateNames();

    vector<string> findPairs(StateJonathan* st1, StateJonathan* st2);

    bool inVector(vector<string> state, string name);

    int getStateOrder(StateJonathan* st, vector<string> orderdedStates);


    string orderAlphabeticly(string line);

    string stateContaining(string line, DFAJonathan* df);

    void setTable(vector<vector<char> > table);

    vector<vector<string> > getTransitionTable();

    vector<int> findPairsHelper(string find,vector<vector<string> > table,int row);

};


#endif //ING_1_DFA_H
