//
// Created by Sinem.E on 21/04/2023.
//

#include "SNFA.h"

SNFA::SNFA() {}

SNFA::SNFA(string filename) {
    parseJson(filename);
}

NFAConfig SNFA::parseJson(string filename) {

    ifstream input(filename);

    json j;
    input >> j;

    string type = j["type"];
    config.setType(type);

    for (string alphabet:j["alphabet"]) {
        config.setAlphabet(alphabet);
    }

    for (auto state:j["states"]) {
        State *newState = new State();
        string name = state["name"];
        newState->setName(name);

        if (state["starting"] == true) {
            newState->setStart(true);

            string start = state["name"];
            config.setStartState(start);
        }
        if (state["accepting"] == true) {
            newState->setAccept(true);

            string accept = state["name"];
            config.setFinalStates(accept);
        }
        config.addToStates(newState);
    }

    for(auto transition:j["transitions"]){
        Transition *newTransition = new Transition();
        string from = transition["from"];
        string to = transition["to"];
        string input = transition["input"];

        newTransition->setFrom(from);
        newTransition->setTo(to);
        newTransition->setInput(input);

        config.addTransitionsNFA(newTransition);
    }
    return config;
}



ToDFAConfig SNFA::toDFA() {
    // set type
    todfa.setType("ODFA");
    // set alphabet
    todfa.setAlphabet(config.getAlphabet());

    vector<string> startStateV;
    // set start state
    string beginStateName = config.getStartState();
    // Start with Begin State
    // Find and Copy Begin
    //
    auto findStateIter = config.getStates().find(beginStateName);
    if (findStateIter != config.getStates().end()) {
        State* newDFAstate = new State();

        State* beginState = findStateIter->second;
        newDFAstate->setName("{" + beginState->getName() + "}");

        newDFAstate->setStart(beginState->isStart());
        newDFAstate->setAccept(beginState->isAccept());

        todfa.addState(newDFAstate);
        startStateV.push_back(beginState->getName());
    }
    //
    // Other states now
    // todo death state ?
    map<string,vector<string>> currentStates;
   transitionsOfNFA(startStateV);

    return todfa;
}

bool SNFA::isExist(string name) {
    map<string, State *>::iterator iter = todfa.getStates().find(name);
    if (iter != todfa.getStates().end()) {
        return true ;
    }
    return false;
}

bool SNFA::transitionsOfNFA( vector<string> currentStates) {
    map<string, vector<string>> tmpNextStatesName;
    map<string, vector<string>> nextStatesName;

    // Every State Iterate
    for (string currentState: currentStates) {
        //T
        // Iterate for Every Input
        for (string input: todfa.getAlphabet()) {
            // Find (By Iteration) for this State for this Input
            vector<Transition *> transitionsOfNFA = config.getTransitions();
            // {a,b,c}
            //Xfor (string subState: currentState) {
            // get  each transitions and find the next State for each input
            for (auto transitionIter = transitionsOfNFA.begin();
                 transitionIter != transitionsOfNFA.end(); transitionIter++) {
                // From AND input
                if ((currentState == (*transitionIter)->getFrom()) && ((*transitionIter)->getInput() == input)) {
                    // Check the state for each input
                    //  Add to Temp Map
                    map<string, vector<string>>::iterator findDfaVectorIter;
                    findDfaVectorIter = tmpNextStatesName.find(input);

                    if (findDfaVectorIter == tmpNextStatesName.end()) {
                        vector<string> dfaStateVector;
                        dfaStateVector.push_back((*transitionIter)->getTo());
                        tmpNextStatesName[input] = dfaStateVector;

                    } else {
                        vector<string> dfaStateVector = findDfaVectorIter->second;
                        //duplicate check
                        bool add = true;
                        for (string t: dfaStateVector) {
                            if (t == (*transitionIter)->getTo()) {
                                add = false;
                            }
                        }
                        if (add) {
                            dfaStateVector.push_back((*transitionIter)->getTo());
                        }
                        tmpNextStatesName[input] = dfaStateVector;
                    }
                }
            }
        }
    }
    // Next Transitions/States are in statesForAllinputs map
    auto stateVectorsMapIter = tmpNextStatesName.begin();
    while (stateVectorsMapIter != tmpNextStatesName.end()) {

        string input = stateVectorsMapIter->first;
        vector<string> dfaStateVector = stateVectorsMapIter->second;
        string dfaStateName = todfa.makeString(dfaStateVector);

        // check if it is already in the States map
        // Add to States
        // Add to Transitions
        // Add to  nextStatesMap to process recursively
        bool isIn = isExist(dfaStateName);

        // Add Transitions
        Transition *newTransition = new Transition();
        string from = todfa.makeString(currentStates);
        string to = dfaStateName;
        newTransition->setTo(to);
        newTransition->setFrom(from);
        newTransition->setInput(input);
        todfa.addTransitionsDFA(newTransition);

        if (!isIn) {
            // Add state
            State *newDFAstate = new State();
            newDFAstate->setName(dfaStateName);
            // Accepting
            map<string, State *>::iterator itFindState = todfa.getStates().find(dfaStateName);
            if (itFindState == todfa.getStates().end()) {
                for (string currentState: dfaStateVector) {
                    for (string endState: config.getFinalStates()) {
                        if (currentState == endState) {
                            newDFAstate->setAccept(true);
                        }
                    }
                }
            }
            todfa.addState(newDFAstate);
            // call recursive
            transitionsOfNFA(dfaStateVector);
        }
        stateVectorsMapIter++;
    }
    return true;
}