// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_STRING : public L_ATOM
{
    static const DataType type_value;

    L_STRING(std::string& value)
        : L_ATOM(type_value)
        , mValue(value)
    {
    }


    L_STRING(std::string&& value)
        : L_ATOM(DataType::STRING)
        , mValue(std::forward<std::string>(value))
    {
    }

    virtual std::string str();

    std::string mValue;
};

typedef std::shared_ptr<L_STRING> PL_STRING;

PL_ATOM parseString(const std::string& input, size_t& offset);

}

