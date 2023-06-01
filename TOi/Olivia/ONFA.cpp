#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include "ONFA.h"
using json = nlohmann::json;
using namespace std;

ONFA::ONFA(std::string filename){
    nlohmann::json j;
    std::ifstream input;
    input.open(filename);
    input >> j;

    type = j["type"];
    if (j.contains("alphabet")) {
        for (const auto &a: j["alphabet"]) {
            alphabet.push_back(a);
        }
    }

    if (j.contains("states")) {
        for (const auto &s: j["states"]) {
            states.push_back(s["name"]);
            if (s["starting"] == true) {
                startingState = s["name"];
                currentState = s["name"];
            }
            if (s["accepting"] == true) {
                finalStates.push_back(s["name"]);
            }
        }
    }

    if (j.contains("transitions")) {
        for (auto t: j["transitions"]) {
            transitions[t["from"]].push_back({t["input"], t["to"]});
        }
    }
}

void ONFA::print() {
    vector<map<string,nlohmann::json>> states;
    for (auto i:transitions){
        nlohmann::json state;
        state["name"] = i.first; //string
        state["starting"] = (i.first == startingState); //bool
        std::vector<string>::iterator it;
        it = std::find(finalStates.begin(), finalStates.end(), i.first);
        if(it != finalStates.end()){
            state["accepting"] = true; //bool
        }
        states.push_back(state);
    }
    vector<map<string,string>> Transitions;
    for(auto i:transitions){
        map<string, string> transition;
        for(auto j:i.second){
            transition["from"] =  i.first;
            transition["to"] = j[1];
            transition["input"] = j[0];

            Transitions.push_back(transition);
        }
    }
    json j{
            {"type", type},
            {"alphabet", alphabet},
            {"states", states},
            {"transitions", Transitions}
    };
    cout << setw(4) << j << endl;
}

ODFA ONFA::toDFA() {
    ODFA dfa;
    string empty = "{}";
    dfa.setAlphabet(alphabet);
    dfa.setStartingState("{" + startingState + "}");
    dfa.setCurrentState("{" + startingState + "}");

    std::map<std::string, std::vector<std::vector<std::string>>> newtransitions;
    std::vector<string> newstates;
    vector<string> newFinals;
    std::queue<std::vector<std::string>> notFound;

    newstates.push_back("{" + startingState + "}");

    for (auto i: alphabet) {
        std::string newstate = "{";
        std::vector<string> closure;
        for (auto t: transitions[startingState]) {
            if (t[0] == i) {
                closure.push_back(t[1]);
            }
        }

        if (closure.empty()) {
            newtransitions["{" + startingState + "}"].push_back({i, empty});
        } else {
            std::sort(closure.begin(), closure.end());
            for (int it = 0; it < closure.size() - 1; it++) {
                newstate += closure[it] + ",";
            }
            newstate += closure[closure.size() - 1] + "}";
            newtransitions["{" + startingState + "}"].push_back({i, newstate});

            if (find(newstates.begin(), newstates.end(), newstate) == newstates.end()) {
                notFound.push(closure);
                newstates.push_back(newstate);
            }
            for (auto c: closure) {
                if (find(finalStates.begin(), finalStates.end(), c) != finalStates.end()) {
                    newFinals.push_back(newstate);
                    break;
                }
            }
        }
    }
    while (!notFound.empty()) {
        auto curstate = notFound.front();
        notFound.pop();
        for (auto a: alphabet) {
            vector<string> closure2;
            string state = "{";
            string newstate2 = "{";
            for (auto c: curstate) {
                for (auto tran: transitions[c]) {
                    if (tran[0] == a && std::find(closure2.begin(), closure2.end(), tran[1]) == closure2.end()) {
                        closure2.push_back(tran[1]);
                    }
                }
            }

            for (int it = 0; it < curstate.size() - 1; it++) {
                state += curstate[it] + ",";
            }
            state += curstate[curstate.size() - 1] + "}";

            if (closure2.empty()) {
                newtransitions[state].push_back({a, empty});
            } else {
                std::sort(closure2.begin(), closure2.end());
                for (int it = 0; it < closure2.size() - 1; it++) {
                    newstate2 += closure2[it] + ",";
                }
                newstate2 += closure2[closure2.size() - 1] + "}";

                newtransitions[state].push_back({a, newstate2});

                if (find(newstates.begin(), newstates.end(), newstate2) == newstates.end()) {
                    notFound.push(closure2);
                    newstates.push_back(newstate2);
                }
                for (auto c: closure2) {
                    if (find(finalStates.begin(), finalStates.end(), c) != finalStates.end()) {
                        newFinals.push_back(newstate2);
                        break;
                    }
                }
            }
        }
    }
    dfa.setStates(newstates);
    dfa.setFinalStates(newFinals);
    dfa.transitions = newtransitions;
    dfa.setType("ODFA");
    return dfa;
}

