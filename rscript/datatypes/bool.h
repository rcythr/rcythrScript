// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_BOOL : public L_ATOM
{
    L_BOOL(bool value)
        : L_ATOM(DataType::BOOL)
        , mValue(value)
    {
    }

    virtual std::string str();

    bool mValue;
};

typedef std::shared_ptr<L_BOOL> PL_BOOL;

PL_ATOM parseBool(const std::string& input, size_t& offset);

}
