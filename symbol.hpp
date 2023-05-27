//
// Created by yoavgilad on 5/26/23.
//

#ifndef HW3_SYMBOL_HPP
#define HW3_SYMBOL_HPP

#include <string>
#include <iostream>
#include <list>

using namespace std;
class Symbol
{
    string name;
    string type;
    int offset;
    bool isFunc;

public:
    Symbol(string name, string type,  int offset=0, bool isFunc=false):
    name(name), type(type), offset(offset), isFunc(isFunc){}
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

//ostream& operator<<(ostream& os, const Symbol& s)


#endif //HW3_SYMBOL_HPP
