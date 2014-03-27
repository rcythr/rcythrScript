// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

#include <rscript/builtin_handler.h>

#include <vector>

namespace rscript
{

typedef std::shared_ptr<BuiltinHandlerInterface> BuiltinFuncType;

struct L_BUILTIN_FUNCTION : public L_ATOM
{
    static const DataType type_value;

    L_BUILTIN_FUNCTION(BuiltinFuncType func, bool isLiteral=false)
        : L_ATOM(type_value, isLiteral)
        , mFunc(func)
    {
    }
    
    virtual std::string str();
    
    BuiltinFuncType mFunc;
};

typedef std::shared_ptr<L_BUILTIN_FUNCTION> PL_BUILTIN_FUNCTION;

}

