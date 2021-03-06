// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_CHAR : public L_ATOM
{
    static const DataType type_value;

    L_CHAR(char value, bool isLiteral=false)
        : L_ATOM(type_value, isLiteral)
        , mValue(value)
    {
    }
    
    virtual std::string str();
    
    char mValue;
};

typedef std::shared_ptr<L_CHAR> PL_CHAR;

PL_ATOM parseChar(const std::string& input, size_t& offset);

}

