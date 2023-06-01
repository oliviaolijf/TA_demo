//
// Created by Jonat on 26/05/2023.
//

#include "Output.h"


bool Output::out_found_blacklisted_email(string keyword, string mailName) {
    ofstream outfile;
    outfile.open("../Output/SpamFilterResults.txt", ios_base::app);
    outfile << getTimeStamp()  <<mailName << " --- " <<"Email contained Blacklisted emailAdress: " + keyword + " . Mail has been marked as spam!" << endl << endl;
    return true;
}

bool Output::out_found_nothing(string mailName) {
    ofstream outfile;
    outfile.open("../Output/SpamFilterResults.txt", ios_base::app);
    outfile << getTimeStamp()  << mailName << " --- " << "Email does not contain spam!"<< endl << endl;
    return true;
}

bool Output::out_found_spamKeyword(string keyword,string mailName) {
    ofstream outfile;
    outfile.open("../Output/SpamFilterResults.txt", ios_base::app);
    outfile << getTimeStamp()  <<mailName << " --- " <<"Email contained spam keyword: " + keyword + " . Mail has been marked as spam!" << endl << endl;
    return true;
}

char* Output::getTimeStamp() {
    time_t tt;
    struct tm* ti;
    // Applying time()
    time(&tt);
    // Using localtime()
    ti = localtime(&tt);
    return asctime(ti);
}