// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rcythr
{

struct L_CHAR : public L_ATOM
{
    L_CHAR(char value)
        : L_ATOM(DataType::CHAR)
        , mValue(value)
    {
    }
    
    virtual std::string str();
    
    char mValue;
};

typedef std::shared_ptr<L_CHAR> PL_CHAR;

PL_ATOM parseChar(const std::string& input, size_t& offset);

}

