//
// Created by Jonathan on 20/05/2023.
//

#ifndef TOG_T_O_GROEPJE_18_SPAMFILTERUTILS_H
#define TOG_T_O_GROEPJE_18_SPAMFILTERUTILS_H

#include "iostream"
#include "../TOi/Jonathan/SSC_and_TFA/DFAJonathan.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <string>

using namespace std;

bool isChar(char c);

bool is_valid_email(string email);

bool DirectoryExists(const string dirname);

bool FileExists(const string dirname);

bool FileIsEmpty(const string filename);

bool copyFile(const char *SRC, const char* DEST);

// splits on '/'
vector<string> splitString(string line);

#endif //TOG_T_O_GROEPJE_18_SPAMFILTERUTILS_H
