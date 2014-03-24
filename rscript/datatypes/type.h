// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.
#pragma once

namespace rscript
{

enum class DataType
{
    ATOM = 0,
    BOOL,
    BUILTIN_FUNCTION,
    CHAR,
    COMPLEX,
    FUNCTION,
    INT,
    LIST,
    LITERAL,
    REAL,
    RATIONAL,
    STRING,
    SYMBOL,
    VECTOR,
};

extern const char* TYPE_NAME_LOOKUP[];

}

