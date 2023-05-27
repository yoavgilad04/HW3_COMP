//
// Created by yoavgilad on 5/27/23.
//
#include "table_stack.hpp"

void TableStack::openNewScope()
{
    int new_offset;
    if (this->tables.empty())
        new_offset = 0;
    else
        new_offset = this->tables[this->tables.size() - 1]->getSymbolTableOffset();
    SymbolTable* t = new SymbolTable(new_offset);
    this->tables.push_back(t);
}

void TableStack::closeScope()
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to close scope when there are no scopes in stack");
    SymbolTable* t_to_delete = this->tables[this->tables.size()-1];
    this->tables.pop_back();
    delete t_to_delete;
}

void TableStack::addSymbolToLastTable(string name, string type)
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to add element when there are no scopes in stack");
    this->tables[this->tables.size()-1]->insert(name, type);
}

Symbol* TableStack::searchForSymbol(string name)
{
    for(int i=this->tables.size()-1; i>=0 ; i--)
    {
        Symbol* sym = this->tables[i]->getSymbolByName(name);
        if (sym == nullptr)
            continue;
        return sym;
    }
    return nullptr;
}

TableStack::~TableStack()
{
    if (this->tables.size() != 1)
        cout <<"More then one Scope when deleteing tableStack";
    for(int i=0; i<this->tables.size(); i++)
    {
        delete this->tables[i];
    }
}

