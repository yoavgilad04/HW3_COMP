//
// Created by yoavgilad on 5/26/23.
//
#include "source.hpp"
#include <stdlib.h>
#include <ctype.h>

TableStack table_stack;

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

bool isByte(const std::string &str) {
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

Exp::Exp(Node& exp_1, string operation_val, Node& exp_2)
{
//    cout << "e1: " << exp_1.getType() << " e2: " << exp_2.getType() << endl;
    if ((exp_1.getType() == "int" || exp_1.getType() == "byte") && (exp_2.getType() == "int" || exp_2.getType() == "byte"))
    {
        if (operation_val == "binop")
        {
            if(exp_1.getType() == "int" || exp_2.getType() == "int")
                this->type = "int";
            else
                this->type = "byte";
            return;
        }
        if (operation_val == "relop")
        {
            this->type = "bool";
            return;
        }
//        output::errorMismatch(yylineno);
   //     exit(0);
    }
    if (exp_1.getType() == "bool" && exp_2.getType() == "bool"){
        if (operation_val == "bool_op"){
            this->type = "bool";
            return;
        }
    }
//    output::errorMismatch(yylineno);
//    exit(0);
}

Exp::Exp(Node &exp, const string &conversion_type)
{
//    cout << "third exp " << exp.getType() << "," << conversion_type << endl;
    if (conversion_type == "not")
    {
        if (exp.getType() == "bool")
        {
            this->type = "bool";
            return;
        }
        output::errorMismatch(yylineno);
        exit(0);
    }
    if (conversion_type == "int" || conversion_type == "byte")
    {
        if (exp.getType() == "int" || exp.getType() == "byte")
        {
            if (conversion_type == "int")
                this->getType() = "int";
            else // conversion type == "byte"
                this->type = "byte";
            return;
        }
        output::errorMismatch(yylineno);
        exit(0);
    }
    assert(conversion_type == "bool");
    if (exp.getType() == "bool")
    {
        this->type = "bool";
        return;
    }
    output::errorMismatch(yylineno);
    exit(0);
}

Exp::Exp(Node &n): Node(n.getType())
{
    if (isInt(n.getType()))
    {
        int real_val = stoi(n.getType());
        if (real_val > 255 || real_val < 0)
        {
            output::errorByteTooLarge(yylineno, n.getType());
            exit(0);
        }
        this->type = "byte";
    }
    else
    {
        cout << "Shaked Shtok, yoav will search for ID" << endl;
        //handle ID
        Symbol* t = table_stack.searchForSymbol(n.getType()); // in this case type will be the name of the id
        if (t == nullptr)
        {
            output::errorUndef(yylineno, n.getType());
        }
        this->type = t->getType();
    }
}

