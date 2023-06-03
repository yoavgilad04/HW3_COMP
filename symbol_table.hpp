//
// Created by yoavgilad on 5/26/23.
//

#ifndef HW3_SYMBOL_TABLE_HPP
#define HW3_SYMBOL_TABLE_HPP
#include "symbol.hpp"
#include <bits/stdc++.h>
#include <vector>

using namespace std;
class SymbolTable
{
    multimap<string, Symbol*> map;
    vector<Symbol*> vec;
    int next_offset;
    int func_arg_offset;
public:
    SymbolTable(int next_offset=0):map(), vec(), next_offset(next_offset), func_arg_offset(-1){}
    void insert(string name, string type, bool is_func_arg=false);
    void insertFunc(string name, string type, vector<string> input_args, bool is_override);
    void popBySymbol(Symbol* s);
    void popByOffset(int offset);
    Symbol* getSymbolByName(string name);
    Symbol* getSymbolByOffset(int offset);
    bool isEmpty();
    vector<FuncSymbol*> getAllFunctionWithName(string name);
    int getSymbolTableOffset(){return this->next_offset;}
    ~SymbolTable();


    friend ostream& operator<<(ostream& os, const SymbolTable& t)
    {
        for (Symbol* symbol : t.vec)
        {
            os << *(symbol) << endl;
        }
        return os;
    }
};

//ostream& operator<<(ostream& os, const SymbolTable& t)


#endif //HW3_SYMBOL_TABLE_HPP
