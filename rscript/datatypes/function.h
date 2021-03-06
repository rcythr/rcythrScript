// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"
#include "symbol.h"

#include <rscript/symbol_table.h>

#include <vector>

namespace rscript
{

typedef std::function<PL_ATOM(SymbolTable&)> UserFunctionType;
typedef std::vector<PL_SYMBOL> ArgList;

struct L_FUNCTION : public L_ATOM
{
    static const DataType type_value;

    L_FUNCTION(ArgList args, UserFunctionType func, bool isLiteral=false)
        : L_ATOM(type_value, isLiteral)
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

