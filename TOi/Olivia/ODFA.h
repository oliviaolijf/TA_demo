#ifndef TA_TO1_DFA_H
#define TA_TO1_DFA_H
#include <string>
#include <vector>
#include "json.hpp"
#include "RE.h"

using json = nlohmann::json;

class ODFA {
    std::string type;
    std::string startingState;
    std::string currentState;
    std::vector<std::string> finalStates;
    std::vector<std::string> states;
    std::vector<std::string> alphabet;


public:
    std::map<std::string, std::vector<std::vector<std::string>>> transitions;
    explicit ODFA() = default;
    ODFA(std::string);

    void setType(const std::string &t) {type = t;};
    const std::string &getType() {return type;};

    void setStartingState(const std::string &ss) {startingState = ss;};
    const std::string &getStartingState() {return startingState;};

    void setCurrentState(const std::string &curs){currentState = curs;};
    const std::string &getCurrentSate() {return currentState;};

    void setFinalStates(const std::vector<std::string> &finals){finalStates = finals;};
    const std::vector<std::string>& getFinalStates() {return finalStates;};
    void addFinalState(std::string &state){finalStates.push_back(state);};

    void setStates(const std::vector<std::string>& staten){states = staten;};
    const std::vector<std::string>& getStates() {return states;};
    void addState(std::string sta) {states.push_back(sta);};

    void setAlphabet(const std::vector<std::string>& alph) {alphabet =alph;};
    const std::vector<std::string> &getAlphabet(){return alphabet;};
    void addToAlphabet(std::string input) {alphabet.push_back(input);};

    bool accepts(std::string a_string );
    void print();
    ORE toRE();
};


#endif //TA_TO1_DFA_H
