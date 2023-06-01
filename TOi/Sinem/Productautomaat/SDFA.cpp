//
// Created by Sinem.E on 30/04/2023.
//

#include "SDFA.h"

SDFA::SDFA() {
}

SDFA::SDFA(string filename) {
    dfaConfig = parseJson(filename);
}

SDFA::SDFA(SDFA dfa1, SDFA dfa2, bool type) {
    productType = type ;
    product(dfa1, dfa2);
}

void SDFA::print() {
  dfaConfig.print() ;
}

DFAConfig SDFA::parseJson(string filename) {

    ifstream input(filename);

    json j;
    input >> j;

    string type = j["type"];
    dfaConfig.setType(type);

    for (string alphabet:j["alphabet"]) {
        dfaConfig.addAlphabet(alphabet);
    }

    for (auto state:j["states"]) {
        State *newState = new State();
        string name = state["name"];
        newState->setName(name);

        if (state["starting"] == true) {
            newState->setStart(true);

            string start = state["name"];
            dfaConfig.setStartState(start);
        }
        if (state["accepting"] == true) {
            newState->setAccept(true);

            string accept = state["name"];
            dfaConfig.addFinalState(accept);
        }
        dfaConfig.addState(newState);
    }

    for(auto transition:j["transitions"]){
        Transition *newTransition = new Transition();
        string from = transition["from"];
        string to = transition["to"];
        string input = transition["input"];

        newTransition->setFrom(from);
        newTransition->setTo(to);
        newTransition->setInput(input);

        dfaConfig.addTransitionsDFA(newTransition);
    }
    return dfaConfig;
}

DFAConfig SDFA::product(SDFA dfa1, SDFA dfa2) {
    // set type
    dfaConfig.setType("SDFA");
    // set alphabet
    dfaConfig.setAlphabet(dfa1.getDfaConfig().getAlphabet());
    //
    string beginStateName1 = dfa1.getDfaConfig().getStartState();
    string beginStateName2 = dfa2.getDfaConfig().getStartState();
    string beginStateName = makeStateName(beginStateName1,beginStateName2) ;
    dfaConfig.setStartState( beginStateName1 ) ;

    // Add the start nere
    // Then call FindNext() recursivelu to add others
    State *beginState = new State();
    beginState->setName(beginStateName) ;
    beginState->setStart(true) ;
    // Accepting &

    bool final1 = dfa1.isEndState(beginStateName1) ;
    bool final2 = dfa2.isEndState(beginStateName2) ;
    if (productType){
        if( final1 && final2){
            beginState->setAccept(true) ;
            dfaConfig.addFinalState(beginStateName);
        }
    } else {
        if( final1 || final2){
            beginState->setAccept(true) ;
            dfaConfig.addFinalState(beginStateName);
        }
    }

    dfaConfig.addState(beginState);

    // AddNext ()
    addNext(dfa1, beginStateName1, dfa2, beginStateName2);

    return DFAConfig();
}

const DFAConfig &SDFA::getDfaConfig() const {
    return dfaConfig;
}

string SDFA::getToStateName(string fromStateName, string input) {
    vector<Transition *> transitionsOfNFA = dfaConfig.getTransitions();
    for (auto transitionIter = transitionsOfNFA.begin();
         transitionIter != transitionsOfNFA.end(); transitionIter++) {
        // From AND input
        if ((fromStateName == (*transitionIter)->getFrom()) && ((*transitionIter)->getInput() == input)) {
            return (*transitionIter)->getTo() ;
        }
    }

    return "NOT_FOUND";
}

string SDFA::makeStateName(string stateName1, string stateName2) {
    return  "(" + stateName1 +"," + stateName2 + ")" ;
}

void SDFA::addNext(SDFA dfa1, string currentStateOfDFA1, SDFA dfa2, string currentStteOfDFA2) {

    for (string input: dfaConfig.getAlphabet()) {

        //  Call Recursively until Final state
        string nextState1 = dfa1.getToStateName(currentStateOfDFA1, input);
        string nextState2 = dfa2.getToStateName(currentStteOfDFA2, input);
        string nextStateName = makeStateName(nextState1, nextState2);

        // Add transition
        Transition *newTransition = new Transition();
        string from = makeStateName(currentStateOfDFA1, currentStteOfDFA2);
        newTransition->setFrom(from);
        newTransition->setTo(nextStateName);
        newTransition->setInput(input);
        dfaConfig.addTransitionsDFA(newTransition);


        if (!isExist(nextStateName)) {
            // Add State
            State *newState = new State();
            // Name
            newState->setName(nextStateName);
            // Accepting
            //
            bool final1 = dfa1.isEndState(nextState1);
            bool final2 = dfa2.isEndState(nextState2);

            if (productType) {
                if (final1 && final2) {
                    newState->setAccept(true);
                    dfaConfig.addFinalState(nextStateName);
                }
            } else {
                if (final1 || final2) {
                    newState->setAccept(true);
                    dfaConfig.addFinalState(nextStateName);
                }
            }

            dfaConfig.addState(newState);

            // Call Recursive
            addNext(dfa1, nextState1, dfa2, nextState2);
            //
        }
    }
}

bool SDFA::isExist(string stateName) {
    map<string, State *>::iterator iter = dfaConfig.getStates().find(stateName);
    if (iter != dfaConfig.getStates().end()) {
            return true ;
    }
    return false;
}

bool SDFA::isEndState(string stateName) {
    for (string state: dfaConfig.getFinalStates()) {
        if (state == stateName)
            return true;
    }
    return false;
}


