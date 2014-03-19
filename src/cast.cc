// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rcythrScript/builtins.h>

namespace rcythr
{

PL_ATOM proc_vector_to_list(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    std::forward_list<PL_ATOM> output;
    auto bb = output.before_begin();
    for(auto& element : lst)
    {
        bb = output.insert_after(bb, element);
    }
    return WRAP(L_LIST, std::move(output));
}

PL_ATOM proc_list_to_vector(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    std::vector<PL_ATOM> output;
    for(auto& element : lst)
    {
        output.push_back(element);
    }
    return WRAP(L_VECTOR, std::move(output));
}

PL_ATOM proc_number_to_string(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_to_number(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_symbol_to_string(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_to_symbol(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_char_to_integer(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_integer_to_char(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_to_list(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_list_to_string(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}
