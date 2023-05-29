//
// Created by yoavgilad on 5/27/23.
//

#ifndef HW3_TABLE_STACK_H
#define HW3_TABLE_STACK_H
#include <string>
#include <iostream>
#include "symbol_table.hpp"
#include "hw3_output.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

extern int yylineno;
//Saved?
class TableStack
{
    std::vector<SymbolTable*> tables;
public:
    TableStack():tables(){}
    void openNewScope();
    void closeScope();
    void addSymbolToLastTable(string name, string type, bool is_func_arg=false);
    void addFuncSymbol(string name, string type, string args, string is_override);
    vector<FuncSymbol*> getAllFunctionsWithName(string name);
    Symbol* searchForSymbol(string name);
    void compareType(string id_name, string exp_type);
    void printStack();
    bool isFuncExist(string func_name);
    FuncSymbol* searchForFuncSymbol(string func_name);
    ~TableStack();
};



#endif //HW3_TABLE_STACK_H
