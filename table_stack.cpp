//
// Created by yoavgilad on 5/27/23.
//
#include "table_stack.hpp"

std::vector<std::string> splitString(const std::string& inputString) {
    std::vector<std::string> words;
    std::stringstream ss(inputString);
    std::string word;

    while (std::getline(ss, word, ',')) {
        words.push_back(word);
    }
    return words;
}

void TableStack::addFuncSymbol(string name, string type, string args, string is_override)
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to add element when there are no scopes in stack");
    vector<string> input_args = splitString(args);
    bool is_over = false;
    if (is_override == "override")
        is_over = true;
    this->tables[this->tables.size()-1]->insertFunc(name, type, input_args, is_over);
    cout << "<";
    for (auto & it : input_args)
    {
        cout << it << ", ";
    }
    cout << ">";
}

void TableStack::addSymbolToLastTable(string name, string type)
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to add element when there are no scopes in stack");
    this->tables[this->tables.size()-1]->insert(name, type);
}

void TableStack::openNewScope()
{
    int new_offset;
    if (this->tables.empty())
        new_offset = 0;
    else
        new_offset = this->tables[this->tables.size() - 1]->getSymbolTableOffset();
    SymbolTable* t = new SymbolTable(new_offset);
    this->tables.push_back(t);
    cout << "scope opened!" << endl;
}

void TableStack::closeScope()
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to close scope when there are no scopes in stack");
    SymbolTable* t_to_delete = this->tables[this->tables.size()-1];
    this->tables.pop_back();
    delete t_to_delete;
    cout << "Scope closed!" << endl;
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

