#include "builtins.h"

namespace rcythr
{

PL_ATOM proc_make_string(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    char c = 'a';
    size_t num = 0;
    switch(lst.size())
    {
        case 2:
            if(lst[1]->mType == LispType::CHAR)
                c = AS(L_CHAR, lst[1])->mValue;
            else
                throw std::runtime_error("make-string's second argument must be a char");
        case 1:
            if(lst[0]->mType == LispType::INT)
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

PL_ATOM proc_is_string(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_length(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_ref(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_set_exclaim(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_string_eq(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_string_eq_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_lt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_lt_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_gt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_gt_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_lte(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_lte_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_gte(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_gte_ci(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_substring(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_append(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_copy(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_string_fill_exclaim(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}
