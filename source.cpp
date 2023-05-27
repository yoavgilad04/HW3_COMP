//
// Created by yoavgilad on 5/26/23.
//
#include "source.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>

std::vector<SymbolTable*> tables;


bool isInt(const std::string &str) {
    try {
        std::stoi(str);
        return true;
    } catch (const std::invalid_argument &e) {
        return false;
    }
}

bool isString(const std::string& str)
{
    if (str.length() < 2)
        return false;
    if (str[0] == '"' && str[str.length() - 1] == '"')
        return true;
    return false;
}

bool isB(const std::string& str) {
    // Check if the string is empty
    if (str.empty())
        return false;
    for (int i=0; i<str.length()-1; i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    if (str[str.length()-1] != 'b')
        return false;
    return true;
}

Exp::Exp(string type) : Node(type){}

Exp::Exp(Exp e1, string op, Exp e2) : Node(e1.type)
{
    if (e1.type == e2.type) {
        this->type = e1.type;
    }
    else
    {
        if (e1.type == "int" && e2.type == "b")
        {
            this->type = "int";
        }
        else
        {
            output::errorMismatch(yylineno);
        }
    }
    cout << "Exp constructor with OP, " << *this << endl;
}


Exp::Exp(const Node &n): Node(n.type)
{
    if (isInt(n.type))
    {
        cout<< "isInt: " << n.type << endl;
        this->type = "int";
    }
    else if (isB(n.type))
    {
        this->type = "b";
    }
    else if (isString(n.type))
    {
        this->type = "string";
    }
    else
    {
        cout << "Inside Node Converter: " << n.type << endl;
//        Symbol* s = (n.type); //in here type means the id(ex: "x", "var" ..)
//        if (s == nullptr)
//        {
//            output::errorUndef(yylineno, n.type);
//        }
//        cout << "The symbol found is: " << s << endl;
//        this->type = s->getType();
    }
}
