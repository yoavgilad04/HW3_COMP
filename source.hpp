#ifndef _SOURCE_H
#define _SOURCE_H

#include <string>
#include <iostream>
#include "symbol_table.hpp"
#include "hw3_output.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int yylineno;
using namespace std;

class Node {
public:
    string type;
    Node(string type="Default"): type(type){};
};

#define YYSTYPE Node*


class Exp : public Node
{
public:
    string type;
    Exp(string type);
    Exp(Exp e1, string op , Exp e2);
    Exp(const Node& n);
    Exp(const Node* exp, const string& conversion_type);
    friend ostream& operator<<(ostream& os, const Exp& e)
    {
        os << "Type: " << e.type;
        return os;
    }
};

#endif