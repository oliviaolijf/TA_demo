#include "Database.h"


Database::Database() {}

void Database::addAcceptedadresses(ODFA acceptedadresses, string name) {
    ORE adressen = acceptedadresses.toRE();
    acceptedEmailAdresses[name] = adressen;
    cout << "De geaccepteerde e-mailadressen zijn toegevoegd aan de database onder de key " << name << "." << endl;
}

void Database::addKeywords(ODFA keywords, string name, ofstream& stream) {
    ORE keywrds = keywords.toRE();
    this->keywords[name] = keywrds;
    stream << "The DFA with keywords has been added to the database under key " << name << "." << endl;
}

DFADio Database::loadKeywords(string name, ofstream& out) {
    auto keywrds = keywords[name];
    auto strkeywrds = keywrds.getStr();
    char epsilon = ' ';

    REDio regex = REDio(strkeywrds, epsilon);
    ENFADio e_nfa = regex.toENFA();
    DFADio dfa_dio = e_nfa.toDFA();
    out << "The filter's keywords have been set to the DFA saved in the database under key " << name << "." << endl;
    return dfa_dio;
}

DFADio Database::loadAcceptedAdresses(string name) {
    auto am = acceptedEmailAdresses[name];
    auto straem = am.getStr();
    char epsilon = ' ';

    REDio regex = REDio(straem, epsilon);
    ENFADio e_nfa = regex.toENFA();
    DFADio dfa_dio = e_nfa.toDFA();

    return dfa_dio;
}

bool Database::isSpamAdress(string &emailadress, string &namefilter) {
    auto dfaFilter = loadAcceptedAdresses(namefilter);
    if (dfaFilter.accepts(emailadress)) return false;
    return true;
}



