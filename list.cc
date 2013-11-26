// Copyright (c) 2013 Richard Laughlin
// All Rights Reserved

#include "builtins.h"

namespace rcythr
{

PL_ATOM proc_is_pair(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == LispType::LIST)
        {
            size_t i=0;

            auto& atoms = AS(L_LIST, lst[0])->mAtoms;
            auto itr = std::begin(atoms);
            while(itr != atoms.end())
            {
                if(i > 2)
                    break;
                ++i;
            }
            return WRAP(L_BOOL, i == 2);
        }
        else if(lst[0]->mType == LispType::VECTOR)
        {
            return WRAP(L_BOOL, AS(L_VECTOR, lst[0])->mAtoms.size() == 2);
        }
        else
        {
            return WRAP(L_BOOL, false);
        }
    }
    throw std::runtime_error("pair? expects exactly one argument of type list.");
}

PL_ATOM proc_list(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    std::forward_list<PL_ATOM> atoms;
    auto bb = atoms.before_begin();

    for(auto& atom : lst)
        bb = atoms.insert_after(bb, atom);

    return WRAP(L_LIST, std::move(atoms));
}

PL_ATOM proc_cons(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_car(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_cdr(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_set_car_exclaim(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_set_cdr_exclaim(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_null(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_list(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_length(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_append(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_reverse(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_list_tail(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_list_ref(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_memq(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_memv(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_member(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_assq(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_assv(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_assoc(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}
