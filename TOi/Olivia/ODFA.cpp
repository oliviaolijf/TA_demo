#include "ODFA.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include <set>
#include "ORE.h"

#define JSON_HEDLEY_NON_NULL

using json = nlohmann::json;
using namespace std;

ODFA::ODFA(string filename) {
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

void ODFA::print() {
    vector<map<string, nlohmann::json >> staten;
    for (auto s: states){
        nlohmann::json staat;
        staat["name"] = s;
        staat["starting"] = (s == startingState);
        staat ["accepting"] = false;
        if (find(finalStates.begin(), finalStates.end(), s)!= finalStates.end()){
            staat["accepting"] = true;
        }
        staten.push_back(staat);
    }

    vector<map<string,string>> transities;
    for (auto s: states){
        map<string,string> transitie;
        transitie["from"] = s;
        for (int i = 0; i < transitions[s].size(); i++){
            transitie["to"] = transitions[s][i][1];
            transitie["input"] = transitions[s][i][0];
            transities.push_back(transitie);
        }
    }

    json j{
            {"type", type}, {"alphabet", alphabet},{"states", staten}, {transitions, transities}
    };
    cout << setw(4) << j << endl;
}

bool ODFA::accepts(std::string a_string) {
    for (auto c: a_string) {
        bool breakloop = false;
        for (auto t: transitions) {
            int i = 0;
            while (i < t.second.size() && !breakloop) {
                if (currentState == t.first && t.second[i][0] == string(1,c)){
                    currentState = t.second[i][1];
                    breakloop = true;
                    break;
                }
                i++;
            }
        }
    }
    if (std::find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end()) {
        return true;
    }
    return false;
}

ORE ODFA::toRE() {
    ORE re = ORE();
    string regex;
    auto staten = states;
    std::sort(staten.begin(), staten.end());

    auto trans = transitions;


    for (int iter = 0; iter < staten.size(); iter++) {
        auto state = staten[iter];
        if (std::find(finalStates.begin(), finalStates.end(), state) != finalStates.end() || state == startingState) {
            continue;
        } else {
            // slaat op welke staten een transitie naar de staat die we willen verwijderen hebben
            // en met welke input deze transitie verloopt
            std::vector<pair<string, string>> bereikbaarVanuit;
            for (auto t: trans) {
                for (auto b: t.second) {
                    if (b[1] == state) {
                        bereikbaarVanuit.push_back({t.first, b[0]});
                    }
                }
            }

            auto vertrekkendeTrans = trans[state];
            int i = 0;
            string toself;
            while (i<vertrekkendeTrans.size()) {
                if (vertrekkendeTrans[i][1] == state) {
                    toself += vertrekkendeTrans[i][0];
                    vertrekkendeTrans.erase(vertrekkendeTrans.begin() + i);
                } else i++;
            }
            if (toself.size() > 1) {
                std::sort(toself.begin(), toself.end());
                string temp = "(";
                for (int c = 0; c < toself.size()-1; c++){
                    temp += toself[c] + '+';
                }
                temp += toself[toself.size()];
                temp += ")*";
            }
            else if (!toself.empty()){
                toself += "*";
            }

            if (!vertrekkendeTrans.empty()) {
                for (auto bv: bereikbaarVanuit) {
                    for (auto vt: vertrekkendeTrans) {
                        auto checkstaat = bv.first;
                        if (checkstaat == state) {
                            break;
                        }
                        auto atpidk = trans[checkstaat];
                        for (auto a: atpidk) {
                            if (a[1] == state) {
                                string newtrans;
                                if (!toself.empty()) {
                                    newtrans = a[0] + toself + vt[0];
                                } else newtrans = a[0] + vt[0];
                                int inter = 0;
                                for (auto b: atpidk) {
                                    if (b[1] == vt[1] && checkstaat < state) {
                                        newtrans = "("  + newtrans  + "+" + b[0] + ")";
                                        trans[checkstaat].erase(trans[checkstaat].begin() + inter);
                                    }
                                    else if (b[1] == vt[1] && checkstaat > state) {
                                        newtrans = "("  + b[0]+ "+" +newtrans + ")";
                                        trans[checkstaat].erase(trans[checkstaat].begin() + inter);
                                    }
                                    else {
                                        inter++;
                                    }
                                }
                                trans[checkstaat].push_back({newtrans, vt[1]});
                            }
                        }
                    }
                }
            }
        }
        for (auto t: trans) {
            if (t.first == state) {
                trans.erase(state);
                break;
            }
        }
        int inter = 0;
        for (auto t: trans) {
            for (auto v: t.second) {
                if (v[1] == state) {
                    trans[t.first].erase(trans[t.first].begin() + inter);
                } else inter++;
            }
            inter = 0;
        }
    }
    vector<string> regex2;
    for (auto &mm: trans[startingState]){
        regex2.push_back(mm[0]);
    }
    if (regex2.size() > 1){
        for (int i = 0; i < regex2.size()-1; i++){
            regex += regex2[i] + "+";
        }
    }
    regex += regex2[regex2.size()-1];
    re.setStr(regex);
    return re;
}
