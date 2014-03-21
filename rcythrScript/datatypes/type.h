// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.
#pragma once

namespace rcythr
{

enum class DataType
{
    // NUMERIC TYPES
    INT,
    REAL,
    RATIONAL,
    COMPLEX,

    // Wrapper types
    LIST,
    LITERAL,
    VECTOR,

    // String Types
    CHAR,
    STRING,

    BOOL,
    SYMBOL,
    BUILTIN_FUNCTION,
    FUNCTION
};

}

