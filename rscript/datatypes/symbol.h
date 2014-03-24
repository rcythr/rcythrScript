// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_SYMBOL : public L_ATOM
{
    static const DataType type_value;

    L_SYMBOL(std::string name)
        : L_ATOM(type_value)
        , mName(name)
    {
    }

    virtual std::string str();

    std::string mName;
};

typedef std::shared_ptr<L_SYMBOL> PL_SYMBOL;

PL_ATOM parseSymbol(const std::string& input, size_t& offset);

}

