// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

#include <vector>

namespace rscript
{

struct L_VECTOR : public L_ATOM
{
    L_VECTOR(std::vector<PL_ATOM>& atoms)
        : L_ATOM(DataType::VECTOR)
        , mAtoms(atoms)
    {
    }
    
    L_VECTOR(std::vector<PL_ATOM>&& atoms)
        : L_ATOM(DataType::VECTOR)
        , mAtoms(std::forward<std::vector<PL_ATOM>>(atoms))
    {
    }
    
    virtual std::string str();
    
    std::vector<PL_ATOM> mAtoms;
};

typedef std::shared_ptr<L_VECTOR> PL_VECTOR;

PL_ATOM parseVector(const std::string& input, size_t& offset);

}
