// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/constants.h>

namespace rscript
{

PL_ATOM proc_vector_to_list(PL_VECTOR vec, SymbolTable& symbols)
{
    std::forward_list<PL_ATOM> output;
    auto bb = output.before_begin();
    for(auto& element : vec->mAtoms)
    {
        bb = output.insert_after(bb, element);
    }
    return WRAP(L_LIST, std::move(output));
}

PL_ATOM proc_list_to_vector(PL_LIST lst, SymbolTable& symbols)
{
    std::vector<PL_ATOM> output;
    for(auto& element : lst->mAtoms)
    {
        output.push_back(element);
    }
    return WRAP(L_VECTOR, std::move(output));
}

PL_ATOM proc_number_to_string(PL_ATOM atom, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_to_number(PL_STRING str, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_symbol_to_string(PL_SYMBOL sym, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_to_symbol(PL_STRING str, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_char_to_integer(PL_CHAR chr, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_integer_to_char(PL_INT in, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_to_list(PL_STRING str, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_list_to_string(PL_LIST lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}
