// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_INT : public L_ATOM
{
    typedef int value_type;

    L_INT(int value)
        : L_ATOM(DataType::INT)
        , mValue(value)
    {
    }

    virtual std::string str();

    value_type mValue;
};

typedef std::shared_ptr<L_INT> PL_INT;

}

