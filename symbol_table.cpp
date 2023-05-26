//
// Created by yoavgilad on 5/26/23.
//
#include "symbol_table.hpp"

void SymbolTable::insert(Symbol* s)
{
    this->map.insert(pair<string, Symbol*>(s->getName(), s));
    s->setOffset(this->next_offset);
    this->next_offset++;
}

void SymbolTable::popBySymbol(Symbol* s)
{
    this->map.erase(s->getName());
    this->next_offset--;
}

void SymbolTable::popByOffset(int offset)
{
    for (std::multimap<string,Symbol*>::iterator it = this->map.begin(); it != this->map.end();++it)
    {
        if (it->second->getOffset() == offset)
        {
            this->map.erase(it->second->getName());
            return;
        }
    }
}

Symbol* SymbolTable::getSymbolByName(string name)
{
    return this->map.find(name)->second;
}

bool SymbolTable::isEmpty()
{
    return this->map.empty();
}

~SymbolTable::SymbolTable()
{
    for (std::multimap<string,Symbol*>::iterator it = this->map.begin(); it != this->map.end();++it)
    {
        delete it->second;
    }
}


