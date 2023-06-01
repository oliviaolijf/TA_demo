//
// Created by dio on 19/05/2023.
//

#include "SpamFilter.h"

SpamFilter::SpamFilter() {
    //Dit initialiseert de SpamWords dfa met een lege DFADio
    REDio regex=REDio("abcdefghijklmnopqrstuvwxyz.@",'%');
    ENFADio enfa=regex.toENFA();
    DFADio dfa=enfa.toDFA();
    alfabetdfa=dfa;
    //minimize_dfa(alfabetdfa);
    this->setSpamKeywords(dfa);

    //Dit initialiseert de Blacklist dfa met een lege DFADio
    REDio regex_b=REDio("",'%');
    ENFADio enfa_b=regex_b.toENFA();
    DFADio dfa_b=enfa_b.toDFA();
    this->setBlacklist(this->alfabetdfa);

    //Dit initialiseert de mailclasses dfa met een lege DFADio
    REDio regex_c=REDio("",'%');
    ENFADio enfa_c=regex_c.toENFA();
    DFADio dfa_c=enfa_c.toDFA();
    this->setMailClasses(this->alfabetdfa);

    //Dit initialiseert de whitelist dfa met een lege DFADio
    REDio regex_w=REDio("",'%');
    ENFADio enfa_w=regex_w.toENFA();
    DFADio dfa_w=enfa_w.toDFA();
    this->setWhitelist(this->alfabetdfa);
}

bool SpamFilter::setBlacklist(DFADio dfa){
    BlackList = dfa;
    return true;
}

void SpamFilter::deleteKeyWord(string keyword) {
    REDio regex=REDio(keyword,'*');
    ENFADio enfa=regex.toENFA();
    DFADio dfa=enfa.toDFA();
    dfa.changeToComplementDFA();

    this->SpamKeywords=DFADio(this->SpamKeywords,dfa,true);
}

DFADio &SpamFilter::getSpamKeywords()  {
    return SpamKeywords;
}

void SpamFilter::setSpamKeywords(const DFADio &spamKeywords) {
    SpamKeywords = spamKeywords;
}

const DFADio &SpamFilter::getSpamEmails() const {
    return SpamEmails;
}

void SpamFilter::setSpamEmails(const DFADio &spamEmails) {
    SpamEmails = spamEmails;
}

SpamFilter::~SpamFilter() {}

bool SpamFilter::isThisSpam(string filepath) {
    REQUIRE(FileExists(filepath),"File is does not exist, called from isThisSpam");
    REQUIRE(!FileIsEmpty(filepath),"File is empty, called from isThisSpam");
    fstream file;
    string word;
    Output out;

    file.open(filepath.c_str());

    int spamwordCounter=0;
    while (file >> word){
        string keyword;
        for (int i=0;i<word.size(); i++){
            //skipt leestekens om obfustication tegen te gaan
            if (!(word[i]=='/' | word[i]=='?' | word[i]=='!' | word[i]=='.')){
               keyword.push_back(word[i]);
            }
            if (word[i]=='@'){
                keyword=word;
                i=word.size();
            }
        }
        if(getSpamKeywords().accepts(keyword)){
            spamwordCounter++;
            out.out_found_spamKeyword(keyword,filepath);
            if (spamwordCounter==2){
                return true;
            }
        }
        if(getBlacklist().accepts(keyword)){
            out.out_found_blacklisted_email(keyword,filepath);
            return true;
        }
    }
    out.out_found_nothing(filepath);
    return false;
}

bool SpamFilter::classify_email(string filepath) {
    REQUIRE(FileExists(filepath),"File is does not exist, called from classify_email");
    REQUIRE(!FileIsEmpty(filepath),"File is empty, called from classify_email");
    fstream file;
    string word;
    Output out;
    string fileName = splitString(filepath)[splitString(filepath).size() -1];

    file.open(filepath.c_str());

    while (file >> word){
        string keyword;
        for (int i=0;i<word.size(); i++){
            //skipt leestekens om obfustication tegen te gaan
            if (!(word[i]=='/' | word[i]=='?' | word[i]=='!')){
                keyword.push_back(word[i]);
            }
        }
        if(getMailClasses().accepts(keyword)){
            std::string to = "../Inbox_demo/" + keyword + "/"+ fileName;
            copyFile(filepath.c_str(),to.c_str());
            return true;
        }
    }

    std::string to = "../Inbox_demo/General/" + fileName;
    copyFile(filepath.c_str(),to.c_str());
    return true;
}

void SpamFilter::readInstructions(string filepath) {
    ifstream file(filepath);
    string line;

    while (getline(file,line)) {
        vector <string> command;
        string word="";
        for (int i=0; i<line.size(); i++){
            if (line[i]!= ':'){
                word+=line[i];
                if (i==line.size()-1){
                    command.push_back(word);
                }
            }else{
                i++;
                command.push_back(word);
                word="";
            }
        }

        if (!command.empty()) {
            execute_command(command);
        }
    }
}


void SpamFilter::execute_command(vector <string> command) {
    if (command[0] == "spamkeyword_toevoegen") {
        // roep functie op om spamkeyword aan databank toe te voegen
        markKeywordAsSpam(command[1]);
    } else if (command[0] == "spamkeyword_verwijderen") {
        // spamkeyword verwijderen
        deleteKeyWord(command[1]);
        //cout << command[1] << "--> was added to spam" << endl;
    }
    else if (command[0] == "aan_blacklist_toevoegen") {
        addToBlacklist(command[1]);
    } else if (command[0] == "van_blacklist_verwijderen") {
        removeFromBlacklist(command[1]);
    }else if (command[0] == "aan_whitelist_toevoegen") {
        addToWhitelist(command[1]);
    } else if (command[0] == "van_whitelist_verwijderen") {
        removeFromWhitelist(command[1]);
    }
    else if (command[0] == "spam_e-mail_toevoegen") {
        // spam e-mail toevoegen
    } else if (command[0] == "spam_e-mail_verwijderen") {
        // spam e-mail verwijderen
        removeFromBlacklist(command[1]);

    } else if (command[0] == "add_mail_class") {
        // e-mail klasse toevoegen
        add_mail_class(command[1]);

    }  else if (command[0] == "remove_from_mail_class") {
        // e-mail klasseverwijderen
        remove_from_mail_class(command[1]);

    } else if (command[0] == "classify_email") {
        // e-mail classificeren
        classify_email(command[1]);

    } else if (command[0] == "e-mail_controle") {
        // e-mail controleren op spam
        isThisSpam(command[1]);

    }
    /**else if (command[0] == "save_keywords"){
        //save_keywords(command[1]);
    }
    else if (command[0] == "save_accepted_adresses"){
        //save_accepted_adresses(command[1]);
    }**/
    /**else if (command[0] == "load_keywords"){
        load_keywords(command[1]);
    }**/
    else if (command[0] == "load_accepted_adresses"){
        load_accepted_adresses(command[1]);
    }
}

DFADio SpamFilter::getBlacklist() {
    return BlackList;
}

bool SpamFilter::addToBlacklist(string email) {
    // if form is valid...
    if(is_valid_email(email)){
        REDio regex=REDio(email,'%');
        ENFADio enfa=regex.toENFA();
        DFADio dfa=enfa.toDFA();
        update_blackList(dfa,false);
        return true;
    } else{
        return false;
    }
}

bool SpamFilter::removeFromBlacklist(string email) {
    if(is_valid_email(email)){
        REDio regex=REDio(email,'*');
        ENFADio enfa=regex.toENFA();
        DFADio dfa=enfa.toDFA();
        dfa.changeToComplementDFA();
        DFADio dfa2(dfa,alfabetdfa,false);
        update_blackList(dfa2,true);
        return true;
    } else{
        return false;
    }
}


bool SpamFilter::update_blackList(DFADio dfa, bool remove) {
    // Adds or removes from class blacklist variable and optimizes it.
    this->BlackList = DFADio(this->BlackList,dfa,remove);
    minimize_dfa(BlackList);
    return true;
}

bool SpamFilter::update_whiteList(DFADio dfa, bool remove) {
    whiteList = DFADio(whiteList,dfa,remove);
    minimize_dfa(whiteList);
    return true;
}

bool SpamFilter::minimize_dfa(DFADio& dfa){
    DFAJonathan minimized = DFAJonathan(dfa.get_json_dfa()).minimize();
    dfa = DFADio(minimized.get_json_dfa());
    return true;
}

void SpamFilter::markKeywordAsSpam(string keyword) {

    REDio regexKeyword = REDio(keyword,'%'); // '%' stelt epsilon voor

    // omzetten naar een ENFA
    ENFADio enfaKeyword = regexKeyword.toENFA();

    // omzetten naar een DFA
    DFADio dfaKeyword = enfaKeyword.toDFA();

    // unie van getSpamkeywords en dfaKeyword, false staat voor unie
    DFADio spamKeyword = DFADio(getSpamKeywords(), dfaKeyword, false);

    setSpamKeywords(spamKeyword);
}

bool SpamFilter::addToWhitelist(string email) {

    if (is_valid_email(email) == false) {
        return false;
    }

    REDio regexEmail = REDio(email,'%');

    // omzetten naar een eNFA
    ENFADio enfaEmail = regexEmail.toENFA();

    // omzetten naar een DFA
    DFADio dfaEmail = enfaEmail.toDFA();

    // regex toevoegen aan databank
    update_whiteList(dfaEmail,false);

    return true;
}

bool SpamFilter::removeFromWhitelist(string email) {
    if (is_valid_email(email) == false) {
        return false;
    }

    REDio regexEmail = REDio(email, '*');

    // omzetten naar een eNFA
    ENFADio enfaEmail = regexEmail.toENFA();

    // omzetten naar een DFA
    DFADio dfaEmail = enfaEmail.toDFA();

    dfaEmail.changeToComplementDFA();

    update_whiteList(dfaEmail, true);

    return true;
}

void SpamFilter::setWhitelist(DFADio dfa) {
    whiteList = dfa;
}

DFADio & SpamFilter::getWhiteList() {
    return whiteList;
}

bool SpamFilter::add_mail_class(string keyword) {
    // if form is valid...
    if(!keyword.empty()){
        REDio regex=REDio(keyword,'%');
        ENFADio enfa=regex.toENFA();
        DFADio dfa=enfa.toDFA();
        update_mailClasses(dfa,false);

        // Create categorie dir
        std::string a = "../Inbox_demo/" + keyword;
        mkdir(a.c_str());

        return true;
    } else{
        return false;
    }
}

bool SpamFilter::remove_from_mail_class(string keyword) {
    REQUIRE(DirectoryExists("../inbox_demo/" +keyword),"Keyword does not exist");
    if(!keyword.empty()){
        REDio regex=REDio(keyword,'*');
        ENFADio enfa=regex.toENFA();
        DFADio dfa=enfa.toDFA();
        dfa.changeToComplementDFA();
        update_mailClasses(dfa,true);

        std::string a = "../Inbox_demo/" + keyword;
        rmdir(a.c_str());

        return true;
    } else{
        return false;
    }
}

bool SpamFilter::update_mailClasses(DFADio dfa, bool remove) {
    // Adds or removes from class blacklist variable and optimizes it.
    DFADio dfa2(dfa,alfabetdfa,false);
    this->mailClasses = DFADio(dfa2,this->mailClasses,remove);
    return true;
}

DFADio SpamFilter::getMailClasses()  {
    return mailClasses;
}

void SpamFilter::setMailClasses(const DFADio &mailClasses) {
    SpamFilter::mailClasses = mailClasses;
}

/**void SpamFilter::save_keywords(std::string &s) {
    auto keywords = this->getSpamKeywords();
    auto odfa = toODFA(keywords);
    ofstream out;
    database.addKeywords(odfa, s);
}

void SpamFilter::save_accepted_adresses(std::string &s) {
    auto adresses = this->getWhiteList();
    auto odfa = toODFA(adresses);
    database.addAcceptedadresses(odfa, s);
}**/

void SpamFilter::load_keywords(std::string &s, ofstream& stream) {
    auto keywords = database.loadKeywords(s, stream);
    this->setSpamKeywords(keywords);
}

void SpamFilter::load_accepted_adresses(std::string &s) {
    auto adresses = database.loadAcceptedAdresses(s);
    this->setWhitelist(adresses);
}







