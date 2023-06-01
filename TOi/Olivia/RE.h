//
// Created by mwuyt on 5/12/2023.
//

#ifndef TA_TO1_RE_H
#define TA_TO1_RE_H


#include "string"
#include "iostream"

class ORE {
    std::string str;
    char epsilon;

public:
    ORE(const std::string &str, char epsilon);

    ORE();

    const std::string &getStr() const;

    void setStr(const std::string &str);

    void print();
};


#endif //TA_TO1_RE_H
