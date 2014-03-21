// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"
#include "int.h"

namespace rcythr
{

struct L_RATIONAL : public L_ATOM
{
    L_RATIONAL(PL_INT numerator, PL_INT denominator)
        : L_ATOM(DataType::RATIONAL)
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

