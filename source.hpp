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
    Node(string text=""): value(text){
        cout << "I'm inside node builder "<< this->value << endl;
    };
};

#define YYSTYPE Node*



class Exp : public Node
{
public:
    string type;
    Exp(string text, string type): Node(text), type(type)
    {
        cout << "text: " << this->value << " type: " << this->type << endl;
    }

    Exp(Exp& exp_1, string , string conversion_type)
    {

    }

    Exp(string text, string type, string operation_type): Node(text)
    {

    }

    Exp(Exp& exp_1, Exp& exp_2, string operation_val)
    {
        if (operation_val == "+" || operation_val == "-" || operation_val == "*" || operation_val == "/")
        {
            if ((exp_1.type == "int" || exp_1.type == "byte") && (exp_2.type == "int" || exp_2.type == "byte"))
            {
                if(exp_1.type == "int" || exp_2.type == "int")
                    this->type = "int";
                else
                    this->type = "byte";

                switch(operation_val){
                    case "+":
                        this->value = exp_1.value + exp_2.value;
                        return;
                    case "-":
                        this->value = exp_1.value - exp_2.value;
                        return;
                    case "*":
                        this->value = exp_1.value * exp_2.value;
                        return;
                    case "/":
                        this->value = exp_1.value / exp_2.value;
                        return;
                }
            }
            else
            {
                output::errorMismatch(yylineno);
            }
            return;
        }

    }

};

#endif