#ifndef _SOURCE_H
#define _SOURCE_H

#include <string>
#include <iostream>
#include <assert.h>
#include "hw3_output.hpp"
#include "symbol_table.hpp"

//stack <SymbolTable*> sts;

extern int yylineno;
using namespace std;

class Node
        {
public:
    string value;
    Node(string text=""): value(text)
    {
        cout << "I'm inside node builder: "<< this->value << endl;
    }
};

#define YYSTYPE Node*


class Exp : public Node
{
public:
    Exp(const string& text): Node(text)
    {
        cout << "first exp " << this->value << endl;
    }

    Exp(string text, const string& type): Node(text)
    {
        cout << "second exp " << text << "," << type << endl;
        if (type == "id")
        {
            //TODO: yoav
            this->value = "int";
            return;
        }
        if (type == "byte")
        {
            int real_val = stoi(text);
            if (real_val > 255 || real_val < 0)
            {
                output::errorByteTooLarge(yylineno, text);
                exit(0);
            }
            this->value = type;
            return;
        }

    }

    Exp(Node& exp, const string& conversion_type)
    {
        cout << "third exp " << exp.value << "," << conversion_type << endl;
        if (conversion_type == "not")
        {
            if (exp.value == "bool")
            {
                this->value = "bool";
                return;
            }
            output::errorMismatch(yylineno);
            exit(0);
        }
        if (conversion_type == "int" || conversion_type == "byte")
        {
            if (exp.value == "int" || exp.value == "byte")
            {
                if(conversion_type == "int")
                    this->value = "int";
                else // conversion type == "byte"
                    this->value = "byte";
                return;
            }
            output::errorMismatch(yylineno);
            exit(0);
        }
        assert(conversion_type=="bool");
        if (exp.value == "bool")
        {
            this->value = "bool";
            return;
        }
        output::errorMismatch(yylineno);
        exit(0);
    }

    Exp(Node& exp_1, Node& exp_2, const string& operation_val)
    {
        cout << "fourth exp " << exp_1.value << "," << exp_2.value << "," << operation_val << endl;
        if ((exp_1.value == "int" || exp_1.value == "byte") && (exp_2.value == "int" || exp_2.value == "byte"))
        {
            if (operation_val == "binop")
            {
                if(exp_1.value == "int" || exp_2.value == "int")
                    this->value = "int";
                else
                    this->value = "byte";
                return;
            }
            if (operation_val == "relop")
            {
                this->value = "bool";
                return;
            }
            output::errorMismatch(yylineno);
            exit(0);
        }
        if (exp_1.value == "bool" && exp_2.value == "bool"){
            if (operation_val == "bool_op"){
                this->value = "bool";
                return;
            }
        }
        output::errorMismatch(yylineno);
        exit(0);
    }
};



#endif