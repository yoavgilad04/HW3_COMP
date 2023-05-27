//
// Created by yoavgilad on 5/27/23.
//

#ifndef HW3_TABLE_STACK_H
#define HW3_TABLE_STACK_H
#include <string>
#include <iostream>
#include "symbol_table.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;
class TableStack
{
    std::vector<SymbolTable*> tables;
public:
    TableStack():tables(){}
    void openNewScope();
    void closeScope();
    void addSymbolToLastTable(string name, string type);
    void addFuncSymbol(string name, string type, string args, string is_override);
    Symbol* searchForSymbol(string name);
    ~TableStack();
};



#endif //HW3_TABLE_STACK_H
