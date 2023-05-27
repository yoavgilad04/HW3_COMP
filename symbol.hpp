//
// Created by yoavgilad on 5/26/23.
//

#ifndef HW3_SYMBOL_HPP
#define HW3_SYMBOL_HPP

#include <string>
#include <iostream>
#include <vector>




using namespace std;

class Symbol
{
    string name;
    string type;
    int offset;
    bool is_func;

public:
    Symbol(string name, string type,  int offset=0, bool is_func=false):
    name(name), type(type), offset(offset), is_func(is_func){}
    int getOffset() const {return this->offset;}
    string getName() const {return this->name;}
    string getType() const {return this->type;}
    void setOffset(int offset){this->offset = offset;}
    friend ostream& operator<<(ostream& os, const Symbol& s)
    {
        os << "(" << s.getName() << ", " << s.getType() << ", " << s.getOffset() << ")";
        return os;
    }
};

class FuncSymbol : public Symbol
{
    vector<string> input_args;
    bool is_override;
public:
    FuncSymbol(string name, string type, int offset, bool is_func, vector<string> input_args, bool is_override):
            Symbol(name, type, offset, is_func), input_args(input_args), is_override(is_override){};
    bool isOverride(){return this->is_override;}
    friend ostream& operator<<(ostream& os, const FuncSymbol& s)
    {
        os << "(" << s.getName() << ", " << s.getType() << ", " << s.getOffset() << ", ";
        os << "< ";
        for (auto & it : s.input_args)
        {
            os << it << ", ";
        }
        os << " >";
        os << ")";
        return os;
    }
};

//ostream& operator<<(ostream& os, const Symbol& s)


#endif //HW3_SYMBOL_HPP
