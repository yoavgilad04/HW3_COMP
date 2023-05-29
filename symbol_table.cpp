//
// Created by yoavgilad on 5/26/23.
//
#include "symbol_table.hpp"

void SymbolTable::insert(string name, string type)
{
    Symbol* s = new Symbol(name, type, this->next_offset);
    this->map.insert(pair<string, Symbol*>(s->getName(), s));
    this->next_offset++;
//    cout << "symbol inserted "<< name << endl;
}

void SymbolTable::insertFunc(string name, string type, vector<string> input_args, bool is_override)
{
    FuncSymbol* s = new FuncSymbol(name, type, 0, true, input_args, is_override);
    this->map.insert(pair<string, Symbol*>(s->getName(), s));
//    cout << "func symbol inserted "<< name << endl;
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
    std::multimap<string, Symbol*>::iterator it = this->map.find(name);
    if (it == this->map.end())
        return nullptr;
    return this->map.find(name)->second; //(return the symbol pointe (x, symbol_x)
}

Symbol* SymbolTable::getSymbolByOffset(int offset)
{
    for (std::multimap<string,Symbol*>::iterator it = this->map.begin(); it != this->map.end();++it)
    {
        if (it->second->getOffset() == offset)
            return it->second;
    }
    return nullptr;
}

bool SymbolTable::isEmpty()
{
    return this->map.empty();
}

SymbolTable::~SymbolTable()
{
    for (std::multimap<string,Symbol*>::iterator it = this->map.begin(); it != this->map.end();++it)
    {
        delete it->second;
    }
}


