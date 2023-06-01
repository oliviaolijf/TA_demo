#include "DatabaseUtils.h"

ODFA toODFA(DFADio dfa_dio) {
    ODFA odfa;
    odfa.setAlphabet(dfa_dio.getAlphabet());
    vector<string> states;
    vector<string> finalstates;
    string startstate;
    map<string, vector<vector<string>>> transitions;
    for (auto s: dfa_dio.getStates()){
        auto naam = s->getLabel();
        if (s->isAccepting()){
            finalstates.push_back(naam);
        }
        if (s->isStarting()){
            startstate = naam;
        }
        states.push_back(naam);

        vector<vector<string>> transi;
        auto trans = s->getTransitionFunction();
        for (auto t: trans){
            auto input = t.first;
            for (auto to: t.second){
                auto toname = to->getLabel();
                transi.push_back({input, toname});
            }
        }
        transitions[naam] = transi;
    }
    odfa.setStates(states);
    odfa.setFinalStates(finalstates);
    odfa.setStartingState(startstate);
    odfa.transitions = transitions;
    odfa.setType("ODFA");
    odfa.setCurrentState(startstate);

    return odfa;
}
