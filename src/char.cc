// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/constants.h>

namespace rscript
{

PL_ATOM proc_is_char_eq(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (a->mValue == b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_is_char_eq_ci(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    char aLC = (a->mValue > 'A' && a->mValue < 'Z') ? to_lc(a->mValue) : a->mValue;
    char bLC = (b->mValue > 'A' && b->mValue < 'Z') ? to_lc(b->mValue) : b->mValue;
    return (aLC == bLC) ? TRUE : FALSE;
}

PL_ATOM proc_char_lt(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (a->mValue < b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_lt_ci(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (to_lc(a->mValue) < to_lc(b->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_char_gt(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (a->mValue > b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_gt_ci(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (to_lc(a->mValue) > to_lc(b->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_char_lte(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (a->mValue <= b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_lte_ci(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (to_lc(a->mValue) <= to_lc(b->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_char_gte(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (a->mValue >= b->mValue) ? TRUE : FALSE;
}

PL_ATOM proc_char_gte_ci(PL_CHAR a, PL_CHAR b, SymbolTable& symbols)
{
    return (to_lc(a->mValue) >= to_lc(b->mValue)) ? TRUE : FALSE;
}

PL_ATOM proc_is_char_alphabetic(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue;
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? TRUE : FALSE;
}

PL_ATOM proc_is_char_numeric(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue; 
    return (c >= '0' && c <= '9') ? TRUE : FALSE;
}

PL_ATOM proc_is_char_whitespace(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue; 
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n') ? TRUE : FALSE;
}

PL_ATOM proc_is_char_uppercase(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue; 
    return (!(c >= 'a' && c <= 'z')) ? TRUE : FALSE;
}

PL_ATOM proc_is_char_lowercase(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue; 
    return (!(c >= 'A' && c <= 'Z')) ? TRUE : FALSE;
}

PL_ATOM proc_char_upcase(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue; 
    if(c >= 'a' && c <= 'z')
        return WRAP(L_CHAR, to_uc(c));
    return chr; 
}

PL_ATOM proc_char_downcase(PL_CHAR chr, SymbolTable& symbols)
{
    char c = chr->mValue; 
    if(c >= 'A' && c <= 'Z')
        return WRAP(L_CHAR, to_lc(c));
    return chr;
}
}
