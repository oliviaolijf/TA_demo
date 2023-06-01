//
// Created by dio on 19/04/2023.
//

#include "REDio.h"

REDio::REDio(const string &expression, char eps) : expression(expression), eps(eps) {}

ENFADio REDio::toENFA() {

    int i=0;

    StateDio * current= createDefaultSet();
    StateDio * start=current;
    this->start=current;
    start->setStarting(true);
    ENFADio* enfa=get<0>(createENFA(expression, i, start, current));

    return *enfa;
}



StateDio *REDio::createDefaultSet() {
    StateDio * s=new StateDio();
    vector<StateDio *> empty{};
    string label="{Q";
    label += to_string(stateCounter);
    label +="}";
    s->setLabel(label);
    s->setStarting(false);
    s->setAccepting(false);
    stateCounter++;
    states.push_back(s);

    return s;
}

tuple<ENFADio*,int> REDio::createENFA(const string &expression, int &i, StateDio * &start, StateDio* &current) {
    ENFADio* e=new ENFADio();
    MyStack brackets;
    MyStack orStack;

    //int i=x;

    while (i<expression.size()){
        char p = expression[i];

        if (p=='('){
            if (i!=0){
                StateDio* temp=createDefaultSet();
                StateDio* temp2=temp;
                i++;
                ENFADio * tep=get<0>(createENFA(this->expression, i, temp, temp2));
                delete tep;

                current->setTransitionFunction(string(1,eps),temp);
                current=temp2;
            }
            else{
                i++;
                createENFA(this->expression,i,start,current);
            }

        } else if (p=='*') {
            KleeneOperation(start, current);
        }else if (p==')'){
            if (!orStack.isEmpty()){
                endOR(current,orStack);
            }
            if(i<expression.size()-1 && expression[i+1]=='*'){
                i++;
                KleeneOperation(start,current);
            }
            tuple<ENFADio*,int> result=make_tuple(e, i);
            return result;

        } else if (p=='+'){
            if (!orStack.isEmpty()){
                //case 1: tweede (of meer) opeenvolgende or statement in haakjes
                endOR(current,orStack);
            }
                //case 2: or statement niet in haakjes
            orOperation(start, current, orStack);

        } else {

            StateDio* temp2= createDefaultSet();
            current->setTransitionFunction(string(1, p),temp2);

            current=temp2;

            if(i<expression.size()-1 && expression[i+1]!='+' && expression[i+1]!='*' && expression[i+1]!=')' && expression[i+1]!='('){
                StateDio* temp= createDefaultSet();
                current->setTransitionFunction(string(1, eps),temp);

                current=temp;
            }


            if (p!=eps && find(alphabet.begin(),alphabet.end(),string(1, p))==alphabet.end()){
                alphabet.push_back(string(1, p));
            }

            if(i==expression.size()-1 && !(orStack.isEmpty())){
                endOR(current,orStack);
            }
        }
        i++;
    }



    this->start=start;
    current->setAccepting(true);

    e->setAlphabet(alphabet);
    e->setStates(states);
    e->setStartstate(start);
    e->setType("ENFADio");
    e->setEps(string(1,eps));

    tuple<ENFADio*,int> result=make_tuple(e, i);
    return result;
}




void REDio::KleeneOperation(StateDio *&beginning, StateDio *&ending) {
    //create new beginning- and endstate
    StateDio* temp1=createDefaultSet();
    StateDio* temp2=createDefaultSet();


    //create epsilon transitions
    temp1->setTransitionFunction(string(1,eps),beginning);
    ending->setTransitionFunction(string(1,eps),beginning);
    ending->setTransitionFunction(string(1,eps),*&temp2);
    temp1->setTransitionFunction(string(1,eps),*&temp2);

    //change pointers, to point at new beginning- and endstate
    beginning=*&temp1;
    ending=*&temp2;
}

void REDio::orOperation(StateDio *&start, StateDio *&current, MyStack &orStack) {

    //case 1: first term in or statement
    StateDio* newStart=createDefaultSet();
    newStart->setTransitionFunction(string(1, eps),start);
    start=newStart;

    StateDio* temp=createDefaultSet();
    current->setTransitionFunction(string(1, eps),temp);
    orStack.push(temp);

    current=start;

    StateDio* firstStateinOr=createDefaultSet();
    start->setTransitionFunction(string(1, eps),firstStateinOr);
    current=firstStateinOr;

}

void REDio::endOR(StateDio *&current, MyStack &orStack) {
    StateDio* temp=orStack.pop();
    current->setTransitionFunction(string(1,eps),temp);
    current=temp;
}

void REDio::concatenate(StateDio *&current, int &i) {
    i++;
    while (i<expression.size()){
        if (expression[i]=='*' or expression[i]=='+' or expression[i]==')'){
            break;
        } else if (expression[i]=='('){
            //nieuwe state en epsilon transitie

            StateDio* temp= createDefaultSet();
            current->setTransitionFunction(string(1, eps),temp);
            current=temp;

            i++;
        } else{

            StateDio* temp= createDefaultSet();
            current->setTransitionFunction(string(1, eps),temp);
            current=temp;

            StateDio* temp2= createDefaultSet();
            current->setTransitionFunction(string(1, expression[i]),temp2);
            current=temp2;

            i++;
        }
        if (expression[i]!=eps && find(alphabet.begin(),alphabet.end(),string(1,expression[i]))==alphabet.end()){
            alphabet.push_back(string(1,expression[i]));
        }
    }
    i--;
}


