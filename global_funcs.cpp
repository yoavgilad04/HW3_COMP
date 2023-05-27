//
// Created by yoavgilad on 5/27/23.
//
#include "global_funcs.hpp"

using namespace std;


void global::openNewScope()
{
    int new_offset;
    if (tables.empty())
        new_offset = 0;
    else
        new_offset = tables[tables.size() - 1]->getSymbolTableOffset();
    SymbolTable* t = new SymbolTable(new_offset);
    tables.push_back(t);
}

void global::closeScope()
{
    if (tables.empty())
        throw std::invalid_argument("Trying to close scope when there are no scopes in stack");
    SymbolTable* t_to_delete = tables[tables.size()-1];
    tables.pop_back();
    delete t_to_delete;
}

void global::addSymbolToLastTable(string name, string type)
{
    if (tables.empty())
        throw std::invalid_argument("Trying to add element when there are no scopes in stack");
    tables[tables.size()-1]->insert(name, type);
}

Symbol* global::searchForSymbol(string name)
{
    for(int i=tables.size()-1; i>=0 ; i--)
    {
        Symbol* sym = tables[i]->getSymbolByName(name);
        if (sym == nullptr)
            continue;
        return sym;
    }
}

