//
// Created by Sinem.E on 26/04/2023.
//

#ifndef NFA_CPP_STATE_H
#define NFA_CPP_STATE_H

#include <string>

using namespace std;

class State {
private:
    string name;
    bool start = false;
    bool accept = false;
public:
    const string &getName() const;

    void setName(const string &name);

    bool isStart() const;

    void setStart(bool start);

    bool isAccept() const;

    void setAccept(bool accept);
};


#endif //NFA_CPP_STATE_H
