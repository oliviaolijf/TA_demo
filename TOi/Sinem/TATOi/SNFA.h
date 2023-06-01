//
// Created by Sinem.E on 21/04/2023.
//

#ifndef TATOI_NFA_H
#define TATOI_NFA_H

#include "NFAConfig.h"
#include "ToDFAConfig.h"
#include "State.h"
#include <set>

using namespace std;

class SNFA {
private:
    NFAConfig config;
    ToDFAConfig todfa;
    NFAConfig parseJson(string filename);
public:
    SNFA();

    SNFA(string filename);

    bool transitionsOfNFA(vector<string> currentStates);

    bool isExist(string name);

    ToDFAConfig toDFA();
};


#endif //TATOI_NFA_H