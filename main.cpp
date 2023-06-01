#include <iostream>
#include <fstream>
#include "TOi/Jonathan/SSC_and_TFA/DFAJonathan.h"
#include "SpamFilter.h"
#include "TOi/Olivia/json.hpp"
#include "Output.h"

using namespace std;

int main() {
    ofstream out;
    out.open("Output/outputolivia.txt");
    ODFA odfa("DFA.json");
    SpamFilter filter;
    filter.database.addKeywords(odfa, "keywords", out);
    out << filter.database.keywords["keywords"].getStr() << endl;
    string name = "keywords";
    filter.load_keywords(name, out);
    out.close();
    return 0;
}
