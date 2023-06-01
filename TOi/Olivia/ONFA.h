#ifndef TA_TO1_NFA_H
#define TA_TO1_NFA_H
#include "ODFA.h"
#include "json.hpp"

class ONFA{
    std::string type;
    std::string startingState;
    std::string currentState;
    std::vector<std::string> finalStates;
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::map<std::string, std::vector<std::vector<std::string>>> transitions;

public:
    explicit ONFA() = default;
    ONFA(std::string);

    ODFA toDFA();
    void print();;
};


#endif //TA_TO1_NFA_H
