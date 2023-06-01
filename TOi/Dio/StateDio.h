//
// Created by dio on 27/02/2023.
//

#ifndef OPDRACHT_1_STATE_H
#define OPDRACHT_1_STATE_H

using namespace std;
#include <vector>
#include "string"
#include "map"

class StateDio {
private:
    StateDio* initcheck;
    string label;
    map <string,vector<StateDio*>>transition_function;
    bool starting;
    bool accepting;

public:

    void setLabel(const string &label);

    bool uniqueTransition(string symbol)const;

    bool isStarting() const;

    void setStarting(bool starting);

    bool isAccepting() const;

    void setAccepting(bool accepting);

    explicit StateDio(const string &label);

    void setTransitionFunction(string input, StateDio* to);

    vector <StateDio *> transition(string input);
    StateDio();

    const string &getLabel() const;

    vector<StateDio*> eclose(StateDio * s, string eps);

    virtual ~StateDio();

    const map<string, vector<StateDio *>> &getTransitionFunction() const;

    bool properlInitialized();
};


#endif //OPDRACHT_1_STATE_H
