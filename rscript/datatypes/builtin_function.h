// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

#include <rscript/symbol_table.h>

#include <vector>

namespace rscript
{

typedef std::function<PL_ATOM(std::vector<PL_ATOM>&,SymbolTable&)> BuiltinFuncType;

struct L_BUILTIN_FUNCTION : public L_ATOM
{
    L_BUILTIN_FUNCTION(BuiltinFuncType func)
        : L_ATOM(DataType::BUILTIN_FUNCTION)
        , mFunc(func)
    {
    }
    
    virtual std::string str();
    
    BuiltinFuncType mFunc;
};

typedef std::shared_ptr<L_BUILTIN_FUNCTION> PL_BUILTIN_FUNCTION;

}

