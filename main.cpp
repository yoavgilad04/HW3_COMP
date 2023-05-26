//
// Created by yoavgilad on 5/26/23.
//

#include <stdlib.h>
#include "symbol_table.hpp"

int main()
{
    Symbol* a = new Symbol("a", "int");
    Symbol* b = new Symbol("b", "string");
    Symbol* c = new Symbol("c", "float");
    SymbolTable t;
    t.insert(a);
    t.insert(b);
    t.insert(c);
    std::cout << t;
}