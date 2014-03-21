// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"
#include "symbol.h"

#include <rcythrScript/symbol_table.h>

#include <vector>

namespace rcythr
{

typedef std::function<PL_ATOM(SymbolTable&)> UserFunctionType;
typedef std::vector<PL_SYMBOL> ArgList;

struct L_FUNCTION : public L_ATOM
{
    L_FUNCTION(ArgList args, UserFunctionType func)
        : L_ATOM(DataType::FUNCTION)
        , mFunc(func)
        , mArgs(args)
    {
    }

    virtual std::string str();

    UserFunctionType mFunc;
    ArgList mArgs;
};

typedef std::shared_ptr<L_FUNCTION> PL_FUNCTION;

}

