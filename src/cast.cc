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
    switch(atom->mType)
    {
    case DataType::INT:
    case DataType::REAL:
    case DataType::COMPLEX:
    case DataType::RATIONAL:
        return WRAP(L_STRING, atom->str());
    default:
        break;
    }
    throw std::runtime_error("Argument to number->string must be an int, real, rational, or complex.");
}

PL_ATOM proc_string_to_number(PL_STRING str, SymbolTable& symbols)
{
    size_t offset = 0;
    return parseNumeric(str->mValue, offset);
}

PL_ATOM proc_symbol_to_string(PL_SYMBOL sym, SymbolTable& symbols)
{
    return WRAP(L_STRING, sym->mName);
}

PL_ATOM proc_string_to_symbol(PL_STRING str, SymbolTable& symbols)
{
    return WRAP(L_SYMBOL, str->mValue, true);
}

PL_ATOM proc_char_to_integer(PL_CHAR chr, SymbolTable& symbols)
{
    return WRAP(L_INT, (int)chr->mValue);
}

PL_ATOM proc_integer_to_char(PL_INT in, SymbolTable& symbols)
{
    return WRAP(L_CHAR, (char)in->mValue);
}

PL_ATOM proc_string_to_list(PL_STRING str, SymbolTable& symbols)
{
    size_t offset = 0;
    return parseList(str->mValue, offset);
}

PL_ATOM proc_list_to_string(PL_LIST lst, SymbolTable& symbols)
{
    return WRAP(L_STRING, lst->str());
}

}
