
#pragma once

#include "atom.h"

#include <forward_list>

namespace rscript
{

struct L_LIST : public L_ATOM
{
    static const DataType type_value;

    L_LIST(std::forward_list<PL_ATOM>& atoms, bool isLiteral=false)
        : L_ATOM(type_value, isLiteral)
        , mAtoms(atoms)
    {
    }
    
    L_LIST(std::forward_list<PL_ATOM>&& atoms, bool isLiteral=false)
        : L_ATOM(DataType::LIST, isLiteral)
        , mAtoms(std::forward<std::forward_list<PL_ATOM>>(atoms))
    {
    }

    virtual std::string str();

    std::forward_list<PL_ATOM> mAtoms;
};

typedef std::shared_ptr<L_LIST> PL_LIST;

PL_ATOM parseList(const std::string& input, size_t& offset);

}

