//
// Created by Sinem.E on 30/04/2023.
//

#ifndef DFA_CPP_TRANSITION_H
#define DFA_CPP_TRANSITION_H

#include <string>
using namespace std;

class Transition {

private:
    string from;
    string to;
    string input;

public:
    string &getFrom();

    void setFrom(string &from);

    const string &getTo() const;

    void setTo(string &to);

    const string &getInput() const;

    void setInput(const string &input);
};




#endif //DFA_CPP_TRANSITION_H
