// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_REAL : public L_ATOM
{
    typedef double value_type;

    L_REAL(double value)
        : L_ATOM(DataType::REAL)
        , mValue(value)
    {
    }
    
    virtual std::string str();
    
    value_type mValue;
};

typedef std::shared_ptr<L_REAL> PL_REAL;

}

