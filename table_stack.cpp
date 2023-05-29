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

bool isVectorsEqual(const std::vector<string>& v1, std::vector<string>& v2)
{
    if (v1.size() != v2.size())
        return false;
    for(int i=0; i<v1.size(); i++)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

void TableStack::addFuncSymbol(string name, string type, string args, string is_override)
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to add element when there are no scopes in stack");
    if (name == "main")
    {
        Symbol* potential_main = searchForSymbol(name);
        if (potential_main != nullptr || is_override == "OVERRIDE")
            output::errorMainOverride(yylineno);
    }
    vector<string> input_args = splitString(args);
    bool is_over = true;
    if (is_override != "OVERRIDE")
    {
        is_over = false;
    }
    vector<FuncSymbol*> funcs = this->getAllFunctionsWithName(name);
    if (func != nullptr)
    {
        if (!funcs[0]->isOverride())
            output::errorFuncNoOverride(yylineno, name);
        if (!is_over)
            output::errorOverrideWithoutDeclaration(yylineno, name);
        for (int i=0; i<funcs.size(); i++)
        {
            if (isVectorsEqual(input_args, funcs[i].getArgs()))
                output::errorDef(yylineno, name);
        }

    }
    if (this->tables.size() > 1)
        this->tables[this->tables.size()-2]->insertFunc(name, type, input_args, is_over); // we want the func symbol to enter previous scope
    else
        this->tables[this->tables.size()-1]->insertFunc(name, type, input_args, is_over);

}

bool TableStack::isFuncExist(string func_name)
{
    FuncSymbol* func = this->searchForFuncSymbol(func_name);
     if (func == nullptr)
         return false;
     if (!func->isOverride())
         output::errorFuncNoOverride(yylineno, func_name);
     return true;
}

FuncSymbol* TableStack::searchForFuncSymbol(string func_name)
{
    FuncSymbol* func = dynamic_cast<FuncSymbol*>(this->searchForSymbol(func_name));
    return func; //if the cast failed func = nullptr
}

void TableStack::addSymbolToLastTable(string name, string type, bool is_func_arg)
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to add element when there are no scopes in stack");
    if (this->searchForSymbol(name) != nullptr)
        output::errorDef(yylineno, name);
    this->tables[this->tables.size()-1]->insert(name, type, is_func_arg);
}

vector<FuncSymbol*> TableStack::getAllFunctionsWithName(string name)
{
    vector<FuncSymbol*> funcs();
    for(int i=0; i<this->tables.size(); i++)
        funcs.insert(funcs.end(), this->tables[i].begin(), this->tables[i].end());
    if (funcs.empty())
        return nullptr;
    return funcs;
}

void TableStack::openNewScope()
{
    int new_offset;
    if (this->tables.empty() || this->tables.size() == 1)
    {
        new_offset = 0;
    }
    else
        new_offset = this->tables[this->tables.size() - 1]->getSymbolTableOffset() + 1;
    SymbolTable* t = new SymbolTable(new_offset);
    this->tables.push_back(t);
//    cout << "scope opened!" << endl;
}

void TableStack::closeScope()
{
    if (this->tables.empty())
        throw std::invalid_argument("Trying to close scope when there are no scopes in stack");
    SymbolTable* t_to_delete = this->tables[this->tables.size()-1];

//    this->printStack();
    if(this->tables.size() == 1)
    {
//        cout <<"I'm in last scope" << endl;
        FuncSymbol* main = dynamic_cast<FuncSymbol*>(this->searchForSymbol("main"));
        if (main == nullptr || main->getType() != "VOID")
            output::errorMainMissing();
    }

    output::endScope();
    cout << *t_to_delete;
    this->tables.pop_back();
    delete t_to_delete;
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

void TableStack::printStack()
{
    for (int i = this->tables.size()-1; i>=0; i--)
    {
        cout << "Table "<< i << ": " << *(this->tables[i]) << endl;
    }
}

TableStack::~TableStack()
{
    if (this->tables.size() != 0)
        cout <<"ERROR: More then one Scope when deleteing tableStack";
    for(int i=0; i<this->tables.size(); i++)
    {
        delete this->tables[i];
    }
}

void TableStack::compareType(string id_name, string exp_type)
{
    cout<<"In compareType function, id: " << id_name << " exp_type: " << exp_type << endl;
    Symbol* s = this->searchForSymbol(id_name);
    if (s == nullptr)
        output::errorUndef(yylineno, id_name);
    if (s->getType() != exp_type)
        output::errorMismatch(yylineno);
}


