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
    virtual ostream& printSymbol(std::ostream& os) const
    {
        os << "(" << this->getName() << ", " << this->getType() << ", " << this->getOffset() << ")";
        return os;
    }
    friend ostream& operator<<(ostream& os, const Symbol& s)
    {
        s.printSymbol(os);
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
    ostream& printSymbol(std::ostream& os) const override
    {
        os << "(" << this->getName() << ", " << this->getType() << ", " << this->getOffset() << ", ";
        os << "<";
        int size = this->input_args.size();
        if (size != 0)
        {
            for (int i = 0; i < size - 1; i++)
                os << this->input_args[i] << ", ";
            os << this->input_args[size-1];
        }
        os << ">";
        os << ")";
        return os;
    }
    friend ostream& operator<<(ostream& os, const FuncSymbol& s)
    {
        s.printSymbol(os);
        return os;
    }
};

//ostream& operator<<(ostream& os, const Symbol& s)


#endif //HW3_SYMBOL_HPP
