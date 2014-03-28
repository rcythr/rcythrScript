// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/constants.h>

namespace rscript
{

PL_ATOM proc_make_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    char c = 'a';
    size_t num = 0;
    switch(lst.size())
    {
        case 2:
            if(lst[1]->mType == DataType::CHAR)
                c = AS(L_CHAR, lst[1])->mValue;
            else
                throw std::runtime_error("make-string's second argument must be a char");
        case 1:
            if(lst[0]->mType == DataType::INT)
                num = AS(L_INT, lst[0])->mValue;
            else
                throw std::runtime_error("make-strings's first argument must be an int.");
        case 0:
        {
            std::string data;
            for(size_t i=0; i < num; ++i)
                data += c;
            return WRAP(L_STRING, std::move(data));
        }
        default:
            break;
    }
    throw std::runtime_error("make-string takes either 0, 1 or 2 arguments.");
}

PL_ATOM proc_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    std::string result;
    for(auto& atom : lst)
    {
        if(atom->mType != DataType::CHAR)
            throw std::runtime_error("string takes zero or more arguments of type char.");
        result += AS(L_CHAR, atom)->mValue;
    }
    return WRAP(L_STRING, result);
}

PL_ATOM proc_string_length(PL_STRING str, SymbolTable& symbols)
{
    return WRAP(L_INT, str->mValue.size());
}

PL_ATOM proc_string_ref(PL_STRING str, PL_INT k, SymbolTable& symbols)
{
    int kval = k->mValue;
    size_t index;
    if(kval < 0)
        index = str->mValue.size() + kval;
    else
        index = (size_t)kval;

    if(index >= 0 && index < str->mValue.size())
    {
        return WRAP(L_CHAR, str->mValue[index]);
    }
    throw std::runtime_error("String length insufficient to get k'th character.");
}

PL_ATOM proc_is_string_eq(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    return (a->mValue == b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_is_string_eq_ci(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    if(a->mValue.size() == b->mValue.size())
    {
        for(size_t i=0; i < a->mValue.size(); ++i)
        {
            if(to_lc(a->mValue[i]) != to_lc(b->mValue[i]))
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

PL_ATOM proc_string_lt(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    return (a->mValue < b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_string_lt_ci(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    if(a->mValue.size() == b->mValue.size())
    {
        for(size_t i=0; i < a->mValue.size(); ++i)
        {
            char lca = to_lc(a->mValue[i]);
            char lcb = to_lc(b->mValue[i]);
            if(lca > lcb)
            {
                return FALSE;
            }
            else if(lca < lcb)
            {
                return TRUE;
            }
        }
        return FALSE;
    }
    return FALSE;
}

PL_ATOM proc_string_gt(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    return (a->mValue > b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_string_gt_ci(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    if(a->mValue.size() == b->mValue.size())
    {
        for(size_t i=0; i < a->mValue.size(); ++i)
        {
            char lca = to_lc(a->mValue[i]);
            char lcb = to_lc(b->mValue[i]);
            if(lca < lcb)
            {
                return FALSE;
            }
            else if(lca > lcb)
            {
                return TRUE;
            }
        }
        return FALSE;
    }
    return FALSE;
}

PL_ATOM proc_string_lte(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    return (a->mValue <= b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_string_lte_ci(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    if(a->mValue.size() == b->mValue.size())
    {
        for(size_t i=0; i < a->mValue.size(); ++i)
        {
            char lca = to_lc(a->mValue[i]);
            char lcb = to_lc(b->mValue[i]);
            if(lca > lcb)
            {
                return FALSE;
            }
            else if(lca < lcb)
            {
                return TRUE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

PL_ATOM proc_string_gte(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    return (a->mValue >= b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_string_gte_ci(PL_STRING a, PL_STRING b, SymbolTable& symbols)
{
    if(a->mValue.size() == b->mValue.size())
    {
        for(size_t i=0; i < a->mValue.size(); ++i)
        {
            char lca = to_lc(a->mValue[i]);
            char lcb = to_lc(b->mValue[i]);
            if(lca < lcb)
            {
                return FALSE;
            }
            else if(lca > lcb)
            {
                return TRUE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

PL_ATOM proc_substring(PL_STRING str, PL_INT start, PL_INT end, SymbolTable& symbols)
{
    int startVal = start->mValue;
    int endVal = end->mValue;

    if((0 <= startVal) && (startVal <= endVal) && ((size_t)endVal <= str->mValue.size()))
    {
        return WRAP(L_STRING, str->mValue.substr(start->mValue, end->mValue - start->mValue));
    }
    throw std::runtime_error("substring requires that 0 <= start <= end <= string size");
}

PL_ATOM proc_string_append(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    std::string result;
    for(size_t i=0; i < lst.size(); ++i)
    {
        if(lst[i]->mType != DataType::STRING)
            throw std::runtime_error("All arguments to string-append must be strings.");
        result += AS(L_STRING, lst[i])->mValue;
    }
    return WRAP(L_STRING, result);
}

}
