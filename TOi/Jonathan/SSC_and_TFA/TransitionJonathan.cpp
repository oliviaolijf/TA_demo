//
// Created by Jonathan on 03/03/2023.
//

#include "TransitionJonathan.h"

TransitionJonathan::TransitionJonathan(string symbol, StateJonathan* from, StateJonathan* to) {
    TransitionJonathan::symbol = symbol;
    TransitionJonathan::from = from;
    TransitionJonathan::to = to;


}

StateJonathan *TransitionJonathan::getFrom() {
    return from;
}

string TransitionJonathan::getSymbol() {
    return symbol;
}

StateJonathan *TransitionJonathan::getTo() {
    return to;
}