// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rcythr
{

struct L_INT : public L_ATOM
{
    L_INT(int value)
        : L_ATOM(DataType::INT)
        , mValue(value)
    {
    }

    virtual std::string str();

    int mValue;
};

typedef std::shared_ptr<L_INT> PL_INT;

}

