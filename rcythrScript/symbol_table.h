
#pragma once

#include <rcythrScript/datatypes/atom.h>
#include <unordered_map>

namespace rcythr
{

class SymbolTable
{
public:

    SymbolTable();
    SymbolTable(SymbolTable& next);

    void set(std::string key, PL_ATOM value);
    void set_global(std::string key, PL_ATOM value);

    PL_ATOM get(std::string key);
    PL_ATOM get_global(std::string key);

    void clear();

private:
    
    SymbolTable* get_global_table();

    std::unordered_map<std::string, PL_ATOM> lookup;
    SymbolTable* next;
};

}
