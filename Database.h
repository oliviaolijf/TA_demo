#ifndef TA_TO1_DATABASE_H
#define TA_TO1_DATABASE_H

#include "TOi/Olivia/ONFA.h"
#include "TOi/Olivia/ORE.h"
#include "TOi/Olivia/ODFA.h"
#include "TOi/Dio/REDio.h"
#include "TOi/Dio/ENFADio.h"
#include "TOi/Dio/DFADio.h"
#include "Utils/DatabaseUtils.h"

using namespace std;

class Database {
public:
    map<string, ORE> acceptedEmailAdresses;
    map<string, ORE> keywords;

public:
    Database();

    void addAcceptedadresses(ODFA acceptedadresses, string name);
    /**
     * zet een ODFA waarin aanvaarde e-mailadressen zitten om in een regex
     * doordat het opgeslagen zit in een map met als key de naam
     * kunnen er verschillende filters met verschillende sterkte/inhoud waarop ze filter
     * opgeslagen worden in dezelfde database en kan er later makkelijk met ene bepaalde filter
     * gecontroleerd worden
     */
    DFADio loadAcceptedAdresses(string name);

    void addKeywords(ODFA, string name, ofstream& stream);
    
    DFADio loadKeywords(string name, ofstream& stream);

    bool isSpamAdress(string &emailadress, string &namefilter);
};


#endif //TA_TO1_DATABASE_H
