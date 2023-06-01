#include "RE.h"

ORE::ORE(const std::string &str, char epsilon) : str(str), epsilon(epsilon) {}

void ORE::print() {
    std::cout << str << std::endl;
}

ORE::ORE() {}

const std::string &ORE::getStr() const {
    return str;
}

void ORE::setStr(const std::string &str) {
    ORE::str = str;
}