//
// Created by Jonathan on 20/05/2023.
//

#include "SpamFilterUtils.h"

bool isChar(char c){
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

bool is_valid_email(string email){
    // Check the first character
    // is an alphabet or not
    if (!isChar(email[0])) {

        // If it's not an alphabet
        // email id is not valid
        return 0;
    }
    // Variable to store position
    // of At and Dot
    int At = -1, Dot = -1;

    // Traverse over the email id
    // string to find position of
    // Dot and At
    for (int i = 0;
         i < email.length(); i++) {

        // If the character is '@'
        if (email[i] == '@') {

            At = i;
        }

            // If character is '.'
        else if (email[i] == '.') {

            Dot = i;
        }
    }

    // If At or Dot is not present
    if (At == -1 || Dot == -1)
        return 0;

    // If Dot is present before At
    if (At > Dot)
        return 0;

    // If Dot is present at the end
    return !(Dot >= (email.length() - 1));

    // copied from stackoverflow!
}

bool DirectoryExists(const string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

bool FileExists(const string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) return false;
    ifstream f(filename.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

bool FileIsEmpty(const string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) return true; // File does not exist; thus it is empty
    return st.st_size == 0;
}


bool copyFile(const char *SRC, const char* DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}

vector<string> splitString(string line){
    vector<string> temp{};
    string tempString{};
    for(auto x : line){
        if(x != '/'){
            tempString = tempString + x;
        }else{
            temp.push_back(tempString);
            tempString.clear();
        }
    }
    temp.push_back(tempString);
    return temp;
}
