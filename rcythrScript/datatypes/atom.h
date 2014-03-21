// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.
#pragma once

#include "type.h"

#include <memory>

namespace rcythr
{

struct L_ATOM
{
    L_ATOM(DataType type)
        : mType(type)
    {
    }

    virtual std::string str() = 0;

    DataType mType;
};

typedef std::shared_ptr<L_ATOM> PL_ATOM;

}

