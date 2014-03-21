// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rcythr
{

struct L_STRING : public L_ATOM
{
    L_STRING(std::string& value)
        : L_ATOM(DataType::STRING)
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

