#ifndef _SOURCE_H
#define _SOURCE_H

#include <string>
#include <iostream>
#include "hw3_output.hpp"

extern int yylineno;
using namespace std;

class Node {
public:
    string value;
    Node(string text): value(text){
        cout << "I'm inside node builder "<< this->value << endl;
    };
};

#define YYSTYPE Node*

class Exp : public Node
{
public:
    string type;
    Exp(string text, string type): Node(text), type(type){
        cout << "text: " << this->value << " type: " << this->type << endl;
    };
    Exp(Exp& exp_1, Exp& exp_2)
};

class Add : public Exp
{
    int true_val;
    Add(Exp exp_1, Exp exp_2): Exp(exp_1.value, exp_1->type){
        if(exp_1.type == 'int' && exp_1->type == exp_2->type) {
            output::errorMismatch(yylineno);
        }
        cout << "num:" << this->true_val << "string" << this->value << endl;
    };
};

#endif