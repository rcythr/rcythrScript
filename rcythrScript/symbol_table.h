
#pragma once

#include <unordered_map>

namespace rcythr
{

// Todo: Create a real symbol table type instead of this hackery
typedef std::unordered_map<std::string,PL_ATOM> SymbolTableType;

}
