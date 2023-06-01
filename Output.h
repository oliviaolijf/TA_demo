//
// Created by Jonat on 26/05/2023.
//

#ifndef TOG_T_O_GROEPJE_18_OUTPUT_H
#define TOG_T_O_GROEPJE_18_OUTPUT_H

#include "iostream"
#include <fstream>
#include <ctime>

using namespace std;

class Output {
protected:
    char* getTimeStamp();

public:
    bool out_found_blacklisted_email(string keyword, string mailName);

    bool out_found_spamKeyword(string keyword,string mailName);

    bool out_found_nothing(string mailname);

};


#endif //TOG_T_O_GROEPJE_18_OUTPUT_H
