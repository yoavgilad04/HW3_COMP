#ifndef _SOURCE_H
#define _SOURCE_H

#include <string>
#include <iostream>
#include "table_stack.hpp"
#include "hw3_output.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int yylineno;
using namespace std;


class Node {
protected:
    string type;
public:
    Node(string type="Default"): type(type){};
    string getType(){return this->type;}
};

#define YYSTYPE Node*


class Exp : public Node
{
public:
    Exp(string type);
    Exp(Node& exp_1, string operation_val, Node& exp_2);
    Exp(Node& n);
    Exp(Node& exp, const string& conversion_type);
    friend ostream& operator<<(ostream& os, const Exp& e)
    {
        os << "Type: " << e.type;
        return os;
    }
};

#endif