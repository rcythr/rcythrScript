// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"
#include "int.h"

namespace rscript
{

struct L_RATIONAL : public L_ATOM
{
    static const DataType type_value;

    L_RATIONAL(PL_INT numerator, PL_INT denominator)
        : L_ATOM(type_value)
        , mNumerator(numerator)
        , mDenominator(denominator)
    {
    }
    
    virtual std::string str();
    
    PL_INT mNumerator;
    PL_INT mDenominator;
};

typedef std::shared_ptr<L_RATIONAL> PL_RATIONAL;

}

