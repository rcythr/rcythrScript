// Copyright (c) 2013 Richard Laughlin
// All Rights Reserved

#include "builtins.h"

namespace rcythr
{

char tolc(char val)
{
    if(val >= 'A' && val <= 'Z')
        return 'a' + (val-'A');
    return val;
}

PL_ATOM proc_is_char_eq(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() < 2)
        throw std::runtime_error("char=? requires at least two arguments of type char.");

    if(lst[0]->mType != LispType::CHAR)
        throw std::runtime_error("char=? requires at least two arguments of type char.");

    char val = AS(L_CHAR, lst[0])->mValue;
    for(size_t i=1; i < lst.size(); ++i)
    {
        if(lst[i]->mType != LispType::CHAR)
            throw std::runtime_error("char=? requires at least two arguments of type char.");

        if(val != AS(L_CHAR, lst[i])->mValue)
            return FALSE;
    }
    return TRUE;
}

PL_ATOM proc_is_char_eq_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() < 2)
        throw std::runtime_error("char-ci=? requires at least two arguments of type char.");

    if(lst[0]->mType != LispType::CHAR)
        throw std::runtime_error("char-ci=? requires at least two arguments of type char.");

    char val = AS(L_CHAR, lst[0])->mValue;
    for(size_t i=1; i < lst.size(); ++i)
    {
        if(lst[i]->mType != LispType::CHAR)
            throw std::runtime_error("char-ci=? requires at least two arguments of type char.");

        if(val != tolc(AS(L_CHAR, lst[i])->mValue))
            return FALSE;
    }
    return TRUE;
}

PL_ATOM proc_is_char(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1)
        throw std::runtime_error("char? requires exactly one arguments.");
    return (lst[0]->mType == LispType::CHAR) ? TRUE : FALSE;
}

PL_ATOM proc_char_lt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (AS(L_CHAR, lst[0])->mValue < AS(L_CHAR, lst[1])->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_lt_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (tolc(AS(L_CHAR, lst[0])->mValue) < tolc(AS(L_CHAR, lst[1])->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_char_gt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (AS(L_CHAR, lst[0])->mValue > AS(L_CHAR, lst[1])->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_gt_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (tolc(AS(L_CHAR, lst[0])->mValue) > tolc(AS(L_CHAR, lst[1])->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_char_lte(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (AS(L_CHAR, lst[0])->mValue <= AS(L_CHAR, lst[1])->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_lte_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (tolc(AS(L_CHAR, lst[0])->mValue) <= tolc(AS(L_CHAR, lst[1])->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_char_gte(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (AS(L_CHAR, lst[0])->mValue >= AS(L_CHAR, lst[1])->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_gte_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 2 || (lst[0]->mType != LispType::CHAR) || (lst[1]->mType != LispType::CHAR))
        throw std::runtime_error("char<? requires exactly two char arguments.");
    return (tolc(AS(L_CHAR, lst[0])->mValue) >= tolc(AS(L_CHAR, lst[1])->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_is_char_alphabetic(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("alphabetic? requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? TRUE : FALSE;
}

PL_ATOM proc_is_char_numeric(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("numeric? requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    return (c >= '0' && c <= '9') ? TRUE : FALSE;
}

PL_ATOM proc_is_char_whitespace(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("whitespace? requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n') ? TRUE : FALSE;
}

PL_ATOM proc_is_char_uppercase(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("uppercase? requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    return (c >= 'A' && c <= 'Z') ? TRUE : FALSE;
}

PL_ATOM proc_is_char_lowercase(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("lowercase? requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    return (c >= 'a' && c <= 'z') ? TRUE : FALSE;
}

PL_ATOM proc_char_upcase(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("upcase requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    if(c >= 'a' && c <= 'z')
        return WRAP(L_CHAR, 'A' + (c - 'a'));
    return lst[0];
}

PL_ATOM proc_char_downcase(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() != 1 || (lst[0]->mType != LispType::CHAR))
        throw std::runtime_error("downcase requires exactly one char arguments.");
    char c = AS(L_CHAR, lst[0])->mValue;
    if(c >= 'A' && c <= 'Z')
        return WRAP(L_CHAR, 'a' + (c - 'A'));
    return lst[0];
}
}
