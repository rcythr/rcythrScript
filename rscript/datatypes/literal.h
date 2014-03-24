// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_LITERAL : public L_ATOM
{
    static const DataType type_value;

    L_LITERAL(PL_ATOM literal)
        : L_ATOM(type_value)
        , mLiteral(literal)
    {
    }
    
    virtual std::string str();
    
    PL_ATOM mLiteral;
};

typedef std::shared_ptr<L_LITERAL> PL_LITERAL;


}

