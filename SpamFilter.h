//
// Created by dio on 19/05/2023.
//

#ifndef TOG_T_O_GROEPJE_18_SPAMFILTER_H
#define TOG_T_O_GROEPJE_18_SPAMFILTER_H

#include "Input.h"
#include "TOi/Jonathan/SSC_and_TFA/DFAJonathan.h"
#include "Utils/SpamFilterUtils.h"
#include "Utils/DBC.h"
#include "Output.h"
#include "TOi/Dio/REDio.h"
#include "TOi/Dio/DFADio.h"
#include "Database.h"

using namespace std;

class SpamFilter {
private:
    DFADio SpamKeywords;
    DFADio SpamEmails;
    DFADio BlackList;
    DFADio whiteList;
    DFADio mailClasses;
    DFADio alfabetdfa;


protected:
    bool update_blackList(DFADio dfa, bool remove);
    bool update_whiteList(DFADio dfa, bool remove);
    bool minimize_dfa(DFADio& dfa);
    bool setBlacklist(DFADio dfa);

    DFADio getMailClasses();
    void setMailClasses(const DFADio &mailClasses);

public:
    Database database;
    SpamFilter();

    DFADio getBlacklist();

    void deleteKeyWord(string keyword);

    DFADio &getSpamKeywords();

    void setSpamKeywords(const DFADio &spamKeywords);

    bool isThisSpam(string filepath);

    const DFADio &getSpamEmails() const;

    void setSpamEmails(const DFADio &spamEmails);

    virtual ~SpamFilter();

    void execute_command(vector <string> command);

    bool addToBlacklist(string keyword);

    bool removeFromBlacklist(string keyword);

    void markKeywordAsSpam(string keyword);

    bool addToWhitelist(string email);

    bool removeFromWhitelist(string email);

    DFADio & getWhiteList();

    bool add_mail_class(string keyword);

    bool keyword_is_mail_class(string keyword);

    bool update_mailClasses(DFADio dfa, bool remove);

    bool remove_from_mail_class(string keyword);

    bool classify_email(string filepath);

    void readInstructions(string filepath);

    void save_keywords(std::string &s);
    void save_accepted_adresses(std::string &s);
    void load_keywords(std::string &s, ofstream& stream);
    void load_accepted_adresses(std::string &s);
    void setWhitelist(DFADio dfa);

};


#endif //TOG_T_O_GROEPJE_18_SPAMFILTER_H
