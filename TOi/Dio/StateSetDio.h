//
// Created by dio on 29/03/2023.
//

#ifndef OPDRACHT_1_STATESET_H
#define OPDRACHT_1_STATESET_H


#include "StateDio.h"

class StateSetDio {
public:
    explicit StateSetDio(vector<StateDio *> &set);

    explicit StateSetDio(vector<StateDio *> &set, bool product);

    StateSetDio();

    bool equal(vector<StateDio *> &altset);

    const vector<StateDio *> &getSet() const;

    bool isAcceptSet() const;

    void setAcceptSet(bool acceptSet);

    bool isStartSet() const;

    void setStartSet(bool startSet);

    StateSetDio * transition(string symbol);

    void setTransitionFunction(string symbol, StateSetDio * to);

    StateDio* toState();

    bool equivalent(StateDio* s);


    string createProductLabel(vector<StateDio *> &set);

    string createSetLabel(vector<StateDio *> &set);

    const string &getLabel() const;

    void setLabel(const string &label);

    void setSet(const vector<StateDio *> &set);

    void setEclose(string eps);


private:
    vector <StateDio *> set= {nullptr};

    map<string, StateDio*> states={};

    bool acceptSet = false;

    bool startSet = false;

    string label;

    map <string, StateSetDio*>transition_function;



};


#endif //OPDRACHT_1_STATESET_H
