// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.
#pragma once

#include "type.h"

#include <memory>

namespace rscript
{

struct L_ATOM
{
    static const DataType type_value;

    L_ATOM(DataType type, bool isLiteral=false)
        : mType(type)
        , mIsLiteral(isLiteral)
    {
    }

    virtual std::string str() = 0;

    DataType mType;
    bool mIsLiteral;
};

typedef std::shared_ptr<L_ATOM> PL_ATOM;

}

