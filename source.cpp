//
// Created by yoavgilad on 5/26/23.
//
#include "source.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>

std::vector<SymbolTable *> tables;


bool isInt(const std::string &str) {
    try {
        std::stoi(str);
        return true;
    } catch (const std::invalid_argument &e) {
        return false;
    }
}

bool isString(const std::string &str) {
    if (str.length() < 2)
        return false;
    if (str[0] == '"' && str[str.length() - 1] == '"')
        return true;
    return false;
}

bool isB(const std::string &str) {
    // Check if the string is empty
    if (str.empty())
        return false;
    for (int i = 0; i < str.length() - 1; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    if (str[str.length() - 1] != 'b')
        return false;
    return true;
}

Exp::Exp(string type) : Node(type) {}

Exp::Exp(Exp e1, string op, Exp e2) : Node(e1.type)
{
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
//    if (e1.type == e2.type)
//    {
//        this->type = e1.type;
//    }
//    else
//    {
//        if (e1.type == "int" && e2.type == "byte")
//        {
//            this->type = "int";
//        }
//        else
//        {
//            output::errorMismatch(yylineno);
//        }
//    }
//    cout << "Exp constructor with OP, " << *this << endl;
}

Exp::Exp(Node &exp, const string &conversion_type)
{
    cout << "third exp " << exp.type << "," << conversion_type << endl;
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
        if (exp.type == "int" || exp.type == "byte")
        {
            if (conversion_type == "int")
                this->type = "int";
            else // conversion type == "byte"
                this->type = "byte";
            return;
        }
        output::errorMismatch(yylineno);
        exit(0);
    }
    assert(conversion_type == "bool");
    if (exp.type == "bool")
    {
        this->type = "bool";
        return;
    }
    output::errorMismatch(yylineno);
    exit(0);
}

Exp::Exp(const Node &n) : Node(n.type)
{
    if (isInt(n.type))
    {
        cout << "isInt: " << n.type << endl;
        this->type = "int";
    } else if (isB(n.type))
    {
        this->type = "byte";
    } else if (isString(n.type))
    {
        this->type = "string";
    }
    else
    {
        //search for id in symbol tables
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
